#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "stm32f10x.h"
#include "Configuration.h"

#ifdef USE_USART
#include "USART.h"
extern USART *pUSART1;
extern USART *pUSART2;
extern USART *pUSART3;
#endif

extern "C"{
	
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void DMA1_Channel4_IRQHandler(void);
void DMA1_Channel7_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);
	
}


#endif

