#include <cstdint>
#include <vector>

/**
 * @file adv_packets.cpp
 * @brief Task template implementation for BLE advertising payload builders.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.1: Advertising Packets.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#include "adv_packets.h"

#include "advertisement_data.hpp"

/**
 * Task Description (Module 7 Task 7.1: Advertising Packets)
 *
 * Goal:
 * - Build BLE legacy advertising payloads using ``AdvertisementDataBuilder``.
 *
 * Requirements:
 * 1. Implement ``BuildFlagsAndNameAdvertisement``.
 *    - Add ``kFlags`` with value ``0x06``.
 *    - Add ``kCompleteLocalName`` containing ``device_name``.
 * 2. Implement ``BuildTxPowerAndManufacturerAdvertisement``.
 *    - Add ``kTxPowerLevel`` with one-byte signed dBm value.
 *    - Add ``kManufacturerSpecific`` with little-endian
 *      ``company_id`` and one-byte ``counter``.
 * 3. Implement ``BuildUuidAndServiceDataAdvertisement``.
 *    - Add ``kCompleteList16BitUuid`` with one UUID.
 *    - Add ``kServiceData16BitUuid`` with UUID and sensor value in little-endian.
 * 4. Ensure each function builds the payload before returning bytes.
 */

std::vector<std::uint8_t> BuildFlagsAndNameAdvertisement(const std::string& device_name) {
	
	// TODO: Create an AdvertisementDataBuilder, add Flags + Complete Local Name,
	// build the payload, and return the raw bytes.
	//
	// Requirements:
	// - Flags value must be 0x06 (General Discoverable Mode + BR/EDR Not Supported).
	// - Use AdvertisementDataType::kFlags and AdvertisementDataType::kCompleteLocalName.
	// - The builder must be built before accessing its raw payload bytes.


	c7222::AdvertisementDataBuilder builder;

    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kFlags,
        std::vector<std::uint8_t>{0x06}
    ));

    std::vector<std::uint8_t> name_data(device_name.begin(), device_name.end());
    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kCompleteLocalName,
        name_data
    ));

    builder.Build();
    return builder.data();

	
}

std::vector<std::uint8_t> BuildTxPowerAndManufacturerAdvertisement(std::uint16_t company_id,
																   std::int8_t tx_power_dbm,
																   std::uint8_t counter) {
	
	// TODO: Create an AdvertisementDataBuilder, add Tx Power + Manufacturer Specific.
	//
	// Requirements:
	// - Tx Power Level payload is exactly 1 byte (tx_power_dbm).
	// - Manufacturer payload is: company_id (little-endian, 2 bytes) + counter (1 byte).
	// - Use AdvertisementDataType::kTxPowerLevel and AdvertisementDataType::kManufacturerSpecific.
	c7222::AdvertisementDataBuilder builder;

    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kTxPowerLevel,
        std::vector<std::uint8_t>{static_cast<std::uint8_t>(tx_power_dbm)}
    ));

    std::vector<std::uint8_t> mfg_data;
    mfg_data.push_back(static_cast<std::uint8_t>(company_id & 0xFF));       
    mfg_data.push_back(static_cast<std::uint8_t>((company_id >> 8) & 0xFF)); 
    mfg_data.push_back(counter);                                             

    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kManufacturerSpecific,
        mfg_data
    ));

    builder.Build();
    return builder.data();
	
}

std::vector<std::uint8_t> BuildUuidAndServiceDataAdvertisement(std::uint16_t service_uuid,
															   std::uint16_t sensor_value) {
	
	// TODO: Create an AdvertisementDataBuilder, add UUID list + Service Data.
	//
	// Requirements:
	// - Complete list 16-bit UUIDs contains exactly one UUID (service_uuid).
	// - Service Data 16-bit UUID contains: service_uuid + sensor_value (little-endian).
	// - Use AdvertisementDataType::kCompleteList16BitUuid and AdvertisementDataType::kServiceData16BitUuid.
	c7222::AdvertisementDataBuilder builder;

    std::vector<std::uint8_t> uuid_data;
    uuid_data.push_back(static_cast<std::uint8_t>(service_uuid & 0xFF));        
    uuid_data.push_back(static_cast<std::uint8_t>((service_uuid >> 8) & 0xFF)); 

    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kCompleteList16BitUuid,
        uuid_data
    ));

    std::vector<std::uint8_t> svc_data;
    svc_data.push_back(static_cast<std::uint8_t>(service_uuid & 0xFF));       
    svc_data.push_back(static_cast<std::uint8_t>((service_uuid >> 8) & 0xFF));  
    svc_data.push_back(static_cast<std::uint8_t>(sensor_value & 0xFF));         
    svc_data.push_back(static_cast<std::uint8_t>((sensor_value >> 8) & 0xFF)); 

    builder.Add(c7222::AdvertisementData(
        c7222::AdvertisementDataType::kServiceData16BitUuid,
        svc_data
    ));

    builder.Build();
    return builder.data();
	
}
