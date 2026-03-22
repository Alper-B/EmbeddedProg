/**
 * @file gap_event_handler.cpp
 * @brief Template implementation for the Module 8 GATT service GAP handler.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.4.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#include "gap_event_handler.hpp"

#include <cstdio>

GapEventHandler::GapEventHandler(c7222::Gap* gap,
								 c7222::AttributeServer* attribute_server)
	: gap_(gap), attribute_server_(attribute_server) {}

void GapEventHandler::SetAttributeServer(c7222::AttributeServer* attribute_server) {
	// TODO: store the AttributeServer pointer for later connection handling.
	
	(void)attribute_server;
	
}

void GapEventHandler::OnConnectionComplete(uint8_t status,
										   c7222::ConnectionHandle con_handle,
										   const c7222::BleAddress& address,
										   uint16_t conn_interval,
										   uint16_t conn_latency,
										   uint16_t supervision_timeout) const {
	(void)address;
	std::printf(
		"GAP event: ConnectionComplete (status=0x%02X, handle=%u, interval=%u, latency=%u, timeout=%u)\n",
		status,
		con_handle,
		conn_interval,
		conn_latency,
		supervision_timeout);

	// TODO: if an AttributeServer exists, propagate the active connection handle
	// to it so GATT operations can use the current connection.
	
	(void)con_handle;
	
}

void GapEventHandler::OnDisconnectionComplete(uint8_t status,
											  c7222::ConnectionHandle con_handle,
											  uint8_t reason) const {
	std::printf("GAP event: DisconnectionComplete (status=0x%02X, handle=%u, reason=0x%02X)\n",
				status,
				con_handle,
				reason);

	// TODO: restart advertising through GAP so the device becomes discoverable again.
	
	(void)status;
	(void)con_handle;
	(void)reason;
	
}
