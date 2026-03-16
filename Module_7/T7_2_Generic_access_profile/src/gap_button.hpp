/**
 * @brief GAP button helper declaration for Module 7 Task 7.2.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 7 Task 7.2: Generic Access Profile.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 * NOTE: This file is for local testing only.
 *
 * TASK REQUIREMENT FOR THIS FILE:
 * Students implement task-specific declarations and callback declarations in this file
 * as described by the guidance below.
 */

#pragma once

#include <cstdint>
#include <string>

#include "button.hpp"
#include "c7222_pico_w_board.hpp"
#include "gap.hpp"
#include "led.hpp"
#include "non_copyable.hpp"

/*----------------------------------------------------------------
 * Task template interface for the T7.2 GAP button-count exercise.
 *----------------------------------------------------------------*/

/**
 * @brief GAP helper that publishes a dynamic advertisement payload.
 *
 * This class is the task-specific GAP application object and owns the entire
 * application workflow for the button-count exercise.
 *
 * Functionality scope:
 * - `Initialize()` stores device/button/LED configuration and prepares references
 *   to board peripherals.
 * - `Run()` is the application task entry point: it configures peripherals and
 *   callbacks, starts BLE advertising, then loops forever managing LED output and
 *   pending GAP updates.
 * - A button IRQ callback (`OnButtonPressed`) monitors button activity.
 *   It records a deferred update request so that heavy work is not performed in
 *   interrupt context.
 * - The class derives from `c7222::Gap::EventHandler` and receives GAP lifecycle
 *   callbacks (`OnBleInitComplete`, `OnAdvertisingStart`,
 *   `OnAdvertisingEnd`, `OnConnectionComplete`, `OnDisconnectionComplete`) used to
 *   keep internal state synchronized with the BLE stack.
 *
 * GAP state tracking and behavior:
 * - `advertising_` indicates whether GAP advertising is currently active.
 *   Run() uses this to decide whether the LED should blink.
 * - `connected_` indicates whether a BLE link is currently established.
 *   Run() uses this to select steady LED-on when connected.
 * - `pending_update_` is set by the button IRQ path and consumed in
 *   `ProcessPendingUpdate()`; this defers advertisement reconstruction to the
 *   main loop.
 * - `button_press_count_` is tracked and written into manufacturer-specific
 *   advertisement data through `UpdateAdvertisementData()`.
 * - `running_` protects against re-entering `Run()` and running two task loops at
 *   the same time.
 *
 * The class also owns a lightweight task-safe LED state model where BLE connection
 * and advertising states determine visible LED output, while advertisement payload
 * updates are delayed through a pending-update mechanism.
 *
 * Students implement this class in `gap_button.cpp`.
 *
 * Runtime model:
 * - Button press is captured in an ISR-like callback and marks
 *   `pending_update_`.
 * - The main Run loop consumes pending updates when safe to do so.
 * - BLE callbacks mutate task state and trigger restart/update decisions.
 *
 * @note The class declaration is provided as a template; students should
 * implement the definitions in the corresponding gap_button.cpp file.
 */
class GapButton : public c7222::Gap::EventHandler, public c7222::NonCopyableNonMovable {
  private:
	std::string device_name_;					  //!< Device name shown in advertisements.
	c7222::Button *button_{nullptr};			  //!< Button object resolved from Platform.
	c7222::Led *led_{nullptr};					  //!< LED object resolved from Platform.
	mutable std::uint32_t button_press_count_{0}; //!< Number of registered button presses.
	mutable bool advertising_{false};			  //!< True while GAP advertising is active.
	mutable bool connected_{false};				  //!< True while a BLE link is established.
	mutable bool pending_update_{false};		  //!< Set by button callback; consumed by Run().
	mutable bool running_{false};				  //!< Prevents reentering Run() concurrently.

	/**
	 * @brief IRQ callback for the button.
	 *
	 * The callback only signals that an update is required.
	 * Keep work here minimal because it may be invoked from interrupt context.
	 */
	void OnButtonPressed(std::uint32_t events);
	/**
	 * @brief Update manufacturer specific data with the latest button press count.
	 *
	 * Rebuilds the payload from internal state and publishes it through GAP if
	 * advertising is enabled.
	 */
	void UpdateAdvertisementData() const;
	/**
	 * @brief Callback executed when BLE stack initialization completes.
	 *
	 * Triggered after BLE startup is complete; this is where task bootstrap
	 * actions are resumed.
	 */
	void OnBleInitComplete();
	/**
	 * @brief Re-process deferred button press updates in the main loop.
	 *
	 * Reads and clears `pending_update_`, then updates advertisement contents
	 * and triggers GAP restart logic where applicable.
	 */
	void ProcessPendingUpdate() const;

	
	// TODO: declare c7222::Gap::EventHandler callbacks to handle advertising start, advertising end,
	// connection complete, and disconnection complete events.
	// Each callback must be declared with the correct signature to compile and link properly.
	// You must use override or final keywords to ensure correct overriding of the base class methods.
	//
	// ! ONLY DECLARE THE CALLBACKS IN THIS HEADER FILE. DEFINITIONS GO IN gap_button.cpp !
	// 
	// When advertising starts: we must set the advertising_ flag so that the main loop in run task can blink
	the led.
	// When advertising ends: we must clear the advertising_ flag so that the main loop in run task can turn
	off the led.
	// When a connection is established: we must set the connected_ flag so that the main loop in run task can
	turn on the led.
	// When a disconnection occurs: we must clear the connected_ flag and restart advertising with updated
	manufacturer data (button press count).
	
	

  public:
	GapButton() = default;
	/**
	 * @brief Construct a new GapButton object.
	 * @details The constructor initializes the object with the provided device name, button ID, and LED ID.
	 * The device name is used in the advertising payload, while the button ID and LED ID are used to interact
	 * with the board peripherals.
	 *
	 * @param device_name Device name to include in advertisements.
	 * @param button_id Board button to track for presses.
	 * @param led_id Board LED to indicate advertising/connection status.
	 */
	void Initialize(const std::string &device_name,
					c7222::PicoWBoard::ButtonId button_id,
					c7222::PicoWBoard::LedId led_id);

	/**
	 * @brief Starts the GAP demo workflow.
	 *
	 * This function initializes runtime objects, registers callbacks,
	 * starts BLE and keeps running forever.
	 *
	 * If Initialize() was never called successfully, Run() returns immediately.
	 * It performs the following high-level steps:
	 * 1. Initialize the button and LED objects from Platform.
	 * 2. Register an IRQ callback for the button to track presses.
	 * 3. Register GAP event handlers for advertising and connection events.
	 * 4. Start the BLE stack and begin advertising.
	 * 5. In the main loop:
	 *    - If advertising, blink LED at 500 ms on/off.
	 *    - If not advertising, keep LED on when connected, else off.
	 *    - Update advertisement payload and restart advertising when updates are pending.
	 *
	 */
	void Run();

	/**
	 * @brief Return true once both peripheral objects are provisioned.
	 *
	 * @return true when button_ and led_ are not null.
	 */
	bool IsInitialized() const { return button_ != nullptr && led_ != nullptr; }
};
