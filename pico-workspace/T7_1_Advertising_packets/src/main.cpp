/**
 * @file main.cpp
 * @brief Demonstration entry point for advertising packet payload builders.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.1: Advertising Packets.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 * NOTE: This file is for local testing only.
 * The exercise solution must be implemented in `adv_packets.cpp`.
 */

#include <iomanip>
#include <iostream>

#include "adv_packets.h"

/**
 * @brief Print advertisement payload as hex bytes.
 */
static void PrintPayload(const std::string& label, const std::vector<std::uint8_t>& payload) {
	std::cout << label << ": ";
	for (std::size_t i = 0; i < payload.size(); ++i) {
		std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
				  << static_cast<int>(payload[i]);
		if (i + 1 < payload.size()) {
			std::cout << ' ';
		}
	}
	std::cout << std::dec << '\n';
}

int main() {
	const std::string device_name = "Pico2W";
	const std::uint16_t company_id = 0x0059;  // Apple example company ID for demo output.
	const std::int8_t tx_power_dbm = -4;
	const std::uint8_t counter = 17;
	const std::uint16_t service_uuid = 0x180F;	// Battery Service
	const std::uint16_t sensor_value = 0x01AF;

	auto flags_and_name = BuildFlagsAndNameAdvertisement(device_name);
	auto tx_and_manufacturer = BuildTxPowerAndManufacturerAdvertisement(company_id, tx_power_dbm, counter);
	auto uuid_and_service_data = BuildUuidAndServiceDataAdvertisement(service_uuid, sensor_value);

	PrintPayload("Flags + Complete Local Name", flags_and_name);
	PrintPayload("Tx Power + Manufacturer", tx_and_manufacturer);
	PrintPayload("UUID List + Service Data", uuid_and_service_data);

	return 0;
}
