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
    RCC->AHB2ENR |= (1 << 0);   // GPIO for A 

    RCC->APB2ENR |= (1 << 16);  // TIM15
    RCC->APB2ENR |= (1 << 17);  // TIM16

    // Configure PA6 for TIM16 on channel 1
    pinMode(6, GPIO_ALT);       // PA6
    GPIO->AFRL &= ~(0xF << (6 * 4));
    GPIO->AFRL |= (14 << (6 * 4));

    // initPWM
    const uint32_t sysClk = 80000000/80;     // 80MHz system clk / 80 = Timer clk
    initPWM(TIM16, sysClk, 440, 50);         // Tuning A4 (440Hz)

    // Fur Elise
    int i = 0;
    while (fur_elise_notes[i][1] != 0) {
        int freq_fur = fur_elise_notes[i][0];
        int length_fur = fur_elise_notes[i][1];

        if (freq_fur == 0) {
            TIM16->CCER &= ~(1 << 0);
            delay_micros(length_fur);
            TIM16->CCER |= (1 << 0);
        } 
        
        else {
            setPWM(TIM16, sysClk, freq_fur, 50);
            delay_micros(length_fur);  
        }
        i++;
    }

    // Stop for 1 second
    TIM16->CR1 &= ~1;                 // Stop PWM
    delay_micros(1000000);            // 1 second delay

    initPWM(TIM16, sysClk, 440, 50);   

    // Blue (Da Be Dee)
    i = 0;
    while (blue_notes[i][1] != 0) {
        int freq_blue = blue_notes[i][0];
        int length_blue = blue_notes[i][1];

        if (freq_blue == 0) {
            TIM16->CCER &= ~(1 << 0);
            delay_micros(1.5 * length_blue);        // Slowed down to match actual song speed
            TIM16->CCER |= (1 << 0);
        } 
        
        else {
            setPWM(TIM16, sysClk, freq_blue, 50);
            delay_micros(1.5 * length_blue); 
        }
        i++;
   
    }
 
    // Turn PWM off at the very end to end the music
    TIM16->CR1 &= ~1;
    while (1);
}
