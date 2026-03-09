/**
 * @file main.cpp
 * @brief Template implementation for polling-based GPIO control on Pico 2 W.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 5 Task 5.1: Simplest Computer (Polling).
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#include "button.hpp"
#include "led.hpp"
#include "c7222_pico_w_board.hpp"
#include "platform.hpp"

/**
 * Task Description (Module 5 Task 5.1: Simplest Computer, Polling)
 *
 * Goal:
 * - Implement button-controlled LED behavior using c7222 platform abstractions.
 *
 * Requirements:
 * 1. Initialize platform services once at startup.
 * 2. Select one board button as input and one board LED as output.
 *    Use LED and Button IDs defined for the board:
 *    c7222::PicoWBoard::LedId and c7222::PicoWBoard::ButtonId.
 * 3. In an infinite loop:
 *    - If the button is pressed, turn the LED ON.
 *    - If the button is released, turn the LED OFF.
 * 4. Add a short delay in each loop iteration to avoid busy-waiting.
 */
int main() {
    // 1) Initialize the platform before using board peripherals or stdio.
    c7222::Platform* platform = c7222::Platform::GetInstance();
    platform->Initialize();

    printf("Platform initialized\n");

    // 2) Get one board LED and one board button through platform abstractions
    //    using c7222::PicoWBoard::LedId and c7222::PicoWBoard::ButtonId.
    c7222::Led& led = platform->GetLed(c7222::PicoWBoard::LedId::LED1_GREEN);
    c7222::Button& button = platform->GetButton(c7222::PicoWBoard::ButtonId::BUTTON_B1);

    // 3) Poll button state in the main loop and drive LED state accordingly.
    while (true) {
        
        if (button.IsPressed()) {
            led.On();
        } else {
            led.Off();
        }
        // 4) Keep a small delay in the loop to avoid busy-waiting at full speed.
        // Platform provides static delay helpers (for example SleepMs/SleepUs/SleepUntil)
        // that are useful for controlled timing in polling loops.
        c7222::Platform::SleepMs(10);
    }
}
