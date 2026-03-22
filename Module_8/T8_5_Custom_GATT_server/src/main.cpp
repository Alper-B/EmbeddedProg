/**
 * @file main.cpp
 * @brief Template implementation for the Module 8 custom GATT server task.
 *
 * DISCLAIMER:
 * This file is a task template for ELEC C7222 Module 8 Task 8.5.
 * It contains task-specific TODO notes that indicate the required
 * implementation points.
 */

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

#include "advertisement_data.hpp"
#include "attribute_server.hpp"
#include "ble.hpp"
#include "button.hpp"
#include "characteristic.hpp"
#include "c7222_pico_w_board.hpp"
#include "freertos_event_group.hpp"
#include "freertos_task.hpp"
#include "gap.hpp"
#include "led.hpp"
#include "platform.hpp"

#include "app_profile.h"
#include "gap_event_handler.hpp"

namespace {

/** Device name advertised by the custom GATT server. */
constexpr const char* kDeviceName = "c7222-custom-gatt";
/** 128-bit UUID of the custom service in byte-array form. */
constexpr std::array<uint8_t, 16> kCustomServiceUuidBytes = {
	0x7a, 0xc2, 0x15, 0x17, 0x86, 0xb3, 0x4b, 0x8e,
	0x9d, 0x9a, 0x85, 0xce, 0x5d, 0x7c, 0x10, 0x01,
};
/** 128-bit UUID of the Status characteristic. */
constexpr std::array<uint8_t, 16> kStatusCharacteristicUuidBytes = {
	0x7a, 0xc2, 0x15, 0x17, 0x86, 0xb3, 0x4b, 0x8e,
	0x9d, 0x9a, 0x85, 0xce, 0x5d, 0x7c, 0x20, 0x01,
};
/** 128-bit UUID of the Configure characteristic. */
constexpr std::array<uint8_t, 16> kConfigureCharacteristicUuidBytes = {
	0x7a, 0xc2, 0x15, 0x17, 0x86, 0xb3, 0x4b, 0x8e,
	0x9d, 0x9a, 0x85, 0xce, 0x5d, 0x7c, 0x20, 0x02,
};
/** 128-bit UUID of the ButtonCounter characteristic. */
constexpr std::array<uint8_t, 16> kButtonCounterCharacteristicUuidBytes = {
	0x7a, 0xc2, 0x15, 0x17, 0x86, 0xb3, 0x4b, 0x8e,
	0x9d, 0x9a, 0x85, 0xce, 0x5d, 0x7c, 0x20, 0x03,
};
/** Runtime user-description texts assigned to the three custom characteristics. */
constexpr const char* kCharacteristicDescriptions[] = {
	"Status",
	"Configure",
	"ButtonCounter",
};

/** Event-group bit used for deferred button-press handling. */
constexpr uint32_t BUTTON_PRESSED_EVENT_MASK = (1u << 0);
/** Event-group bit used for deferred Configure write handling. */
constexpr uint32_t CONFIG_WRITTEN_EVENT_MASK = (1u << 1);
/** Combined event mask waited on by the BLE application task. */
constexpr uint32_t APP_EVENT_MASK = BUTTON_PRESSED_EVENT_MASK | CONFIG_WRITTEN_EVENT_MASK;

/** Active attribute-server instance created from the generated GATT profile. */
static c7222::AttributeServer* g_att_server = nullptr;
/** Board LED used to reflect Configure characteristic state. */
static c7222::Led* g_led1 = nullptr;
/** Board button used to generate deferred ButtonCounter updates. */
static c7222::Button* g_button = nullptr;

/** Cached pointer to the custom service inside the parsed attribute database. */
static c7222::Service* g_custom_service = nullptr;
/** Cached pointer to the Status characteristic. */
static c7222::Characteristic* g_status_characteristic = nullptr;
/** Cached pointer to the Configure characteristic. */
static c7222::Characteristic* g_configure_characteristic = nullptr;
/** Cached pointer to the ButtonCounter characteristic. */
static c7222::Characteristic* g_button_counter_characteristic = nullptr;

/** Shared event group for IRQ-to-task and BLE-callback-to-task handoff. */
static c7222::FreeRtosEventGroup g_event_group;
/** Main BLE application task wrapper. */
static c7222::FreeRtosTask g_ble_task;
/** GAP event handler used for connection-state tracking and advertising restart. */
static GapEventHandler g_gap_event_handler;

/** Current second counter published through the Status characteristic. */
static uint32_t g_status_seconds = 0;
/** Latest value written to the Configure characteristic. */
static uint8_t g_configure_value = 0;
/** Current per-connection button-press count. */
static uint32_t g_button_counter = 0;

/**
 * @brief Characteristic event handler for Configure writes.
 *
 * The handler stores the latest written Configure value and signals the
 * application task to process it outside BLE callback context.
 */
class ConfigureEventHandler : public c7222::Characteristic::EventHandler {
   public:
	// TODO: declare and implement the characteristic callback needed to detect
	// when the Configure characteristic value is written.
	// It must store the latest Configure value and signal the application task.
	// Inspect the Characteristic::EventHandler API to find the write-related
	// callback provided by the base class.
	
};

/**
 * @brief Characteristic event handler for ButtonCounter client-update events.
 *
 * The handler reports notification/indication configuration changes and
 * indication confirmations for the ButtonCounter characteristic.
 */
class ButtonCounterEventHandler : public c7222::Characteristic::EventHandler {
   public:
	// TODO: declare and implement the characteristic callbacks needed to detect
	// when ButtonCounter updates are enabled, disabled, and confirmed.
	// They must print when notifications/indications are enabled, disabled, or
	// confirmed.
	// Inspect the Characteristic::EventHandler API to find the update-related
	// callbacks provided by the base class.
	
};

/** Event-handler instance bound to the Configure characteristic. */
static ConfigureEventHandler g_configure_event_handler;
/** Event-handler instance bound to the ButtonCounter characteristic. */
static ButtonCounterEventHandler g_button_counter_event_handler;

/**
 * @brief Configure advertising data and start advertising.
 */
void ConfigureAdvertisement() {
	// TODO: Implement advertising configuration for the custom GATT server.
	// Useful directions:
	// - Reuse the GAP-side startup pattern from Module 7 and Task 8.4.
	// - Register the GAP event handler before starting advertising.
	// The function should:
	// 1. Get the BLE and GAP instances.
	// 2. Register the GAP event handler.
	// 3. Configure the advertising flags and device name.
	// 4. Set advertising parameters.
	// 5. Start advertising.
	
}

/**
 * @brief Print the parsed service and characteristic structure.
 */
void PrintParsedServices() {
	// TODO: Print a short summary of the parsed services and characteristics.
	// Useful API:
	// - AttributeServer provides service-count access and iterator support.
	// - Service provides characteristic iteration support.
	// The function should:
	// 1. Verify that the AttributeServer has been created.
	// 2. Print the number of parsed services.
	// 3. Print for each service: index, UUID, and characteristic count.
	// 4. Print for each characteristic: index, UUID, user description if it
	//    exists, and descriptor count.
	
}

/**
 * @brief Cache the custom service and its three characteristics.
 */
void GetServiceCharacteristics() {
	// TODO: Find the generated custom service by its UUID and get its three
	// characteristics.
	// Useful API:
	// - AttributeServer exposes FindServiceByUuid(...) for UUID-based lookup.
	// - Service exposes FindCharacteristicByUuid(...), FindCharacteristicByHandle(...),
	//   and indexed characteristic access after the service has been found.
	// The function should:
	// 1. Verify that the AttributeServer contains at least one service.
	// 2. Find the custom service by its 128-bit UUID.
	// 3. Resolve its three characteristics in declaration order.
	
}

/**
 * @brief Assign runtime Characteristic User Description texts.
 */
void ConfigureCharacteristicDescriptions() {
	// TODO: Set the Characteristic User Description texts for the three custom
	// characteristics when the descriptors are present in the generated profile.
	
}

/**
 * @brief Attach the runtime event handlers required by the task.
 */
void AttachCharacteristicHandlers() {
	// TODO: Attach the runtime event handlers required by the task.
	// Configure needs its write handler, and ButtonCounter needs its event
	// handler so the application can print when notifications or indications
	// are enabled, disabled, or confirmed.
	
}

/**
 * @brief Apply the latest Configure value to the board LED.
 */
void ApplyConfigureValue() {
	// TODO: Apply the latest Configure characteristic value to LED1_RED.
	// Non-zero should turn the LED on. Zero should turn it off.
	
}

/**
 * @brief Publish the current second counter to the Status characteristic.
 */
void UpdateStatusValue() {
	// TODO: Update the Status characteristic with the current second counter.
	
}

/**
 * @brief Reset and publish the per-connection button counter.
 */
void ResetButtonCounter() {
	// TODO: Reset the per-connection button counter and publish the new value.
	
}

/**
 * @brief Process a deferred button press in task context.
 */
void HandleDeferredButtonPress() {
	// TODO: Increment the button counter only while a client is connected and
	// publish the updated value through the ButtonCounter characteristic.
	
}

/**
 * @brief Button IRQ callback that defers button events to the application task.
 *
 * @param events GPIO input event flags supplied by the IRQ source.
 */
void button_irq_handler(std::uint32_t /*events*/) {
	// TODO: Use the button IRQ callback to detect a button press and defer the
	// event to the application task through the shared synchronization primitive.
	// Keep the IRQ path short and do not perform BLE or long-running work here.
	// The deferred button press must affect ButtonCounter only when a client is
	// connected.
	
}

/**
 * @brief Main BLE application task.
 *
 * @param params Unused task argument pointer.
 */
[[noreturn]] void ble_app_task(void* /*params*/) {
	// TODO: Implement the main BLE application task.
	// The task should:
	// 1. Get the BLE instance.
	// 2. Enable the generated AttributeServer database.
	// 3. Print the parsed service and characteristic list.
	// 4. Attach the AttributeServer to the GAP event handler.
	// 5. Resolve the custom service and its three characteristics.
	// 6. Assign the required Characteristic User Description texts.
	// 7. Attach the characteristic event handlers.
	// 8. Initialize the characteristic values.
	// 9. Register the stack-on callback and turn BLE on.
	// 10. In the task loop:
	//     - handle connection and disconnection state changes,
	//     - process deferred Configure writes,
	//     - process deferred button-press events only while connected,
	//     - update Status once per second.
	

	while(true) {
		c7222::FreeRtosTask::Delay(c7222::FreeRtosTask::MsToTicks(50));
	}
	
}

}  // namespace

/**
 * @brief Program entry point for the custom GATT server task.
 *
 * @return `0` if the scheduler unexpectedly returns, otherwise a negative
 * setup error code.
 */
int main() {
	// TODO: Implement the program entry point.
	// The main function should:
	// 1. Initialize the platform.
	// 2. Resolve BUTTON_B1 and LED1_RED from the board support layer.
	// 3. Initialize the shared synchronization primitive.
	// 4. Register a button IRQ callback for BUTTON_B1.
	// 5. Create the BLE application task.
	// 6. Start the scheduler.
	

	// TODO: implement main() here.
	
	return 0;
}
