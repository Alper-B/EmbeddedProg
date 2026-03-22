#include "mini_characteristic.hpp"

/**
 * @file mini_characteristic.cpp
 * @brief Task template implementation for Module 8 mini characteristic container.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.2: Mini Characteristic Container.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 *
 * Task summary:
 * - Build one logical characteristic from multiple Attribute objects.
 * - Create a Characteristic Declaration attribute at declaration_handle.
 * - Create a dynamic readable Characteristic Value attribute at value_handle.
 * - If notifications are enabled, create a CCCD at the next handle.
 * - If user_description is not empty, create a User Description descriptor at
 *   the next free handle.
 * - Return all existing attributes in ATT database order.
 * - Implement SetValue() by updating the dynamic value attribute.
 */

namespace {
constexpr std::uint8_t kGattPropertyRead = 0x02;
constexpr std::uint8_t kGattPropertyNotify = 0x10;
}

MiniCharacteristic::MiniCharacteristic(const c7222::Uuid& value_uuid,
									   std::uint16_t declaration_handle,
									   std::uint16_t value_handle,
									   bool enable_notifications,
									   const std::string& user_description)
	
	{
	// TODO: Build the internal attributes using the factory helpers in
	// Attribute:
	// - declaration_ must describe the characteristic value UUID and handle.
	// - value_ must use value_uuid, value_handle, and dynamic readable storage.
	// - if enable_notifications is true, create cccd_ at value_handle + 1.
	// - if user_description is non-empty, create user_description_ at the next
	//   free handle after the value or CCCD.
	(void)value_uuid;
	(void)declaration_handle;
	(void)value_handle;
	(void)enable_notifications;
	(void)user_description;
	
}

std::vector<const c7222::Attribute*> MiniCharacteristic::GetAllAttributes() const {
	
	// TODO: Return declaration_, value_, and any optional descriptor
	// attributes in ATT database order.
	return {};
	
}

bool MiniCharacteristic::SetValue(const std::vector<std::uint8_t>& value) {
	
	// TODO: Forward the update to value_ and return the result.
	(void)value;
	return false;
	
}
