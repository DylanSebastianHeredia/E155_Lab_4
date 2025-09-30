// Sebastian Heredia
// dheredia@g.hmc.edu
// September 29, 2025
// TIM.c contains code to implement timer functions.

#include "TIM.h"

void initTIM(TIM_TypeDef * TIMx) {
    RCC->APB2ENR |= (1 << 16);            // Set up clock
    TIMx->TIM_PSC |= (40000-1);           // Prescale: Divides by n + 1. 40 MHz/40000 = 1 kHz
    TIMx->TIM_EGR |= (0b1 << 0 );         // Set UG bit to initialize/update registers
    TIMx->TIM_CR1 |= 0b1;                 // Enable counter
}

void initTIM_PWM(TIM_TypeDef * TIMx) {
    RCC->APB1ENR1 |= (1 << 0);            // Set up clock to timer
    RCC->AHB2ENR |= (1 << 1);             // Set up clock to GPIOB
    TIMx->TIM_PSC |= 399;                 // Prescale: Divides by n + 1. 40 MHz/400 = 100 kHz
    TIMx->TIM_CCMR1 |= (0b110 << 12);     // Set output channel 2 to PWM mode 1
    TIMx->TIM_CCMR1 |= (0b1 << 11);       // Enable output compare 2 preload
    TIMx->TIM_CR1 |= (0b1 << 7);          // Set auto-reload preload
    TIMx->TIM_EGR |= (0b1 << 0 );         // Set UG bit to initialize/update registers
    TIMx->TIM_CR1 |= (0b1 << 0);          // Enable counter
    TIMx->TIM_CCER |= (0b1 << 4);         // Enable capture/compare output pin
    
    pinMode(3, GPIO_ALT);                 // Enable GPIO PB3 pin to alternative mode
    GPIO->AFRL |= (0b0001 << 12);
}

void setPWM_Freq(TIM_TypeDef * TIMx, uint32_t freqDes){
    uint32_t freq;
    
    if (freqDes == 0) freq = 0x8FFFFFFF;  // If no freqDes, set frequency to max
    
    else freq = (100000/freqDes);         // 100 kHz / desired frequency = counter

    if ((TIMx->TIM_CR1 & 1) != 1) initTIM_PWM(TIMx);
  
    // Frequency is determined by value in TIMx_ARR register
    // Duty Cycle is determined by value in TIMx_CCR1,2 register 

    TIMx->TIM_ARR = freq - 1;
    TIMx->TIM_CCR2 = freq/2;              // 50% Duty Cycle
    TIMx->TIM_EGR |= (0b1 << 0 );         // Set UG bit to initialize/update registers
}

void pwmControl(uint32_t FreqDes){
    setPWM_Freq(TIM2, FreqDes);
}

void TIM_delay_millis(TIM_TypeDef * TIMx, uint32_t ms){

    if ((TIMx->TIM_CR1 & 1) != 1) initTIM(TIMx);

    TIMx->TIM_ARR = 100;
    TIMx->TIM_EGR |= 1;                   // Update registers
    TIMx->TIM_SR &= ~(0b1);               // Clear the update flag
    TIMx->TIM_CNT = 0;                        

    while (!(TIMx->TIM_SR & 1));          // Actual delay
}

void delay_millis(uint32_t ms){
    TIM_delay_millis(TIM15, ms);
}
