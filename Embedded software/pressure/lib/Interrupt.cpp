#include "Interrupt.h"

#ifdef USE_USART
USART *pUSART1 = 0;
USART *pUSART2 = 0;
USART *pUSART3 = 0;

void USART1_IRQHandler(void)
{
	if(pUSART1)
		pUSART1->Irq();
}
void USART2_IRQHandler(void)
{
	if(pUSART2)
		pUSART2->Irq();
}
void USART3_IRQHandler(void)
{
	if(pUSART3)
		pUSART3->Irq();
}
#endif


void DMA1_Channel4_IRQHandler()
{	
#ifdef USE_USART
	if(pUSART1)
		pUSART1->DmaIrq();
#endif
}

void DMA1_Channel7_IRQHandler()
{	
#ifdef USE_USART
	if(pUSART2)
		pUSART2->DmaIrq();
#endif
}


void DMA1_Channel2_IRQHandler()
{	
#ifdef USE_USART
	if(pUSART3)
		pUSART3->DmaIrq();
#endif
}



#ifdef USE_CAPTURE_EXIT0
InputCapture_EXIT *pICPExt0;
#endif
#ifdef USE_CAPTURE_EXIT1
InputCapture_EXIT *pICPExt1;
#endif
#ifdef USE_CAPTURE_EXIT2
InputCapture_EXIT *pICPExt2;
#endif
#ifdef USE_CAPTURE_EXIT3
InputCapture_EXIT *pICPExt3;
#endif
#ifdef USE_CAPTURE_EXIT4
InputCapture_EXIT *pICPExt4;
#endif
#ifdef USE_CAPTURE_EXIT5
InputCapture_EXIT *pICPExt5;
#endif
#ifdef USE_CAPTURE_EXIT6
InputCapture_EXIT *pICPExt6;
#endif
#ifdef USE_CAPTURE_EXIT7
InputCapture_EXIT *pICPExt7;
#endif
#ifdef USE_CAPTURE_EXIT8
InputCapture_EXIT *pICPExt8;
#endif
#ifdef USE_CAPTURE_EXIT9
InputCapture_EXIT *pICPExt9;
#endif
#ifdef USE_CAPTURE_EXIT10
InputCapture_EXIT *pICPExt10;
#endif
#ifdef USE_CAPTURE_EXIT11
InputCapture_EXIT *pICPExt11;
#endif
#ifdef USE_CAPTURE_EXIT12
InputCapture_EXIT *pICPExt12;
#endif
#ifdef USE_CAPTURE_EXIT13
InputCapture_EXIT *pICPExt13;
#endif
#ifdef USE_CAPTURE_EXIT14
InputCapture_EXIT *pICPExt14;
#endif
#ifdef USE_CAPTURE_EXIT15
InputCapture_EXIT *pICPExt15;
#endif



