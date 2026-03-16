/**
 * @brief GAP button press counter task entry point.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.2: Generic Access Profile.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 * NOTE: This file contains the main function and global objects for the GAP button exercise. 
 * The main function initializes the platform, configures the GAP button task, and starts 
 * the FreeRTOS scheduler. The GAP button task object is defined globally and is used to call 
 * `Initialize()` with the desired configuration before starting the task.
 * The exercise solution must be implemented in `main.cpp`/`gap_button.hpp`/`gap_button.cpp`.
 */

#include <iostream>

#include "freertos_task.hpp"
#include "platform.hpp"
#include "gap_button.hpp"

//! Global instance of the GAP button task object. The application task will use
// this object to call `Initialize()` with the desired configuration.
GapButton gap_button;
//! FreeRTOS task object for the application task. The main function will initialize
// this task to run the GAP button workflow.
c7222::FreeRtosTask app_task;

int main() {
	

	// TODO: implement main function logic here.
	// The main function should perform the following steps:
	// 1. Initialize the platform by calling `Platform::GetInstance()->Initialize()`.
	//    - If platform initialization fails, print an error message and return a non-zero value to indicate failure.
	// 2. Initialize the global `gap_button` object by calling its `Initialize()` method with the desired 
	//    device name, button ID, and LED ID.
	//	- The device name is a string that will be included in the BLE advertisements.
	//	- The button ID and LED ID should correspond to valid peripherals on the board you are 
	//    using (e.g., BUTTON_B1 and LED1_RED).
	// 3. Initialize the `app_task` FreeRTOS task object to run the `gap_button.Run()` method as the task entry point. 
	//    You can choose an appropriate stack size and priority for the task.
	// 4. Start the FreeRTOS scheduler to begin executing tasks. The `gap_button.Run()` method will 
	//    manage the application workflow from this point onward.	
	return 0;
}
