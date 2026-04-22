/**
 * @file service_builder.cpp
 * @brief Student implementation file for Module 9 Task 9.1.
 *
 * Build a secured ``c7222::Service`` using real ``c7222::Characteristic``
 * objects and evaluate attribute access decisions from the configured
 * characteristic security levels.
 */

#include "service_builder.hpp"

#include <cstdint>
#include <vector>

c7222::Service CreateSecureBoardStatusService() {
    // Build the secured custom service with UUID 0xFFF0 and declaration handle 0x0001
    c7222::Service svc(c7222::Uuid(0xFFF0), c7222::Service::ServiceType::kPrimary, 0x0001);

    // 1. LED State Characteristic
    uint8_t led_props = static_cast<uint8_t>(c7222::Characteristic::Properties::kRead) |
                        static_cast<uint8_t>(c7222::Characteristic::Properties::kWrite);
    auto& led_char = svc.CreateCharacteristic(c7222::Uuid(0xFFF1), led_props, 0x0002, 0x0003);
    uint8_t led_val[] = {0x00};
    led_char.SetValue(led_val, sizeof(led_val));
    led_char.SetWriteSecurityLevel(c7222::Characteristic::SecurityLevel::kAuthenticationRequired);
    led_char.SetUserDescription("LED State").SetHandle(0x0004);

    // 2. Button Count Characteristic
    uint8_t btn_props = static_cast<uint8_t>(c7222::Characteristic::Properties::kRead) |
                        static_cast<uint8_t>(c7222::Characteristic::Properties::kNotify);
    auto& btn_char = svc.CreateCharacteristic(c7222::Uuid(0xFFF2), btn_props, 0x0005, 0x0006);
    uint8_t btn_val[] = {0x00, 0x00};
    btn_char.SetValue(btn_val, sizeof(btn_val));
    btn_char.SetReadSecurityLevel(c7222::Characteristic::SecurityLevel::kEncryptionRequired);
    btn_char.EnableCCCD().SetHandle(0x0007);
    btn_char.SetUserDescription("Button Count").SetHandle(0x0008);

    // 3. Control Mode Characteristic
    uint8_t ctrl_props = static_cast<uint8_t>(c7222::Characteristic::Properties::kRead) |
                         static_cast<uint8_t>(c7222::Characteristic::Properties::kWrite);
    auto& ctrl_char = svc.CreateCharacteristic(c7222::Uuid(0xFFF3), ctrl_props, 0x0009, 0x000A);
    uint8_t ctrl_val[] = {0x01};
    ctrl_char.SetValue(ctrl_val, sizeof(ctrl_val));
    ctrl_char.SetWriteSecurityLevel(c7222::Characteristic::SecurityLevel::kAuthorizationRequired);
    ctrl_char.SetUserDescription("Control Mode").SetHandle(0x000B);

    return svc;
}

std::vector<std::uint16_t> CollectProtectedValueHandles(const c7222::Service& service) {
    std::vector<std::uint16_t> protected_handles;
    
    // Iterate over characteristics and identify those requiring elevated access
    for (const auto& ch : service.GetCharacteristics()) {
        if (ch.RequiresEncryption() || ch.RequiresAuthentication() || ch.RequiresAuthorization()) {
            protected_handles.push_back(ch.GetValueHandle());
        }
    }
    
    return protected_handles;
}

AccessDecision EvaluateReadAccess(const c7222::Service& service,
                                  const c7222::Uuid& uuid,
                                  std::uint8_t security_level,
                                  bool authorization_granted) {
                                      
    const c7222::Characteristic* ch = service.FindCharacteristicByUuid(uuid);
    
    // Check if characteristic exists and supports reading
    if (!ch || !ch->CanRead()) {
        return AccessDecision::kNotPermitted;
    }

    c7222::Characteristic::SecurityLevel req_level = ch->GetReadSecurityLevel();

    if (req_level == c7222::Characteristic::SecurityLevel::kNone) {
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kEncryptionRequired) {
        if (security_level < 1) return AccessDecision::kSecurityUpgradeRequired;
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kAuthenticationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kAuthorizationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        if (!authorization_granted) return AccessDecision::kAuthorizationRequired;
        return AccessDecision::kAllowed;
    }

    return AccessDecision::kNotPermitted;
}

AccessDecision EvaluateWriteAccess(const c7222::Service& service,
                                   const c7222::Uuid& uuid,
                                   std::uint8_t security_level,
                                   bool authorization_granted) {
                                       
    const c7222::Characteristic* ch = service.FindCharacteristicByUuid(uuid);
    
    // Check if characteristic exists and supports writing (with or without response)
    if (!ch || (!ch->CanWrite() && !ch->CanWriteWithoutResponse())) {
        return AccessDecision::kNotPermitted;
    }

    c7222::Characteristic::SecurityLevel req_level = ch->GetWriteSecurityLevel();

    if (req_level == c7222::Characteristic::SecurityLevel::kNone) {
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kEncryptionRequired) {
        if (security_level < 1) return AccessDecision::kSecurityUpgradeRequired;
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kAuthenticationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        return AccessDecision::kAllowed;
    }
    
    if (req_level == c7222::Characteristic::SecurityLevel::kAuthorizationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        if (!authorization_granted) return AccessDecision::kAuthorizationRequired;
        return AccessDecision::kAllowed;
    }

    return AccessDecision::kNotPermitted;
}