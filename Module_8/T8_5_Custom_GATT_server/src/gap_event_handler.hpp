/**
 * @file gap_event_handler.hpp
 * @brief Template declaration for the Module 8 custom GATT server GAP handler.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.5.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#pragma once

#include "attribute_server.hpp"
#include "gap.hpp"

/**
 * @brief GAP event handler for the Module 8 custom GATT server task.
 *
 * The handler is responsible for:
 * - propagating the active connection handle to the AttributeServer,
 * - restarting advertising after disconnection,
 * - printing connection state changes, and
 * - exposing the current connection state to the application task.
 */
class GapEventHandler : public c7222::Gap::EventHandler {
   public:
	/**
	 * @brief Construct the handler with optional GAP and AttributeServer
	 * pointers.
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
	 * @brief Return whether a client is currently connected.
	 */
	bool IsConnected() const { return connected_; }

	// TODO: declare the GAP event-handler callbacks required to detect
	// connection completion and disconnection completion.
	

   private:
	c7222::Gap* gap_ = nullptr;
	c7222::AttributeServer* attribute_server_ = nullptr;
	mutable bool connected_ = false;
};
