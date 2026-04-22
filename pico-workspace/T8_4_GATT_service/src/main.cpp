/**
 * @file main.cpp
 * @brief Template implementation for the Module 8 GATT service task.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.4.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#include <cassert>
#include <cstdio>
#include <iostream>

#include "advertisement_data.hpp"
#include "attribute_server.hpp"
#include "ble.hpp"
#include "characteristic.hpp"
#include "freertos_task.hpp"
#include "gap.hpp"
#include "onboard_led.hpp"
#include "platform.hpp"

#include "gap_event_handler.hpp"
#include "app_profile.h"

namespace {

/**
 * @brief Device name used in BLE advertising packets.
 */
constexpr const char* kDeviceName = "c7222-gatt-service";

/**
 * @brief User-description texts assigned to the generated custom-service
 * characteristics at runtime.
 */
constexpr const char* kCharacteristicDescriptions[] = {
	"Characteristic 1",
	"Characteristic 2",
	"Characteristic 3",
};

/**
 * @brief Global pointer to the runtime attribute server instance.
 */
static c7222::AttributeServer* g_att_server = nullptr;

/**
 * @brief Global pointer to the on-board LED controller.
 */
static c7222::OnBoardLED* g_onboard_led = nullptr;

/**
 * @brief GAP event handler used by the BLE application.
 */
static GapEventHandler g_gap_event_handler;

/**
 * @brief FreeRTOS task object that runs the BLE application logic.
 */
static c7222::FreeRtosTask g_ble_task;

/**
 * @brief Print a short summary of the services parsed into the attribute
 * server.
 */
void PrintParsedServices() {
    if (!g_att_server) return;

    std::cout << "Parsed " << g_att_server->GetServiceCount() << " services.\n";
    
    size_t s_idx = 0;
    for (const auto& svc : g_att_server->GetServices()) {
        std::cout << "Service " << s_idx++ << ": UUID " << svc.GetUuid() 
                  << ", Char Count: " << svc.GetCharacteristicCount() << "\n";
        
        size_t c_idx = 0;
        for (const auto& chr : svc.GetCharacteristics()) {
            std::cout << "  Char " << c_idx++ << ": UUID " << chr.GetUuid();
            if (chr.HasUserDescription()) {
                std::cout << ", Description: " << chr.GetUserDescriptionText();
            }
            std::cout << ", Descriptors: " << chr.GetDescriptorCount() << "\n";
        }
    }
}

/**
 * @brief Configure and start BLE advertising after the stack is ready.
 */
void ConfigureAdvertisement() {
    auto* gap = c7222::Gap::GetInstance();
    
    c7222::AdvertisementDataBuilder builder;
    builder.add(c7222::AdvertisementDataType::kFlags,
                c7222::AdvertisementData::Flags::kLeGeneralDiscoverableMode |
                c7222::AdvertisementData::Flags::kBrEdrNotSupported);
    builder.add(c7222::AdvertisementDataType::kCompleteLocalName, kDeviceName);
    
    gap->SetAdvertisingData(builder);
    
    c7222::Gap::AdvertisementParameters params;
    gap->SetAdvertisingParameters(params);
    gap->StartAdvertising();
    
    std::cout << "Advertising configured and started.\n";
}

/**
 * @brief Assign runtime metadata to the generated custom service.
 *
 * @details This function finds the generated custom service from the parsed
 * attribute database and applies human-readable user-description strings to
 * its three characteristics when the corresponding descriptors are available.
 */
void ConfigureGeneratedService() {
    if (!g_att_server) return;
    
    for (auto& svc : g_att_server->GetServices()) {
        if (svc.GetCharacteristicCount() == 3) {
            size_t i = 0;
            for (auto& chr : svc.GetCharacteristics()) {
                if (i < 3) {
                    chr.SetUserDescriptionText(kCharacteristicDescriptions[i]);
                }
                i++;
            }
            break;
        }
    }
}

/**
 * @brief Main BLE application task.
 *
 * @param params Unused task parameter.
 */
[[noreturn]] void ble_app_task(void* /*params*/) {
    auto* ble = c7222::Ble::GetInstance();
    auto* gap = c7222::Gap::GetInstance();
    
    g_att_server = c7222::AttributeServer::GetInstance();
    g_att_server->Init(profile_data);
    
    PrintParsedServices();
    
    g_gap_event_handler.SetAttributeServer(g_att_server);
    gap->AddEventHandler(g_gap_event_handler);
    
    ConfigureGeneratedService();
    
    ble->SetOnStackReadyCallback([]() {
        ConfigureAdvertisement();
    });
    ble->TurnOn();

    while(true) {
        if (gap->IsConnected()) {
            g_onboard_led->TurnOn();
        } else if (gap->IsAdvertising()) {
            g_onboard_led->Toggle();
        } else {
            g_onboard_led->TurnOff();
        }
        
        c7222::FreeRtosTask::Delay(c7222::FreeRtosTask::MsToTicks(250));
    }
}

}  // namespace

/**
 * @brief Program entry point.
 *
 * @return `0` on normal termination. Negative value if initialization fails
 * before the scheduler starts.
 */
int main() {
	c7222::Platform::Init();
    
    g_onboard_led = c7222::OnBoardLED::GetInstance();
    g_onboard_led->Init();
    
    g_ble_task.CreateTask(ble_app_task, "BLE_TASK", 2048, nullptr, 1);
    
    c7222::FreeRtosTask::StartScheduler();
	
	return 0;
}
