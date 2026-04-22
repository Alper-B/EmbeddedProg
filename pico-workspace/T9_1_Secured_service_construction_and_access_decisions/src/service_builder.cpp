#include "service_builder.hpp"
#include <vector>
#include <memory>

// Assumes standard c7222 namespace enums and types based on the API description
using namespace c7222;

std::unique_ptr<Service> CreateSecureBoardStatusService() {
    // Create Primary Service: UUID 0xFFF0, declaration handle 0x0001
    auto service = std::make_unique<Service>(Uuid(0xFFF0), 0x0001);

    // ------------------------------------------------------------------
    // Characteristic 1: LED State
    // ------------------------------------------------------------------
    auto* led_char = service->CreateCharacteristic(
        Uuid(0xFFF1), 
        0x0002, // Declaration handle
        0x0003, // Value handle
        Attribute::Property::kRead | Attribute::Property::kWrite
    );
    led_char->SetValue(std::vector<uint8_t>{0x00});
    led_char->SetWriteSecurityLevel(Characteristic::SecurityLevel::kAuthenticationRequired);
    led_char->SetUserDescription("LED State", 0x0004);

    // ------------------------------------------------------------------
    // Characteristic 2: Button Count
    // ------------------------------------------------------------------
    auto* button_char = service->CreateCharacteristic(
        Uuid(0xFFF2), 
        0x0005, // Declaration handle
        0x0006, // Value handle
        Attribute::Property::kRead | Attribute::Property::kNotify
    );
    button_char->SetValue(std::vector<uint8_t>{0x00, 0x00});
    button_char->SetReadSecurityLevel(Characteristic::SecurityLevel::kEncryptionRequired);
    button_char->EnableCCCD(0x0007); // Optional handle argument depending on exact API signature, adjust if it takes no arguments
    button_char->SetUserDescription("Button Count", 0x0008);

    // ------------------------------------------------------------------
    // Characteristic 3: Control Mode
    // ------------------------------------------------------------------
    auto* control_char = service->CreateCharacteristic(
        Uuid(0xFFF3), 
        0x0009, // Declaration handle
        0x000A, // Value handle
        Attribute::Property::kRead | Attribute::Property::kWrite
    );
    control_char->SetValue(std::vector<uint8_t>{0x01});
    control_char->SetWriteSecurityLevel(Characteristic::SecurityLevel::kAuthorizationRequired);
    control_char->SetUserDescription("Control Mode", 0x000B);

    return service;
}

std::vector<uint16_t> CollectProtectedValueHandles(const Service& service) {
    std::vector<uint16_t> protected_handles;

    for (const auto* charac : service.GetCharacteristics()) {
        // Check if either read or write operations require elevated security
        bool requires_protection = 
            (charac->GetReadSecurityLevel() != Characteristic::SecurityLevel::kNone) ||
            (charac->GetWriteSecurityLevel() != Characteristic::SecurityLevel::kNone);

        if (requires_protection) {
            protected_handles.push_back(charac->GetValueHandle());
        }
    }

    return protected_handles;
}

AccessDecision EvaluateReadAccess(const Characteristic* characteristic, uint8_t security_level, bool is_authorized) {
    if (characteristic == nullptr) {
        return AccessDecision::kNotPermitted;
    }

    // Check if the characteristic actually supports Read operations
    if ((characteristic->GetProperties() & Attribute::Property::kRead) == 0) {
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

    // Check if the characteristic actually supports Write operations
    if ((characteristic->GetProperties() & Attribute::Property::kWrite) == 0) {
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