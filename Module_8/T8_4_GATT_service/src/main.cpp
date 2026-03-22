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
	// TODO: Print a short summary of the parsed services.
	// Useful API:
	// - AttributeServer provides service-count access and iterator support.
	// - Service provides characteristic iteration support.
	// The function should:
	// 1. Verify that the AttributeServer has been created.
	// 2. Print the number of parsed services.
	// 3. Use AttributeServer iterators to traverse the parsed services.
	// 4. For each service, use Service iterators to traverse its
	//    characteristics.
	// 5. Print for each service: index, UUID, and characteristic count.
	// 6. Print for each characteristic: index, UUID, user description if it
	//    exists, and descriptor count.
	
}

/**
 * @brief Configure and start BLE advertising after the stack is ready.
 */
void ConfigureAdvertisement() {
	// TODO: Implement advertising configuration for the GATT service task.
	// Useful API:
	// - BLE and GAP expose helpers for advertisement-data building and
	//   advertising startup.
	// Advertising-data setup and the overall startup pattern were introduced in
	// Module 7, Section 6.
	// The function should:
	// 1. Get the BLE and GAP instances.
	// 2. Register the GAP event handler.
	// 3. Configure the advertising flags and device name.
	// 4. Add a manufacturer-specific advertisement payload.
	// 5. Set advertising parameters.
	// 6. Start advertising.
	// 7. Print a short status message.
	
}

/**
 * @brief Assign runtime metadata to the generated custom service.
 *
 * @details This function finds the generated custom service from the parsed
 * attribute database and applies human-readable user-description strings to
 * its three characteristics when the corresponding descriptors are available.
 */
void ConfigureGeneratedService() {
	// TODO: Implement runtime configuration of the generated service.
	// Useful API:
	// - AttributeServer exposes the parsed services.
	// - Characteristic provides helpers related to the User Description
	//   descriptor.
	// The function should:
	// 1. Verify that the AttributeServer has been created.
	// 2. Access the generated custom service from the parsed database.
	// 3. Access its three characteristics in order.
	// 4. Set the provided user-description texts for those characteristics.
	
}

/**
 * @brief Main BLE application task.
 *
 * @param params Unused task parameter.
 */
[[noreturn]] void ble_app_task(void* /*params*/) {
	// TODO: Implement the main BLE task.
	// The task should:
	// 1. Get the BLE instance.
	// 2. Enable the generated AttributeServer database.
	// 3. Print the parsed service list.
	// 4. Attach the AttributeServer to the GAP event handler.
	// 5. Configure the generated service.
	// 6. Register the stack-on callback and turn BLE on.
	// 7. Visualize state with the on-board LED:
	//    - blink while advertising,
	//    - turn solid on while connected,
	//    - turn off otherwise.
	

	while(true) {
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
	// TODO: Implement the program entry point.
	// The main function should:
	// 1. Initialize the platform.
	// 2. Initialize the on-board LED.
	// 3. Initialize the BLE application task.
	// 4. Start the FreeRTOS scheduler.
	

	// TODO: implement main() here.
	
	return 0;
}
