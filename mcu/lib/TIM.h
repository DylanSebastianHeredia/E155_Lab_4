// Sebastian Heredia
// dheredia@g.hmc.edu
// September 29, 2025
// TIM.h contains header file code for timer functions.

#ifndef TIM_H
#define TIM_H

#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Defining timer base addresses
#define TIM2_BASE (0x40000000UL)   // Base address for TIM2
#define TIM15_BASE (0x40014000UL)  // Base address for TIM15

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                           Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                           Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM follower mode control register,               Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/Interrupt enable register,                Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                              Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,                    Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,              Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,              Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,              Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter,                                      Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                                    Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                         Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register                   Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,                   Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,                   Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,                   Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,                   Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register                  Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                         Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer register,       Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< TIM option register 1,                            Address offset: 0x50 */
  uint32_t      RESERVED2;   /*!< Reserved,                                         Address offset: 0x54 */
  uint32_t      RESERVED3;   /*!< Reserved,                                         Address offset: 0x58 */
  uint32_t      RESERVED4;   /*!< Reserved,                                         Address offset: 0x5C */
  __IO uint32_t OR2;         /*!< TIM option register 2,                            Address offset: 0x60 */
} TIM_TypeDef;

#define TIM2 ((TIM_TypeDef *) TIM2_BASE)
#define TIM15 ((TIM_TypeDef *) TIM15_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIMx);
void PWM(uint32_t freqDes);
void delay_millis(uint32_t ms);

#endif
