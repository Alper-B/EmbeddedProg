/**
 * @brief GAP button task implementation.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.2: Generic Access Profile.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 * NOTE: This file is for local testing only.
 */

#include "gap_button.hpp"

#include "ble.hpp"
#include "freertos_critical_section.hpp"
#include "platform.hpp"

#include <array>
#include <cstdlib>
#include <cstdint>
#include <iostream>

void GapButton::OnButtonPressed(std::uint32_t events) {
	// TODO: implement button press handling logic in gap_button.cpp.
	// This callback is executed in an ISR context when the button state changes.
	// We only want to count button presses, so we should check for the falling edge event.
	// The callback should update internal state to reflect the new button press count and signal
	// that an update is pending. The main loop will consume the pending update and trigger
	// advertisement data refresh and GAP restart logic as needed.

	
}

/**
 * @brief This function is called by `run()` to update the manufacturer-specific advertisement data with the 
 * latest button press count. It should rebuild the manufacturer data field in the advertisement data builder 
 * and apply it to GAP if advertising is active.
 * 
 */
void GapButton::UpdateAdvertisementData() const {

	

	// TODO: implement advertisement data update login here!
	// This function should rebuild the manufacturer-specific data payload with the latest button press count
	// and update the GAP advertising data if advertising is currently active.

	// Since the button press count is modified in ISR context, while storing its value in the advertisement data 
	// builder and applying it to GAP is done in the main loop, you should ensure that the button press count 
	// is read atomically to prevent race conditions. 
	// HINT: You can use a critical section or other synchronization mechanism.
	
	// HINT: You might find AdvertisementDataBuilder::ReplaceOrAdd() useful for updating the manufacturer 
	// data field in the builder. You can also use some other functions to clear and rebuild the builder contents 
	// if you prefer that approach.

    // HINT: Go over Gap example of c7222-development repository to see how the advertisement data builder is 
	// used to construct and update advertising payloads.
}

void GapButton::OnBleInitComplete() {
	std::cout << "Bluetooth stack is on\n";
	
	// TODO: implement BLE stack initialization complete handling here.

	// This callback is executed once the BLE stack has completed its startup sequence. You can use this callback
	// to perform any GAP setup that requires the stack to be active, such as configuring advertising parameters,
	// setting initial advertising data, and starting advertising.

	// You must set the advertisement flags to at least kLeGeneralDiscoverableMode and kBrEdrNotSupported to 
	// ensure the device is discoverable and indicates that it does not support classic Bluetooth.

	// You must set the device name to the value provided in the Initialize() function.

	// You should also set the initial manufacturer specific data field in the advertisement data builder with 
	// the initial button press count (which should be zero at this point). This ensures that the first advertisements
	// include the correct button press count.

	// Finally, you should configure the advertising parameters for connectable undirected advertising (ADV_IND) 
	// with a custom interval, and then start advertising.

	// HINT: Go over Gap example of c7222-development repository to see how these steps are performed in the 
	// BLE initialization callback.

	std::cout << "Device is advertising\n";
}

void GapButton::ProcessPendingUpdate() const {
	

	// TODO: implement pending update processing logic here.
	// This function is called in the main loop to check if there is a pending update signaled by the button press callback. 
	// If there is a pending update, it should call UpdateAdvertisementData() to refresh the manufacturer data field in 
	// the advertisement payload with the latest button press count, and then clear the pending update flag.

	// HINT: Since the pending update flag is set in ISR context and cleared in the main loop, you should ensure that
	// access to this flag is synchronized to prevent race conditions. You can use a critical section or other 
	// synchronization mechanism to safely read and clear the flag.

}



void GapButton::Initialize(const std::string& device_name,
					c7222::PicoWBoard::ButtonId button_id,
					c7222::PicoWBoard::LedId led_id){
	
	// TODO: implement initialization logic here.
	// This function should initialize the GapButton object with the provided device name, button ID,
	// and LED ID. It should also resolve the button and LED objects from the Platform singleton using the provided IDs.
	// The device name should be stored for later use in the BLE initialization callback when setting up
	// the advertisement data.

	// You can also initialize any internal state variables here, such as the button press count and flags.

	// Hint:: Use the Platform singleton to resolve the button and LED objects using the provided IDs.
	// c7222::Platform::GetButton() and c7222::Platform::GetLed() functions can be used for this purpose.
	// Note that these functions perform hard asserts if the provided IDs are invalid, so you should ensure 
	// that the IDs passed to Initialize() are valid for the board you are using.
}

void GapButton::Run() {
	if(!IsInitialized()) {
		std::cerr << "GapButton::Initialize() must be called before Run()\n";
		std::exit(EXIT_FAILURE);
	}

	

	// TODO:: implement the main task logic in this function. This function should not 
	// return and should perform the following high-level steps:
	// 1. Initialize the internal flags and button press count.
	// 2. Register an IRQ callback for the button to track presses.
	// 3. Register GAP event handlers for advertising and connection events. Since 
	//    `*this` is a c7222::Gap::EventHandler object, you can register the object itself 
	//    as the handler and implement the callback methods in this class.
	// 4. Start the BLE stack and begin advertising. The BLE initialization callback will 
	//    handle the GAP setup and advertising start.
	// 5. In the main loop:
	//    - If advertising, blink the LED at a 500 ms interval.
	//    - If not advertising, keep the LED on when connected, else off.
	//    - Check if there is a pending update signaled by the button press callback,
	//      and if so, call the function to update the advertisement data and clear the pending update flag.
	//    - Sleep for 500 ms per cycle to yield to other tasks and control the LED blinking rate.

}

