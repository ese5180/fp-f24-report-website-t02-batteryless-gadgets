/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_IPC_ICMSG_ME_H_
#define ZEPHYR_INCLUDE_IPC_ICMSG_ME_H_

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/ipc/icmsg.h>
#include <zephyr/ipc/ipc_service.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Multi-endpoint extension of icmsg IPC library
 * @defgroup ipc_icmsg_me_api Icmsg multi-endpoint IPC library API
 * @ingroup ipc
 * @{
 */


/* If more bytes than 1 was used for endpoint id, endianness should be
 * considered.
 */
typedef uint8_t icmsg_me_ept_id_t;

struct icmsg_me_data_t {
	struct icmsg_data_t icmsg_data;
	struct ipc_ept_cfg ept_cfg;

	struct k_event event;

	struct k_mutex send_mutex;
	const struct ipc_ept_cfg *epts[CONFIG_IPC_SERVICE_BACKEND_ICMSG_ME_NUM_EP];

	uint8_t send_buffer[CONFIG_IPC_SERVICE_BACKEND_ICMSG_ME_SEND_BUF_SIZE] __aligned(4);
};


/** @brief Initialize an icmsg_me instance
 *
 *  This function is intended to be called during system initialization.
 *  It initializes the underlying icmsg instace as one of the initialization
 *  steps.
 *
 *  @param[in] conf Structure containing configuration parameters for the
 *                  underlying icmsg instance being created.
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure shall be filled with zeros
 *                     when calling this function. The content of this
 *                     structure must be preserved while the icmsg_me instance
 *                     is active.
 *
 *  @retval 0 on success.
 *  @retval other errno codes from dependent modules.
 */
int icmsg_me_init(const struct icmsg_config_t *conf,
		  struct icmsg_me_data_t *data);

/** @brief Open an icmsg_me instance
 *
 *  Open an icmsg_me instance to be able to send and receive messages to a
 *  remote instance.
 *  This function is blocking until the handshake with the remote instance is
 *  completed.
 *  This function is intended to be called late in the initialization process,
 *  possibly from a thread which can be safely blocked while handshake with the
 *  remote instance is being pefromed.
 *
 *  @param[in] conf Structure containing configuration parameters for the
 *                  underlying icmsg instance.
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] cb Structure containing callback functions to be called on
 *                events generated by this icmsg_me instance. The pointed memory
 *                must be preserved while the icmsg_me instance is active.
 *  @param[in] ctx Pointer to context passed as an argument to callbacks.
 *
 *
 *  @retval 0 on success.
 *  @retval other errno codes from dependent modules.
 */
int icmsg_me_open(const struct icmsg_config_t *conf,
		  struct icmsg_me_data_t *data,
		  const struct ipc_service_cb *cb,
		  void *ctx);

/** @brief Wait until the underlying icmsg instance calls bound callback
 *
 *  This function blocks calling thread until the underlying icmsg connection
 *  is bound. If the connection was bound before this function is called, the
 *  function ends immediately without any delay.
 *
 *  This function is intended to be used in the endpoints handshake procedure
 *  to make sure that handshake is not performed until the icmsg channel is
 *  ready to pass handshake messages.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 */
void icmsg_me_wait_for_icmsg_bind(struct icmsg_me_data_t *data);

/** @brief Notify the icmsg_me instance that the underlying icmsg was bound
 *
 *  The icmsg_me API users are responsible to implement the callback functions
 *  called by the underlying icmsg instance. One of the actions of the bound
 *  callback must be calling this function.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 */
void icmsg_me_icmsg_bound(struct icmsg_me_data_t *data);

/** @brief Notify the icmsg_me instance that data for an endpoint was received
 *
 *  The icmsg_me API users are responsible to implement the callback functions
 *  called by the underlying icmsg instance. If the data received by the icmsg
 *  instance contains data frame destined to one of the endpoints, this
 *  function must be called.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] id The value identifyig the endpoint.
 *  @param[in] msg Data frame received from the peer, stripped of the
 *                 multi-endpoint header.
 *  @param[in] len Size of the data pointed by @p msg.
 */
void icmsg_me_received_data(struct icmsg_me_data_t *data, icmsg_me_ept_id_t id,
			    const void *msg, size_t len);

/** @brief Set endpoint configuration in an empty endpoint slot
 *
 *  During endpoint handshake the handshake initiator must select an id number
 *  and store endpoint metadata required to finalize handshake and maintain
 *  the connection. This function is a helper which stores the configuration
 *  in an empty configuration slot and provides the unique id value associated
 *  with the selected slot.
 *
 *  @note This function is not reentrant for a single icmsg_me instance.
 *        It must be protected by the caller using mutex, critical section,
 *        spinlock, or similar solution.
 *        This function is reentrant for different icmsg_me instances. The
 *        protection scope might be limited to a single instance.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] ept_cfg Configuration data of the endpoint for which the
 *                     handshake procedure is being initiated.
 *  @param[out] id The value uniquely identifyig this endpoint.
 *
 *  @retval 0 on success.
 *  @retval -ENOMEM when there are no more empty endpoint configuration slots.
 */
int icmsg_me_set_empty_ept_cfg_slot(struct icmsg_me_data_t *data,
				    const struct ipc_ept_cfg *ept_cfg,
				    icmsg_me_ept_id_t *id);

/** @brief Set endpoint configuration in a selected endpoint slot
 *
 *  During endpoint handshake the handshake follower must store endpoint id and
 *  metadata required to finalize handshake and maintain the connection. This
 *  function is a helper which stores the configuration in a configuration slot
 *  associated with the id of the endpoint.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] id The value uniquely identifyig this endpoint.
 *  @param[in] ept_cfg Configuration data of the endpoint for which the
 *                     handshake procedure is ongoing.
 *
 *  @retval 0 on success.
 *  @retval -ENOENT when @p id is out of range of available slots.
 */
int icmsg_me_set_ept_cfg(struct icmsg_me_data_t *data, icmsg_me_ept_id_t id,
			 const struct ipc_ept_cfg *ept_cfg);

/** @brief Get endpoint configuration from a selected endpoint slot
 *
 *  When the icmsg_me instance receives data from a remote endpoint, it must
 *  get the endpoint configuration based on the id of the endpoint. This
 *  function is designed for this purpose.
 *
 *  If retrieved endpoint configuration is not set, @p ept_cfg points to NULL.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] id The value uniquely identifyig endpoint.
 *  @param[in] ept_cfg Configuration data of the endpoint with given id.
 *
 *  @retval 0 on success.
 *  @retval -ENOENT when @p id is out of range of available slots.
 */
int icmsg_me_get_ept_cfg(struct icmsg_me_data_t *data, icmsg_me_ept_id_t id,
			 const struct ipc_ept_cfg **ept_cfg);

/** @brief Reset endpoint configuration in a selected endpoint slot.
 *
 *  If handshake fails or an endpoint is disconnected, then configuration
 *  slot for given endpoint should be vacated. This function is intended to
 *  be used for this purpose.
 *
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] id The value uniquely identifyig endpoint.
 */
void icmsg_me_reset_ept_cfg(struct icmsg_me_data_t *data, icmsg_me_ept_id_t id);

/** @brief Send a message to the remote icmsg_me endpoint.
 *
 *  @param[in] conf Structure containing configuration parameters for the
 *                  underlying icmsg instance.
 *  @param[inout] data Structure containing run-time data used by the icmsg_me
 *                     instance. The structure is initialized with
 *                     @ref icmsg_me_init and its content must be preserved
 *                     while the icmsg_me instance is active.
 *  @param[in] id Id of the endpoint to use.
 *  @param[in] msg Pointer to a buffer containing data to send.
 *  @param[in] len Size of data in the @p msg buffer.
 *
 *
 *  @retval 0 on success.
 *  @retval -EBADMSG when the requested data to send is too big.
 *  @retval other errno codes from dependent modules.
 */
int icmsg_me_send(const struct icmsg_config_t *conf,
		  struct icmsg_me_data_t *data, icmsg_me_ept_id_t id,
		  const void *msg, size_t len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_IPC_ICMSG_ME_H_ */
