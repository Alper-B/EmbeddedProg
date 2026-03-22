/**
 * @file service_builder.hpp
 * @brief Service-construction task declarations for Module 8.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.3: Service construction with real Characteristic objects.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#ifndef SERVICE_BUILDER_HPP_
#define SERVICE_BUILDER_HPP_

#include <cstdint>
#include <vector>

#include "service.hpp"

/**
 * @brief Build a primary Board Status service using the real c7222 GATT API.
 *
 * The returned service must use UUID ``0xFFF0`` and declaration handle
 * ``0x0001``. It must contain these characteristics in this order:
 *
 * 1. LED State
 *    - UUID ``0xFFF1``
 *    - declaration handle ``0x0002``
 *    - value handle ``0x0003``
 *    - properties: Read and Write
 *    - initial value: ``{0x00}``
 *    - user description handle ``0x0004``
 *    - user description text: ``"LED State"``
 *
 * 2. Button Count
 *    - UUID ``0xFFF2``
 *    - declaration handle ``0x0005``
 *    - value handle ``0x0006``
 *    - properties: Read and Notify
 *    - initial value: ``{0x00, 0x00}``
 *    - CCCD handle ``0x0007``
 *    - user description handle ``0x0008``
 *    - user description text: ``"Button Count"``
 *
 * 3. Temperature
 *    - UUID ``0xFFF3``
 *    - declaration handle ``0x0009``
 *    - value handle ``0x000A``
 *    - properties: Read
 *    - initial value: ``{0x19}``
 *    - user description handle ``0x000B``
 *    - user description text: ``"Temperature"``
 *
 * Use the real ``c7222::Service`` and ``c7222::Characteristic`` APIs:
 * ``CreateCharacteristic()``, ``SetValue()``, ``EnableCCCD()``, and
 * ``SetUserDescription()``.
 *
 * @return Fully configured Board Status service.
 */
c7222::Service CreateBoardStatusService();

/**
 * @brief Update one characteristic value in a service by UUID.
 *
 * This function must locate the characteristic with ``FindCharacteristicByUuid``.
 * If the characteristic does not exist, return ``false``.
 *
 * In this task, characteristics are created with ``CreateCharacteristic()``,
 * which gives them owned runtime value storage. After locating the
 * characteristic, update it with ``Characteristic::SetValue``.
 *
 * @param service Service that owns the target characteristic
 * @param uuid Characteristic UUID to search for
 * @param value New value bytes
 * @return ``true`` if the characteristic was found and updated, otherwise ``false``.
 */
bool UpdateCharacteristicValue(c7222::Service& service,
                               const c7222::Uuid& uuid,
                               const std::vector<std::uint8_t>& value);

/**
 * @brief Return all characteristic value handles in service order.
 *
 * The returned vector must contain one handle per characteristic, using the
 * order in which the characteristics were added to the service.
 *
 * @param service Service to inspect
 * @return Ordered vector of characteristic value handles.
 */
std::vector<std::uint16_t> CollectValueHandles(const c7222::Service& service);

#endif  // SERVICE_BUILDER_HPP_
