/**
 * @file adv_packets.h
 * @brief BLE advertising packet builder declarations for M7 advertising task.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.1: Advertising Packets.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

/**
 * @note All functions declared in this file must be implemented in
 * `adv_packets.cpp`.
 */

#ifndef ADV_PACKETS_H_
#define ADV_PACKETS_H_

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Build a legacy advertising payload that contains:
 *  - Flags (LE General Discoverable Mode + BR/EDR Not Supported)
 *  - Complete Local Name (device_name)
 *
 * @param device_name ASCII/UTF-8 device name.
 * @return Raw advertising payload bytes (concatenated AD structures).
 */
std::vector<std::uint8_t> BuildFlagsAndNameAdvertisement(const std::string& device_name);

/**
 * @brief Build a legacy advertising payload that contains:
 *  - Tx Power Level (1 byte)
 *  - Manufacturer Specific Data (company_id_little_endian + counter)
 *
 * @param company_id Bluetooth SIG company identifier.
 * @param tx_power_dbm Transmit power in dBm (signed 8-bit).
 * @param counter Application counter value.
 * @return Raw advertising payload bytes (concatenated AD structures).
 */
std::vector<std::uint8_t> BuildTxPowerAndManufacturerAdvertisement(std::uint16_t company_id,
																   std::int8_t tx_power_dbm,
																   std::uint8_t counter);

/**
 * @brief Build a legacy advertising payload that contains:
 *  - Complete list of 16-bit Service UUIDs (one UUID)
 *  - 16-bit Service Data (service_uuid + sensor_value)
 *
 * @param service_uuid 16-bit UUID.
 * @param sensor_value Payload to place in the service data.
 * @return Raw advertising payload bytes (concatenated AD structures).
 */
std::vector<std::uint8_t> BuildUuidAndServiceDataAdvertisement(std::uint16_t service_uuid,
															   std::uint16_t sensor_value);

#endif  // ADV_PACKETS_H_
