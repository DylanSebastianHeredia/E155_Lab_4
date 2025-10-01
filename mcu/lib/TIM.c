// Sebastian Heredia
// dheredia@g.hmc.edu
// September 29, 2025
// TIM.c contains code to implement timer functions.

#include "TIM.h"

int clk_freq = 80000000 / (3000 + 1);

// Use TIM16 for outputting audio
// Calculate PWM: Period (ARR) and Pulse Width (CCR1)

// int freq is the desired output PWM frequency (Hz)
// int dutyCycle is the desired PWM Duty Cycle (%)

void initPWM(TIM_TypeDef *TIMx, uint32_t clk, int freq, int dutyCycle) {
    if (freq <= 0) return;
    uint32_t T = clk / (uint32_t)freq;  // T = timer period
      
    if (T < 2) {
    T = 2;                              // Avoid divide by zero
    }

    TIMx->PSC = 79;                     // For pitch control
    // Set prescaler (PSC)
    // Set such that 1,000,000 Hz = 80,000,000 Hz / (PSC + 1), PSC = 79
    TIMx->ARR = T - 1;

    // Duty Cycle Calculations
    uint32_t ccr = (T * (uint32_t)dutyCycle) / 100;  

    if (ccr >= T) {
    ccr = T - 1;    
    }

    TIMx->CCR1 = ccr;             

    TIMx->CCMR1 &= ~(0x7 << 4);   // PWM mode 1 (OC1M=110), enable preload
    TIMx->CCMR1 |=  (0x6 << 4);   // PWM mode 1
    TIMx->CCMR1 |=  (1 << 3);     // OC1PE = 1
    TIMx->CCER &= ~(1 << 1);      // Enable channel 1 output
    TIMx->CCER |=  (1 << 0);
    TIMx->CR1 |= (1 << 7);        // Enable ARR preload
    TIMx->BDTR |= (1 << 15);      // Enable BDTR.MOE for TIM15 and TIM16)
    TIMx->EGR |= 1;               // Generate update for preload
    TIMx->CR1 |= 1;               // Start counter
}

// Set PWM freq and duty cycle for next notess
// clk = timer clock
void setPWM(TIM_TypeDef *TIMx, uint32_t clk, int freq, int dutyCycle) {
    if (freq <= 0) return;      

    uint32_t T = clk / (uint32_t)freq;  // Compute T (One full timer period)
    if (T < 2) {
    T = 2;
    }

    uint32_t ccr = (T * (uint32_t)dutyCycle) / 100;     // Capture Compare Register 1 (CCR1) is LOW until end of period T
    if (ccr >= T) {
    ccr = T - 1;      // Ensuring Duty Cycle less than 100%
    }

    TIMx->ARR  = T - 1;             // Starts from 0, so T-0 accounts for total ticks
    TIMx->CCR1 = ccr;
    TIMx->EGR |= 1;                 // Enable UG bit
}

// Use TIM15 to generate microsecond timer
void delay_micros(uint32_t us) {

    TIM15->CNT = 0;             // Reset counter

    // Aim for 1MHz timer frequency for improved precision
    // 1MHz is a period of 1 microsecond

    TIM15->PSC = 3000;            // Set prescaler (PSC). TIM15 and TIM16 have same PSC value
    // Set such that 1,000,000 Hz = 80,000,000 Hz / (PSC + 1), PSC = 79

    TIM15->CR1 &= ~1;
    TIM15->ARR = (clk_freq / 1000) * us;            // Set ARR

    TIM15->CR1 |= 1;            // Set counter
    TIM15->EGR |= 1;            // Enable UG bit
    TIM15->CNT = 0;
    TIM15->SR &= ~1;            // Empty the Status Register (SR) to remove previous operations

    while (!(TIM15->SR & 1));   // Wait until UIF is set before clearing flag and stopping counter
}
