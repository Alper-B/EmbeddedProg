#include "attribute_ops.hpp"

/**
 * @file attribute_ops.cpp
 * @brief Task template implementation for Module 8 attribute parsing.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.1: Attribute Parsing and Modification.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

std::string ClassifyAttribute(const c7222::Attribute& attr) {
    if (c7222::Attribute::IsPrimaryServiceDeclaration(attr)) {
        return "primary_service";
    } else if (c7222::Attribute::IsCharacteristicDeclaration(attr)) {
        return "characteristic_declaration";
    } else if (c7222::Attribute::IsDescriptor(attr)) {
        return "descriptor";
    }
    
    return "value";
}

std::vector<std::uint8_t> ReadAttributeSlice(const c7222::Attribute& attr,
                                             std::uint16_t offset,
                                             std::uint16_t max_bytes) {
    std::vector<std::uint8_t> buffer(max_bytes);
    
    std::uint16_t result = attr.InvokeReadCallback(offset, buffer.data(), max_bytes);
    
    if (result > 0xFE00) {
        return {}; 
    }
    
    buffer.resize(result);
    return buffer;
}

c7222::BleError WriteAttributeValue(c7222::Attribute& attr,
                                    const std::vector<std::uint8_t>& new_value) {
    return attr.InvokeWriteCallback(0, new_value.data(), new_value.size());
}
