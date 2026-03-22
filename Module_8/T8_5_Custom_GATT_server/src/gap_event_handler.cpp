/**
 * @file gap_event_handler.cpp
 * @brief Template implementation for the Module 8 custom GATT server GAP handler.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.5.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#include "gap_event_handler.hpp"

#include <cstdio>

// The constructor is provided as part of the template.
// SetAttributeServer(...) remains part of the student implementation.
GapEventHandler::GapEventHandler(c7222::Gap* gap,
								 c7222::AttributeServer* attribute_server)
	: gap_(gap), attribute_server_(attribute_server) {}

void GapEventHandler::SetAttributeServer(c7222::AttributeServer* attribute_server) {
	// TODO: store the AttributeServer pointer for later connection handling.
	
	(void)attribute_server;
	
}
// TODO: define the GAP event-handler overrides declared in the header:
// - OnConnectionComplete(...)
// - OnDisconnectionComplete(...)
// OnConnectionComplete(...) must print the connection, propagate the
// connection handle to AttributeServer, and update the connection state.
// OnDisconnectionComplete(...) must print the disconnection, restart
// advertising, and update the connection state.

