#include "service_builder.hpp"
#include <vector>

using namespace c7222;

Service CreateSecureBoardStatusService() {
    // Create Primary Service: UUID 0xFFF0, ServiceType::kPrimary, declaration handle 0x0001
    Service service(Uuid(0xFFF0), Service::ServiceType::kPrimary, 0x0001);

    // ------------------------------------------------------------------
    // Characteristic 1: LED State
    // ------------------------------------------------------------------
    uint8_t led_props = static_cast<uint8_t>(Characteristic::Properties::kRead) | 
                        static_cast<uint8_t>(Characteristic::Properties::kWrite);
    auto& led_char = service.CreateCharacteristic(
        Uuid(0xFFF1), 
        led_props,
        0x0002, // Declaration handle
        0x0003  // Value handle
    );
    led_char.SetValue(std::vector<uint8_t>{0x00});
    led_char.SetWriteSecurityLevel(Characteristic::SecurityLevel::kAuthenticationRequired);
    led_char.SetUserDescription("LED State").SetHandle(0x0004);

    // ------------------------------------------------------------------
    // Characteristic 2: Button Count
    // ------------------------------------------------------------------
    uint8_t button_props = static_cast<uint8_t>(Characteristic::Properties::kRead) | 
                           static_cast<uint8_t>(Characteristic::Properties::kNotify);
    auto& button_char = service.CreateCharacteristic(
        Uuid(0xFFF2), 
        button_props,
        0x0005, // Declaration handle
        0x0006  // Value handle
    );
    button_char.SetValue(std::vector<uint8_t>{0x00, 0x00});
    button_char.SetReadSecurityLevel(Characteristic::SecurityLevel::kEncryptionRequired);
    button_char.EnableCCCD().SetHandle(0x0007); 
    button_char.SetUserDescription("Button Count").SetHandle(0x0008);

    // ------------------------------------------------------------------
    // Characteristic 3: Control Mode
    // ------------------------------------------------------------------
    uint8_t control_props = static_cast<uint8_t>(Characteristic::Properties::kRead) | 
                            static_cast<uint8_t>(Characteristic::Properties::kWrite);
    auto& control_char = service.CreateCharacteristic(
        Uuid(0xFFF3), 
        control_props,
        0x0009, // Declaration handle
        0x000A  // Value handle
    );
    control_char.SetValue(std::vector<uint8_t>{0x01});
    control_char.SetWriteSecurityLevel(Characteristic::SecurityLevel::kAuthorizationRequired);
    control_char.SetUserDescription("Control Mode").SetHandle(0x000B);

    return service;
}

std::vector<uint16_t> CollectProtectedValueHandles(const Service& service) {
    std::vector<uint16_t> protected_handles;

    for (const auto& charac : service.GetCharacteristics()) {
        bool requires_protection = 
            (charac.GetReadSecurityLevel() != Characteristic::SecurityLevel::kNone) ||
            (charac.GetWriteSecurityLevel() != Characteristic::SecurityLevel::kNone);

        if (requires_protection) {
            protected_handles.push_back(charac.GetValueHandle());
        }
    }

    return protected_handles;
}

AccessDecision EvaluateReadAccess(const Characteristic* characteristic, uint8_t security_level, bool is_authorized) {
    if (characteristic == nullptr) {
        return AccessDecision::kNotPermitted;
    }

    // Rely on the API's helper method rather than manual bitmasking
    if (!characteristic->CanRead()) {
        return AccessDecision::kNotPermitted;
    }

    auto sec_req = characteristic->GetReadSecurityLevel();

    if (sec_req == Characteristic::SecurityLevel::kAuthorizationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        if (!is_authorized) return AccessDecision::kAuthorizationRequired;
    } 
    else if (sec_req == Characteristic::SecurityLevel::kAuthenticationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
    } 
    else if (sec_req == Characteristic::SecurityLevel::kEncryptionRequired) {
        if (security_level < 1) return AccessDecision::kSecurityUpgradeRequired;
    }

    return AccessDecision::kAllowed;
}

AccessDecision EvaluateWriteAccess(const Characteristic* characteristic, uint8_t security_level, bool is_authorized) {
    if (characteristic == nullptr) {
        return AccessDecision::kNotPermitted;
    }

    // Rely on the API's helper method rather than manual bitmasking
    if (!characteristic->CanWrite() && !characteristic->CanWriteWithoutResponse()) {
        return AccessDecision::kNotPermitted;
    }

    auto sec_req = characteristic->GetWriteSecurityLevel();

    if (sec_req == Characteristic::SecurityLevel::kAuthorizationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
        if (!is_authorized) return AccessDecision::kAuthorizationRequired;
    } 
    else if (sec_req == Characteristic::SecurityLevel::kAuthenticationRequired) {
        if (security_level < 2) return AccessDecision::kSecurityUpgradeRequired;
    } 
    else if (sec_req == Characteristic::SecurityLevel::kEncryptionRequired) {
        if (security_level < 1) return AccessDecision::kSecurityUpgradeRequired;
    }

    return AccessDecision::kAllowed;
}