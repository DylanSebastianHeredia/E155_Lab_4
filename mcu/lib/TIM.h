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

// Base addresses
#define TIM2_BASE (0x40000000UL)  // base address of TIM2
#define TIM15_BASE (0x40014000UL) // base address of TIM15

typedef struct
{
  __IO uint32_t TIM_CR1;            /*!< TIM control register 1,                           Address offset: 0x00 */
  __IO uint32_t TIM_CR2;            /*!< TIM control register 2,                           Address offset: 0x04 */
  __IO uint32_t TIM_SR;             /*!< TIM status register,                              Address offset: 0x10 */
  __IO uint32_t TIM_EGR;            /*!< TIM event generation register,                    Address offset: 0x14 */
  __IO uint32_t TIM_CCMR1;          /*!< TIM capture/compare mode register 1,              Address offset: 0x18 */
  __IO uint32_t TIM_CCMR2;          /*!< TIM capture/compare mode register 2,              Address offset: 0x1C */
  __IO uint32_t TIM_CCER;           /*!< TIM capture/compare enable register,              Address offset: 0x20 */
  __IO uint32_t TIM_CNT;            /*!< TIM counter,                                      Address offset: 0x24 */
  __IO uint32_t TIM_PSC;            /*!< TIM prescaler,                                    Address offset: 0x28 */
  __IO uint32_t TIM_ARR;            /*!< TIM auto-reload register,                         Address offset: 0x2C */
  __IO uint32_t TIM_CCR1;           /*!< TIM capture/compare register 1,                   Address offset: 0x34 */
  __IO uint32_t TIM_CCR2;           /*!< TIM capture/compare register 2,                   Address offset: 0x38 */
} TIM_TypeDef;

#define TIM2 ((TIM_TypeDef *) TIM2_BASE)
#define TIM15 ((TIM_TypeDef *) TIM15_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIMx);
void pwmControl(uint32_t freqDes);
void delay_millis(uint32_t ms);

#endif
