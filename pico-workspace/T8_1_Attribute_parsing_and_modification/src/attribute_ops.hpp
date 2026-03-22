/**
 * @file attribute_ops.hpp
 * @brief Attribute parsing and modification task declarations for Module 8.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.1: Attribute Parsing and Modification.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#ifndef ATTRIBUTE_OPS_HPP_
#define ATTRIBUTE_OPS_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "attribute.hpp"

/**
 * @brief Classify an attribute by its ATT/GATT role.
 *
 * Return one of these exact strings:
 * - ``"primary_service"``
 * - ``"characteristic_declaration"``
 * - ``"descriptor"``
 * - ``"value"``
 *
 * @param attr Attribute to classify.
 * @return Classification string.
 */
std::string ClassifyAttribute(const c7222::Attribute& attr);

/**
 * @brief Read at most ``max_bytes`` from an attribute starting at ``offset``.
 *
 * Use the attribute's read path so the solution works for both static and
 * callback-backed attributes.
 *
 * @param attr Attribute to read.
 * @param offset Byte offset into the attribute value.
 * @param max_bytes Maximum number of bytes to return.
 * @return Value bytes read from the attribute.
 */
std::vector<std::uint8_t> ReadAttributeSlice(const c7222::Attribute& attr,
											 std::uint16_t offset,
											 std::uint16_t max_bytes);

/**
 * @brief Attempt to write a new value into an attribute.
 *
 * The function must use the attribute's write path. For writable dynamic
 * attributes, the stored value must update. For non-writable attributes, the
 * correct ATT error must be returned.
 *
 * @param attr Attribute to modify.
 * @param new_value Bytes to write starting at offset 0.
 * @return BLE/ATT status code from the write operation.
 */
c7222::BleError WriteAttributeValue(c7222::Attribute& attr,
									const std::vector<std::uint8_t>& new_value);

#endif  // ATTRIBUTE_OPS_HPP_
