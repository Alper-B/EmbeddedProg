/**
 * @file service_builder.cpp
 * @brief Student implementation file for Module 8 Task 8.3.
 *
 * Build a ``c7222::Service`` using real ``c7222::Characteristic`` objects.
 * The task uses fixed UUIDs, handles, properties, and initial values so the
 * service layout is deterministic and easy to verify automatically.
 *
 * Required functions:
 * - ``CreateBoardStatusService()``
 * - ``UpdateCharacteristicValue(...)``
 * - ``CollectValueHandles(...)``
 */

#include "service_builder.hpp"

#include <cstdint>
#include <vector>

c7222::Service CreateBoardStatusService() {
	
	// TODO: Build the primary Board Status service exactly as specified.
	// Use the real Service and Characteristic APIs:
	// - CreateCharacteristic(...)
	// - SetValue(...)
	// - EnableCCCD()
	// - SetUserDescription()
	return c7222::Service(c7222::Uuid(0xFFF0),
	                      c7222::Service::ServiceType::kPrimary,
	                      0x0001);
	
}

bool UpdateCharacteristicValue(c7222::Service& service,
                               const c7222::Uuid& uuid,
                               const std::vector<std::uint8_t>& value) {
	
	// TODO: Find the characteristic by UUID.
	// - Return false if it does not exist.
	// - In this task, characteristics created with CreateCharacteristic(...)
	//   use owned runtime storage, so Characteristic::SetValue(...) is the
	//   correct update path.
	// - Update the found characteristic value and return the result.
	(void)service;
	(void)uuid;
	(void)value;
	return false;
	
}

std::vector<std::uint16_t> CollectValueHandles(const c7222::Service& service) {
	
	// TODO: Iterate through the service characteristics in insertion order and
	// collect their value handles.
	(void)service;
	return {};
	
}
