#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_dma.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_bus.h"
#include ".\DMA.H"						// OWN header


void DMA_Init(void)
{

  /* Init with LL driver */
  /* DMA controller clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  
}
