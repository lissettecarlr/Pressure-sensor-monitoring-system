#include "stdlib.h"
#include "GPIO.h"
#include "USART.h"
#include "Interrupt.h"
#include "TaskManager.h"
#include "transmission.h"

/*DEFINE********************************************************/
/*设置*/
#define LEAVE					0x01
#define KEY     		  0x02
#define DELAY      	 0x03


/*END********************************************************/

USART SstCom(2,115200,true); 

GPIO Beep(GPIOB,13,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);



int main(){
	
	double record_state1=0;
	double record_state2=0;
	double record_state3=0;

	u8 state = 0 ; //当前状态 

	while(1)
	{		
		state=CMCT_Tool.GetStateOrder(SstCom);//监控设置模式

		switch(state)
		{
	/*离床超时报警*********************************************************************************/		
			case LEAVE:{
					Beep.SetLevel(1);
				while(1)
				{
					if(tskmgr.ClockTool(record_state1,1))
						CMCT_Tool.SendState(SstCom,1);
					if(CMCT_Tool.GetStateOrder(SstCom) == 3)
					{
						Beep.SetLevel(0);
						break;
					}
				}
			}break;
	/*END******************************************************************************************/
			
	/*按键报警*************************************************************************************/
			case KEY:{
					Beep.SetLevel(1);
				while(1)
				{
					if(tskmgr.ClockTool(record_state2,1))
						CMCT_Tool.SendState(SstCom,2);
					if(CMCT_Tool.GetStateOrder(SstCom) == 3)
					{
						Beep.SetLevel(0);
						break;
					}
				}
				
			}break;
	/*END******************************************************************************************/
			case DELAY:{
					Beep.SetLevel(0);
			}break;		
			
	/*常态******************************************************************************************/
			default:		
			{  	
					if(tskmgr.ClockTool(record_state3,1))
						CMCT_Tool.SendState(SstCom,3);
			}
	/*END******************************************************************************************/
			
		}		
	}
}

//测试命令：
/*
按键报警：  aa bb 01 02 ff 67
离床报警    aa bb 01 01 ff 66
解除报警    aa bb 01 03 ff 68

*/
