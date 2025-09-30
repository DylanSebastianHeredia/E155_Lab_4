// Sebastian Heredia
// dheredia@g.hmc.edu
// September 29, 2025
// TIM.c contains code to implement timer functions.

#include "TIM.h"

void initTIM(TIM_TypeDef * TIMx) {
    RCC->APB2ENR |= (1 << 16);        // Setup Clocks
    TIMx->PSC |= (40000-1);           // Prescaler: Divides by n + 1. 40 MHz/40000 = 1 kHz
    TIMx->EGR |= (0b1 << 0 );         // Set Update Generation (UG in EGR) bit to initialize/update registers (EGR - Event Generation Register)
    TIMx->CR1 |= 0b1;                 // Enable counter
}

void initTIM_PWM(TIM_TypeDef * TIMx) {
    RCC->APB1ENR1 |= (1 << 0);        // Set up clocks & enable clock to timer
    RCC->AHB2ENR |= (1 << 1);         // Enable clock to GPIOB
    TIMx->PSC |= 399;                 // Prescaler: Divides by n + 1. 40 MHz/400 = 100 kHz
    TIMx->CCMR1 |= (0b110 << 12);     // Set output CH2 to PWM Mode 1
    TIMx->CCMR1 |= (0b1 << 11);       // Enable output compare to the preload
  
    TIMx->CR1 |= (0b1 << 7);           // Set auto-reload preload
    TIMx->EGR |= (0b1 << 0 );          // Set UG bit to initialize/update registers
    TIMx->CR1 |= (0b1 << 0);           // Enable counter
    TIMx->CCER |= (0b1 << 4);          // Enable compare output pin
    
    pinMode(3, GPIO_ALT);              // Enable GPIO PB3 to ATLMODE
    GPIO->AFRL |= (0b0001 << 12);
}

void set_TIM_PWM_freq(TIM_TypeDef * TIMx, uint32_t freqDes){
    uint32_t freq;
    if (freqDes == 0){
        freq = 0x8FFFFFFF;
    } else {
        freq = (100000/freqDes);       // (100 kHz / Desired frequency) = Counter
    }

    if ((TIMx->CR1 & 1) != 1){
        initTIM_PWM(TIMx);
    }

    // PWM allows for generation of a signal w/ frequency determined by 
    // value on TIMx_ARR reg and duty cycle on the TIMx_CCRx register.
    
    TIMx->ARR = freq - 1;
    TIMx->CCR2 = freq/2;              // Div. by 2 = 50% Duty Cycle
    TIMx->EGR |= (0b1 << 0 );         // Set UG bit to initialize/update registers
}

// TIM2 sets PWM
void PWM(uint32_t freqDes){
    set_TIM_PWM_freq(TIM2, freqDes);
}

void TIM_delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
    if ((TIMx->CR1 & 1) != 1){
        initTIM(TIMx);
    }
    TIMx->ARR = ms;
    TIMx->EGR |= 1;            
    TIMx->SR &= ~(0b1);      
    TIMx->CNT = 0;
    while (!(TIMx->SR & 1));    
}

// TIM15 sets delay
void delay_millis(uint32_t ms){
    TIM_delay_millis(TIM15, ms);
}
