/**
 * @file service_builder.cpp
 * @brief Student implementation file for Module 8 Task 8.3.
 *
 * Build a ``c7222::Service`` using real ``c7222::Characteristic`` objects.
 * The task uses fixed UUIDs, handles, properties, and initial values so the
 * service layout is deterministic and easy to verify automatically.
 *
 * Required functions:
 * - ``CreateBoardStatusService()``
 * - ``UpdateCharacteristicValue(...)``
 * - ``CollectValueHandles(...)``
 */

#include "service_builder.hpp"

#include <cstdint>
#include <vector>
c7222::Service CreateBoardStatusService() {
    c7222::Service service(c7222::Uuid(0xFFF0),
                           c7222::Service::ServiceType::kPrimary,
                           0x0001);

    std::uint8_t led_props = static_cast<std::uint8_t>(c7222::Characteristic::Properties::kRead) | 
                             static_cast<std::uint8_t>(c7222::Characteristic::Properties::kWrite);
    auto& led_char = service.CreateCharacteristic(c7222::Uuid(0xFFF1), led_props, 0x0002, 0x0003);
    led_char.SetValue(std::vector<std::uint8_t>{0x00});
    led_char.SetUserDescription("LED State").SetHandle(0x0004);

    std::uint8_t btn_props = static_cast<std::uint8_t>(c7222::Characteristic::Properties::kRead) | 
                             static_cast<std::uint8_t>(c7222::Characteristic::Properties::kNotify);
    auto& btn_char = service.CreateCharacteristic(c7222::Uuid(0xFFF2), btn_props, 0x0005, 0x0006);
    btn_char.SetValue(std::vector<std::uint8_t>{0x00, 0x00});
    btn_char.EnableCCCD().SetHandle(0x0007);
    btn_char.SetUserDescription("Button Count").SetHandle(0x0008);

    std::uint8_t temp_props = static_cast<std::uint8_t>(c7222::Characteristic::Properties::kRead);
    auto& temp_char = service.CreateCharacteristic(c7222::Uuid(0xFFF3), temp_props, 0x0009, 0x000A);
    temp_char.SetValue(std::vector<std::uint8_t>{0x19});
    temp_char.SetUserDescription("Temperature").SetHandle(0x000B);

    return service;
}

bool UpdateCharacteristicValue(c7222::Service& service,
                               const c7222::Uuid& uuid,
                               const std::vector<std::uint8_t>& value) {
    c7222::Characteristic* characteristic = service.FindCharacteristicByUuid(uuid);
    
    if (!characteristic) {
        return false;
    }
    
    return characteristic->SetValue(value);
}

std::vector<std::uint16_t> CollectValueHandles(const c7222::Service& service) {
    std::vector<std::uint16_t> handles;
    
    for (const auto& characteristic : service.GetCharacteristics()) {
        handles.push_back(characteristic.GetValueHandle());
    }
    
    return handles;
}