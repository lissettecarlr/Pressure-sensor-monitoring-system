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


#ifdef USE_CAPTURE_EXIT0
extern InputCapture_EXIT *pICPExt0;
#endif
#ifdef USE_CAPTURE_EXIT1
extern InputCapture_EXIT *pICPExt1;
#endif
#ifdef USE_CAPTURE_EXIT2
extern InputCapture_EXIT *pICPExt2;
#endif
#ifdef USE_CAPTURE_EXIT3
extern InputCapture_EXIT *pICPExt3;
#endif
#ifdef USE_CAPTURE_EXIT4
extern InputCapture_EXIT *pICPExt4;
#endif
#ifdef USE_CAPTURE_EXIT5
extern InputCapture_EXIT *pICPExt5;
#endif
#ifdef USE_CAPTURE_EXIT6
extern InputCapture_EXIT *pICPExt6;
#endif
#ifdef USE_CAPTURE_EXIT7
extern InputCapture_EXIT *pICPExt7;
#endif
#ifdef USE_CAPTURE_EXIT8
extern InputCapture_EXIT *pICPExt8;
#endif
#ifdef USE_CAPTURE_EXIT9
extern InputCapture_EXIT *pICPExt9;
#endif
#ifdef USE_CAPTURE_EXIT10
extern InputCapture_EXIT *pICPExt10;
#endif
#ifdef USE_CAPTURE_EXIT11
extern InputCapture_EXIT *pICPExt11;
#endif
#ifdef USE_CAPTURE_EXIT12
extern InputCapture_EXIT *pICPExt12;
#endif
#ifdef USE_CAPTURE_EXIT13
extern InputCapture_EXIT *pICPExt13;
#endif
#ifdef USE_CAPTURE_EXIT14
extern InputCapture_EXIT *pICPExt14;
#endif
#ifdef USE_CAPTURE_EXIT15
extern InputCapture_EXIT *pICPExt15;
#endif

#ifdef USE_EXTI0
extern void	EXTI0_IRQ();
#endif
#ifdef USE_EXTI1
extern void	EXTI1_IRQ();
#endif
#ifdef USE_EXTI2
extern void	EXTI2_IRQ();
#endif
#ifdef USE_EXTI3
extern void	EXTI3_IRQ();
#endif
#ifdef USE_EXTI4
extern void	EXTI4_IRQ();
#endif
#ifdef USE_EXTI5
extern void	EXTI5_IRQ();
#endif
#ifdef USE_EXTI6
extern void	EXTI6_IRQ();
#endif
#ifdef USE_EXTI7
extern void	EXTI7_IRQ();
#endif
#ifdef USE_EXTI8
extern void	EXTI8_IRQ();
#endif
#ifdef USE_EXTI9
extern void	EXTI9_IRQ();
#endif
#ifdef USE_EXTI10
extern void	EXTI10_IRQ();
#endif
#ifdef USE_EXTI11
extern void	EXTI11_IRQ();
#endif
#ifdef USE_EXTI12
extern void	EXTI12_IRQ();
#endif
#ifdef USE_EXTI13
extern void	EXTI13_IRQ();
#endif
#ifdef USE_EXTI14
extern void	EXTI14_IRQ();
#endif
#ifdef USE_EXTI15
extern void	EXTI15_IRQ();
#endif


#endif

