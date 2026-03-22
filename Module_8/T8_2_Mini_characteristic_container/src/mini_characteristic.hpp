/**
 * @file mini_characteristic.hpp
 * @brief Characteristic-like container task declarations for Module 8.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.2: Mini Characteristic Container.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#ifndef MINI_CHARACTERISTIC_H_
#define MINI_CHARACTERISTIC_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "attribute.hpp"

/**
 * @brief Small characteristic-like container built from multiple ATT attributes.
 *
 * This class models the core idea behind a GATT characteristic without
 * implementing a full BLE stack abstraction. One logical characteristic is
 * represented by a small ordered set of attributes:
 * - a mandatory characteristic declaration attribute,
 * - a mandatory characteristic value attribute,
 * - an optional client characteristic configuration descriptor (CCCD), and
 * - an optional user description descriptor.
 *
 * The task in this exercise is to assemble those attributes correctly and keep
 * them in ATT database order.
 *
 * Reference:
 * - std::unique_ptr:
 *   https://cplusplus.com/reference/memory/unique_ptr/
 * - <memory>:
 *   https://cplusplus.com/reference/memory/
 */
class MiniCharacteristic {
   public:
	/**
	 * @brief Construct a characteristic-like container from multiple attributes.
	 *
	 * The constructor must build the internal attributes in ATT database order:
	 * - create a characteristic declaration attribute at declaration_handle,
	 * - create a dynamic readable characteristic value attribute at value_handle,
	 * - optionally create a CCCD at the next handle when notifications are enabled,
	 * - optionally create a user description descriptor after the value or CCCD.
	 *
	 * @param value_uuid UUID of the characteristic value attribute
	 * @param declaration_handle Handle of the characteristic declaration attribute
	 * @param value_handle Handle of the characteristic value attribute
	 * @param enable_notifications If true, also create a CCCD
	 * @param user_description Optional user description string for a descriptor
	 */
	MiniCharacteristic(const c7222::Uuid& value_uuid,
					   std::uint16_t declaration_handle,
					   std::uint16_t value_handle,
					   bool enable_notifications,
					   const std::string& user_description);

	/**
	 * @brief Get the characteristic declaration attribute.
	 * @return Reference to the declaration attribute
	 */
	const c7222::Attribute& GetDeclarationAttribute() const { return declaration_; }

	/**
	 * @brief Get the characteristic value attribute.
	 * @return Const reference to the value attribute
	 */
	const c7222::Attribute& GetValueAttribute() const { return value_; }

	/**
	 * @brief Get the CCCD if notifications are enabled.
	 * @return Pointer to the CCCD, or nullptr if no CCCD exists
	 */
	const c7222::Attribute* GetCccdAttribute() const {
		return cccd_.get();
	}

	/**
	 * @brief Get the user description descriptor if it exists.
	 * @return Pointer to the user description descriptor, or nullptr
	 */
	const c7222::Attribute* GetUserDescriptionAttribute() const {
		return user_description_.get();
	}

	/**
	 * @brief Return all existing attributes in ATT database order.
	 */
	std::vector<const c7222::Attribute*> GetAllAttributes() const;

	/**
	 * @brief Update the dynamic value attribute.
	 * @param value New characteristic value bytes
	 * @return true on success, false if the value attribute rejects the update.
	 */
	bool SetValue(const std::vector<std::uint8_t>& value);

   private:
	/** @brief Characteristic declaration attribute. */
	c7222::Attribute declaration_;
	/** @brief Dynamic characteristic value attribute. */
	c7222::Attribute value_;
	/** @brief Optional CCCD used when notifications are enabled. */
	std::unique_ptr<c7222::Attribute> cccd_;
	/** @brief Optional human-readable user description descriptor. */
	std::unique_ptr<c7222::Attribute> user_description_;
};

#endif  // MINI_CHARACTERISTIC_H_
