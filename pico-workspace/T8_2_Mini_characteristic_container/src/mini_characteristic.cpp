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
                                       const std::string& user_description) {
    

    std::uint8_t decl_props = kGattPropertyRead;
    if (enable_notifications) {
        decl_props |= kGattPropertyNotify;
    }

    declaration_ = c7222::Attribute::CharacteristicDeclaration(
        decl_props, value_handle, value_uuid, declaration_handle);

    std::uint16_t value_attr_props = 
        static_cast<std::uint16_t>(c7222::Attribute::Properties::kRead) | 
        static_cast<std::uint16_t>(c7222::Attribute::Properties::kDynamic);
        
    value_ = c7222::Attribute(value_uuid, value_attr_props, value_handle);

    std::uint16_t current_handle = value_handle + 1;

    if (enable_notifications) {
        cccd_ = std::make_unique<c7222::Attribute>(
            c7222::Attribute::ClientCharacteristicConfiguration(0x0000, current_handle)
        );
        current_handle++;
    }

    if (!user_description.empty()) {
        user_description_ = std::make_unique<c7222::Attribute>(
            c7222::Attribute::CharacteristicUserDescription(user_description, current_handle)
        );
    }
}

std::vector<const c7222::Attribute*> MiniCharacteristic::GetAllAttributes() const {
    std::vector<const c7222::Attribute*> attributes;
    
    attributes.push_back(&declaration_);
    attributes.push_back(&value_);
    
    if (cccd_) {
        attributes.push_back(cccd_.get());
    }
    
    if (user_description_) {
        attributes.push_back(user_description_.get());
    }
    
    return attributes;
}

bool MiniCharacteristic::SetValue(const std::vector<std::uint8_t>& value) {
    return value_.SetValue(value);
}
