// Sebastian Heredia
// dheredia@g.hmc.edu
// September 29, 2025
// RCC.c contains code to implement RCC functions.

#include "RCC.h"

void configurePLL() {
    // Set clock to 80 MHz
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz
    // M: XX, N: XX, R: XX
    // Use MSI as PLLSRC

    // Turn off PLL
    RCC->CR &= ~(1 << 24);
    
    // Wait till PLL is unlocked (e.g., off)
    while ((RCC->CR >> 25 & 1) != 0);

    // Load configuration
    // Set PLL SRC to MSI
    RCC->PLLCFGR |= (1 << 0);
    RCC->PLLCFGR &= ~(1 << 1);

    // Set PLLN
    RCC->PLLCFGR &= ~(0b11111111 << 8);
    RCC->PLLCFGR |= ~(0b0101000 << 8);

    // Set PLLM
    RCC->PLLCFGR &= ~(0b111 << 4);

    // Set PLLR
    RCC->PLLCFGR &= ~(1 << 26);
    RCC->PLLCFGR |= (1 << 25);
    
    // Enable PLLR output
    RCC->PLLCFGR |= (1 << 24);

    // Enable PLL
    RCC->CR |= (1 << 24);
    
    // Wait until PLL is locked
    while ((RCC->CR >> 25 & 1) != 1);
}

void configureClock(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}
