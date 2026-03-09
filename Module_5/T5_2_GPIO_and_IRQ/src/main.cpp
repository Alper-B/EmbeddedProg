/**
 * @file main.cpp
 * @brief Template implementation for GPIO interrupt handling on Pico 2 W.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 5 Task 5.2: GPIO and IRQ.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#include <cstdio>

#include "button.hpp"
#include "gpio.hpp"
#include "led.hpp"
#include "c7222_pico_w_board.hpp"
#include "platform.hpp"

/**
 * Task Description (Module 5 Task 5.2: GPIO and IRQ)
 *
 * Goal:
 * - Extend the polling solution by using GPIO interrupts for button events.
 *
 * Requirements:
 * 1. Declare and define an IRQ callback with the signature:
 *      void button_isr(uint32_t events);
 * 2. Configure button interrupt support for both rising and falling edges.
 *    Use LED and Button IDs defined for the board:
 *    c7222::PicoWBoard::LedId and c7222::PicoWBoard::ButtonId.
 * 3. In the ISR, update LED state according to button state:
 *    - pressed  -> LED ON
 *    - released -> LED OFF
 * 4. In the main loop, print LED state whenever it changes.
 */

// Shared objects and flags used by the IRQ callback and main loop.

volatile bool state_changed = false;
c7222::Button* g_button = nullptr;
c7222::Led* g_led = nullptr;

// IRQ callback for button edge events.
void button_isr(uint32_t events) {
    if (g_button != nullptr && g_led != nullptr) {
        if (g_button->IsPressed()) {
            g_led->On();
        } else {
            g_led->Off();
        }
        
        state_changed = true;
    }
}

int main() {
    // 1) Initialize platform services before using peripherals or stdio.
    c7222::Platform* platform = c7222::Platform::GetInstance();
    platform->Initialize();

    printf("Platform initialized.\n");

    // 2) Select one board LED and one board button through platform abstractions
    //    using c7222::PicoWBoard::LedId and c7222::PicoWBoard::ButtonId.
    g_led = &platform->GetLed(c7222::PicoWBoard::LedId::LED1_GREEN);
    g_button = &platform->GetButton(c7222::PicoWBoard::ButtonId::BUTTON_B1);

    // 3) Configure button IRQ for both edges and bind button_isr callback.
    c7222::GpioInputEvent both_edges = c7222::GpioInputEvent::FallingEdge | c7222::GpioInputEvent::RisingEdge;
    
    platform->EnableButtonIrq(c7222::PicoWBoard::ButtonId::BUTTON_B1, both_edges, button_isr);

    printf("IRQ configured");

    // 4) Keep main alive; print LED state whenever ISR reports a state change.
    while (true) {
        if (state_changed) {
            state_changed = false;
            
            if (g_button->IsPressed()) {
                printf("LED State Changed: ON\n");
            } else {
                printf("LED State Changed: OFF\n");
            }
        }

        // Platform provides static delay helpers (SleepMs/SleepUs/SleepUntil)
        // that are useful for controlled timing in main loops.
        c7222::Platform::SleepMs(10);
    }
}