extern "C"
{

//~~~~~~~~~~~~~~~~~~~~~~EXTI IQR  ~~~~~~~~~~~~~~~~~~//
void EXTI0_IRQHandler(void) 	  //----EXTI0 IRQ-----//
{
	EXTI_ClearITPendingBit(EXTI_Line0);
#ifdef USE_EXTI0
	EXTI0_IRQ();
#endif
	
#ifdef USE_ULTRASONIC_EXTI0
	pUltExt0->IRQ();
#endif

#ifdef USE_CAPTURE_EXIT0
	pICPExt0->IRQ();
#endif
}
void EXTI1_IRQHandler(void) 	  //----EXTI1 IRQ-----//
{
	EXTI_ClearITPendingBit(EXTI_Line1);
#ifdef USE_EXTI1
	EXTI1_IRQ();
#endif
	
#ifdef USE_ULTRASONIC_EXTI1
	pUltExt1->IRQ();
#endif
	
#ifdef USE_CAPTURE_EXIT1
	pICPExt1->IRQ();
#endif
}
void EXTI2_IRQHandler(void) 	  //----EXTI2 IRQ-----//
{
	EXTI_ClearITPendingBit(EXTI_Line2);
#ifdef USE_EXTI2
	EXTI2_IRQ();
#endif
	
#ifdef USE_ULTRASONIC_EXTI2
	pUltExt2->IRQ();
#endif
	
#ifdef USE_CAPTURE_EXIT2
	pICPExt2->IRQ();
#endif
}
void EXTI3_IRQHandler(void) 	  //----EXTI3 IRQ-----//
{
	EXTI_ClearITPendingBit(EXTI_Line3);
#ifdef USE_EXTI3
	EXTI3_IRQ();
#endif
	
#ifdef USE_ULTRASONIC_EXTI3
	pUltExt3->IRQ();
#endif
	
#ifdef USE_CAPTURE_EXIT3
	pICPExt3->IRQ();
#endif
}
void EXTI4_IRQHandler(void) 	  //----EXTI4 IRQ-----//
{
	EXTI_ClearITPendingBit(EXTI_Line4);
#ifdef USE_EXTI4
	EXTI4_IRQ();

#endif
	
#ifdef USE_ULTRASONIC_EXTI4
	pUltExt4->IRQ();
#endif
	
#ifdef USE_CAPTURE_EXIT4
	pICPExt4->IRQ();
	//
#endif
}

void EXTI9_5_IRQHandler(void) 	//---EXTI9_5 IRQ----//
{
	if(EXTI_GetITStatus(EXTI_Line5))       //--EXTI5--//
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
	#ifdef USE_EXTI5
		EXTI5_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI5
		pUltExt5->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT5
		pICPExt5->IRQ();
	#endif
	}
	if(EXTI_GetITStatus(EXTI_Line6))       //--EXTI6--//
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
	#ifdef USE_EXTI6
		EXTI6_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI6
		pUltExt6->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT6
		pICPExt6->IRQ();
					
	#endif
	}	
	if(EXTI_GetITStatus(EXTI_Line7))       //--EXTI7--//
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
	#ifdef USE_EXTI7
		EXTI7_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI7
		pUltExt7->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT7
		pICPExt7->IRQ();
	#endif
	}	
	if(EXTI_GetITStatus(EXTI_Line8))       //--EXTI8--//
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
	#ifdef USE_EXTI8
		EXTI8_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI8
		pUltExt8->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT8
		pICPExt8->IRQ();
	#endif
	}
	if(EXTI_GetITStatus(EXTI_Line9))       //--EXTI9--//
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
	#ifdef USE_EXTI9
		EXTI9_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI9
		pUltExt9->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT9
		pICPExt9->IRQ();
	#endif
	}
	
}
void EXTI15_10_IRQHandler(void) //---EXTI15_10 IRQ--//
{
	if(EXTI_GetITStatus(EXTI_Line10))     //--EXTI10--//
	{
		EXTI_ClearITPendingBit(EXTI_Line10); 
	#ifdef USE_EXTI10
		EXTI10_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI10
		pUltExt10->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT10
	pICPExt10->IRQ();
	#endif
	}
	
	if(EXTI_GetITStatus(EXTI_Line11))     //--EXTI11--//
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
	#ifdef USE_EXTI11
		EXTI11_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI11
		pUltExt11->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT11
		pICPExt11->IRQ();
	#endif
	}
	
	if(EXTI_GetITStatus(EXTI_Line12))     //--EXTI12--//
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
	#ifdef USE_EXTI12
		EXTI12_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI12
		pUltExt12->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT12
		pICPExt12->IRQ();
	#endif
	}
	
	if(EXTI_GetITStatus(EXTI_Line13))     //--EXTI13--//
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
	#ifdef USE_EXTI13
		EXTI13_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI13
		pUltExt13->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT13
		pICPExt13->IRQ();
	#endif
	}
	
	if(EXTI_GetITStatus(EXTI_Line14))     //--EXTI14--//
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
	#ifdef USE_EXTI14
		EXTI14_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI14
		pUltExt14->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT14
		pICPExt14->IRQ();
	#endif
	}
	
	if(EXTI_GetITStatus(EXTI_Line15))     //--EXTI15--//
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
	#ifdef USE_EXTI15
		EXTI15_IRQ();
	#endif
		
	#ifdef USE_ULTRASONIC_EXTI15
		pUltExt15->IRQ();
	#endif
		
	#ifdef USE_CAPTURE_EXIT15
		pICPExt15->IRQ();
	#endif
	}
}

}








