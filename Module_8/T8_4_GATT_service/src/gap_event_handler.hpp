/**
 * @file gap_event_handler.hpp
 * @brief Template declaration for the Module 8 GATT service GAP handler.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.4.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#pragma once

#include "attribute_server.hpp"
#include "gap.hpp"

/**
 * @brief Minimal GAP event handler for the Module 8 GATT service task.
 *
 * The class is responsible for:
 * - propagating the active connection handle to the AttributeServer,
 * - restarting advertising after disconnection, and
 * - printing a small amount of runtime status for debugging.
 */
class GapEventHandler : public c7222::Gap::EventHandler {
   public:
	/**
	 * @brief Construct the handler with optional GAP and AttributeServer pointers.
	 *
	 * @param gap GAP instance used for restarting advertising after disconnect.
	 * @param attribute_server Attribute server that should receive the active
	 * connection handle.
	 */
	explicit GapEventHandler(c7222::Gap* gap = c7222::Gap::GetInstance(),
							 c7222::AttributeServer* attribute_server = nullptr);

	/**
	 * @brief Attach the attribute server after construction.
	 *
	 * @param attribute_server Attribute server used by the running application.
	 */
	void SetAttributeServer(c7222::AttributeServer* attribute_server);

	/**
	 * @brief Handle successful connection completion events.
	 */
	void OnConnectionComplete(uint8_t status,
							  c7222::ConnectionHandle con_handle,
							  const c7222::BleAddress& address,
							  uint16_t conn_interval,
							  uint16_t conn_latency,
							  uint16_t supervision_timeout) const override;

	/**
	 * @brief Handle disconnection events.
	 */
	void OnDisconnectionComplete(uint8_t status,
								 c7222::ConnectionHandle con_handle,
								 uint8_t reason) const override;

   private:
	c7222::Gap* gap_ = nullptr;
	c7222::AttributeServer* attribute_server_ = nullptr;
};
