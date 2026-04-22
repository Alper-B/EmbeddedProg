/**
 * @file service_builder.hpp
 * @brief Module 9 declarations for secured service planning.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222 Module 9 Task 9.1.
 * It focuses on building one service with real Characteristic objects and
 * evaluating attribute access decisions from the configured security levels.
 */

#ifndef SERVICE_BUILDER_HPP_
#define SERVICE_BUILDER_HPP_

#include <cstdint>
#include <vector>

#include "service.hpp"

/**
 * @brief Result of evaluating one ATT operation against one characteristic.
 *
 * ``security_level`` is interpreted as:
 *
 * - ``0``: no link security
 * - ``1``: encrypted link
 * - ``2``: authenticated and encrypted link
 */
enum class AccessDecision : std::uint8_t {
	kAllowed = 0,
	kSecurityUpgradeRequired,
	kAuthorizationRequired,
	kNotPermitted,
};

/**
 * @brief Build one secured custom service using the real c7222 GATT API.
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
 *    - write security: authentication required
 *    - user description handle ``0x0004``
 *    - user description text: ``"LED State"``
 *
 * 2. Button Count
 *    - UUID ``0xFFF2``
 *    - declaration handle ``0x0005``
 *    - value handle ``0x0006``
 *    - properties: Read and Notify
 *    - initial value: ``{0x00, 0x00}``
 *    - read security: encryption required
 *    - CCCD handle ``0x0007``
 *    - user description handle ``0x0008``
 *    - user description text: ``"Button Count"``
 *
 * 3. Control Mode
 *    - UUID ``0xFFF3``
 *    - declaration handle ``0x0009``
 *    - value handle ``0x000A``
 *    - properties: Read and Write
 *    - initial value: ``{0x01}``
 *    - write security: authorization required
 *    - user description handle ``0x000B``
 *    - user description text: ``"Control Mode"``
 *
 * Use the real ``c7222::Service`` and ``c7222::Characteristic`` APIs:
 * ``CreateCharacteristic()``, ``SetValue()``, ``EnableCCCD()``,
 * ``SetUserDescription()``, ``SetReadSecurityLevel()``, and
 * ``SetWriteSecurityLevel()``.
 *
 * Standard attribute details in this task:
 *
 * - The Characteristic Declaration attribute is created automatically by
 *   ``CreateCharacteristic()``. It uses the standard Characteristic
 *   Declaration type (UUID ``0x2803``) and is read-only metadata.
 * - The characteristic value attribute stores the properties listed above
 *   for each task characteristic.
 * - The CCCD is created automatically by ``EnableCCCD()`` when the
 *   characteristic supports notifications or indications. It uses the
 *   standard CCCD type (UUID ``0x2902``) and the standard descriptor
 *   properties ``Read | Write | Dynamic``.
 * - The Characteristic User Description descriptor is created by
 *   ``SetUserDescription()``. In this task it is a read-only descriptor.
 *
 * @return Fully configured secured custom service.
 */
c7222::Service CreateSecureBoardStatusService();

/**
 * @brief Return value handles whose characteristic requires link security.
 *
 * The returned vector must contain the value handles of all characteristics
 * that require encryption, authentication, or authorization for at least one
 * ATT operation. Preserve the insertion order used in the service.
 *
 * @param service Service to inspect.
 * @return Ordered vector of protected value handles.
 */
std::vector<std::uint16_t> CollectProtectedValueHandles(
	const c7222::Service& service);

/**
 * @brief Evaluate whether one characteristic read should succeed.
 *
 * This helper must:
 *
 * - locate the characteristic by UUID,
 * - reject unsupported or missing reads with ``AccessDecision::kNotPermitted``,
 * - require ``security_level >= 1`` for encrypted reads,
 * - require ``security_level >= 2`` for authenticated reads, and
 * - require both ``security_level >= 2`` and
 *   ``authorization_granted == true`` for authorized reads.
 *
 * @param service Service that owns the characteristic.
 * @param uuid Characteristic UUID to search for.
 * @param security_level Current connection security level.
 * @param authorization_granted Whether application-level authorization was
 * granted for the connection.
 * @return Access decision for the read operation.
 */
AccessDecision EvaluateReadAccess(const c7222::Service& service,
								  const c7222::Uuid& uuid,
								  std::uint8_t security_level,
								  bool authorization_granted);

/**
 * @brief Evaluate whether one characteristic write should succeed.
 *
 * The decision rules are the same as in ``EvaluateReadAccess(...)``, but they
 * must use the write property and write security level of the characteristic.
 *
 * @param service Service that owns the characteristic.
 * @param uuid Characteristic UUID to search for.
 * @param security_level Current connection security level.
 * @param authorization_granted Whether application-level authorization was
 * granted for the connection.
 * @return Access decision for the write operation.
 */
AccessDecision EvaluateWriteAccess(const c7222::Service& service,
								   const c7222::Uuid& uuid,
								   std::uint8_t security_level,
								   bool authorization_granted);

#endif  // SERVICE_BUILDER_HPP_
