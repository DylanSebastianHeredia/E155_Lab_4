// Sebastian Heredia
// dheredia@g.hmc.edu
// September 28, 2025
// main.c contains starter code to play Fur Elise and Blue.

// Includes for libraries
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "FLASH.h"

#include "fur_elise.h"
#include "blue.h"

// Define macros for constants
// #define PIN    6        // PA6
// #define length 200      // Duration length


int main(void) {
    // Configure flash to add waitstates to avoid timing errors
    configureFlash();

    // Setup the PLL and switch clock source to the PLL
    configureClock();

    // Initialize GPIOA and timers
    RCC->AHB2ENR |= (1 << 0);    

    RCC->APB2ENR |= (1 << 16);  // TIM15
    RCC->APB2ENR |= (1 << 17);  // TIM16

    // Configure PA6 for TIM16 on Channel 1
    pinMode(6, GPIO_ALT);       // PA6
    GPIOA->AFRL &= ~(0xF << (6 * 4));
    GPIOA->AFRL |=  (14 << (6 * 4));

    // initPWM
    const uint32_t CLK = 80000000;  // 80MHz
    // initPWM(TIM16, CLK, 440, 50);   // Example initialization if needed

    // Fur Elise
    int i = 0;
    while (fur_elise_notes[i][1] != 0) {
        int freq = fur_elise_notes[i][0];
        int length  = fur_elise_notes[i][1];

        if (freq == 0) {
            // Rest: disable channel output
            TIM16->CCER &= ~(1 << 0);
            delay_micros(length * 1000);   // Convert ms → us
            TIM16->CCER |= (1 << 0);
        } else {
            setPWM(TIM16, CLK, freq, 50);
            delay_micros(length * 1000);   // Convert ms → us
        }
        i++;
    }

    // Stop for 1 second
    TIM16->CR1 &= ~1;                 // Stop PWM
    delay_micros(1000000);            // 1 second delay

    // Blue (Da Be Dee)
    i = 0;
    while (blue_notes[i][1] != 0) {
        int freq = blue_notes[i][0];
        int length  = blue_notes[i][1];

        if (freq == 0) {
            TIM16->CCER &= ~(1 << 0);
            delay_micros(length * 1000);   // Convert ms → us
            TIM16->CCER |= (1 << 0);
        } else {
            setPWM(TIM16, CLK, freq, 50);
            delay_micros(length * 1000);   // Convert ms → us
        }
        i++;
    }

    // Turn PWM off at the very end to end the music
    TIM16->CR1 &= ~1;
    while (1);
}