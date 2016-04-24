#include "stdlib.h"
#include "ADC.h"
#include "GPIO.h"
//#include "Timer.h"
#include "USART.h"
#include "Memory.h"
#include "Interrupt.h"
#include "TaskManager.h"
#include "transmission.h"
#include "ESP8266.h"
#include "Hint.h"
#include "WIFI_Memory.h"
#include "key.h"

/*DEFINE********************************************************/
/*设置*/
#define GETWIFI					0x01
#define SETOUTTIME      0x02
#define RST							0xff
#define CLEARWIFI       0x03

/*状态*/

#define MODULE_IP 			"192.168.1.1"   
#define MODULE_COM			9000
#define SERVER_IP				"113.250.110.241"                          //"120.27.119.115"
#define SERVER_COM 			1111

/*状态判断的阀值*/
#define threshold_state   3  //小于该值，判断有人，大于该值判断无人



/*END********************************************************/

USART SstCom(1,115200,true); 
USART SeriaNet(2,115200,true);   //USART1  433模块
USART WIFI(3,115200,true);   //USART3  ESP8266模块

GPIO Beep(GPIOB,5,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
GPIO Led_red(GPIOB,8,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
GPIO Led_green(GPIOB,7,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);

ADC pressure(1); //PA1读取AD值



Memory InfoStore(0x08000000+100*MEMORY_PAGE_SIZE,true);//ip存储，长度+IP地址的存档格式，先读取出字符串长度
WifiMemory wifimemory(InfoStore);

Key warning(GPIOB,0);

esp8266 wifi(WIFI);

hint Hint(Led_red,Beep);

void EXTI0_IRQ()
{
	warning.IRQ();
}

int main(){
	
	u8 order=0;
	double record_getwifi=0;
	double record_monitoring_cycle=0;
	double record_alive = 0;
	double record_outtime =0;
	
	bool MonitoringState = false ; //离床监控状态标志位，false为关闭
	
	bool BedState = false ;//床位状态标识位 false 离床
	
	double LeaveTime = 0; //离床时间 
	
	double LeaveOutTime = 10 ; //离床最长时间
	
//	bool KeyHint = false ;
	
	u8 warmingModuleState = 3; //预警模块状态 3表示待机 1表示离床报警 2表示按键报警
	
	bool network=false ; //网络连接标识位 
	char *ip = (char*)calloc(15, sizeof(char*) ); 
	char *WifiName = (char*)calloc(20, sizeof(char*) ); 
	char *WifiPassword = (char*)calloc(20, sizeof(char*) ); 

/*开机WIFI模式选择*****************************************************************/
	if(wifimemory.getWifiSum()!=0)//判断表中是否已经保存wifi信息
	{
		while( wifimemory.Load(WifiName,WifiPassword) )
		 {
			  if(wifi.ConnectNetwork_client(WifiName,WifiPassword,SERVER_IP,1111)) //每次连接历时20秒
				{network=true;   break;}
		 }
		 if(network ==false) {
			  wifi.ConnectNetwork_server(MODULE_COM,0);
			 	WIFI.ClearReceiveBuffer();
		 }
	}
  else
	{
		 wifi.ConnectNetwork_server(MODULE_COM,0);
			WIFI.ClearReceiveBuffer();
	}
	
/*END*********************************************************************************/	
	

/*Hint********************************************************************************/
	if(!network)
		Led_red.SetLevel(1); 
	
/*END********************************************************************************/	
	
	while(1)
	{		
		order=CMCT_Tool.GetStateOrder(SstCom);//监控设置模式
		warmingModuleState=CMCT_Tool.ListeningWarmingModule(SeriaNet); //监控预警模块状态
	
		if(warning.LeaveState == true && warmingModuleState ==3)
		{
			//报警处理
			SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(2),6);
			tskmgr.DelayS(1);
		}
		if(warning.LeaveState == false && warmingModuleState ==2)
		{
			//解除报警
			SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(3),6);
			tskmgr.DelayS(1);
		}
		
		
		if(network)
			if(tskmgr.ClockTool(record_alive,30))//30秒发送一次存活确认
				CMCT_Tool.SendAlive(wifi);
		
			
		switch(order)
		{
	/*获取WIFI信息*********************************************************************************/		
			case GETWIFI:{//得到wifi账号密码
				record_getwifi=tskmgr.Time();
					while(1)
					{
						if(CMCT_Tool.GetWifiNameAndPassword(WifiName,WifiPassword,WIFI) )
						{
							//保存WIFI账号密码
							wifimemory.Save(WifiName,WifiPassword);
								break;
						}
						if(tskmgr.ClockTool(record_getwifi,60)) //超时60秒退出
						   break;
					}
			}break;
	/*END******************************************************************************************/
			
	/*设置阀值*************************************************************************************/
			case SETOUTTIME:{
				 u8 temp[4];
				 while(1)
				 {
						if(SstCom.ReceiveBufferSize()>=4)
						{
							SstCom.GetReceivedData(temp,4);
							u8 sum = temp[0]+temp[1]+temp[2];
							if(sum == temp[3])
								LeaveOutTime = temp[2];
							break;
						}
						if(tskmgr.ClockTool(record_outtime,60)) //超时60秒退出
							break;
				 }
			}break;
	/*END******************************************************************************************/
			
			
	 /*复位******************************************************************************************/
			case RST:{//复位
					wifimemory.ClearAllData(); //清空所有保存信息
					*((u32 *)0xE000ED0C) = 0x05fa0004;
			}break;
	/*END******************************************************************************************/
		
					
	 /*清空wifi信息******************************************************************************************/
			case CLEARWIFI:{//复位
					wifimemory.ClearAllData(); //清空所有保存信息
			}break;
	/*END******************************************************************************************/	
		
	/*常态******************************************************************************************/
			default:		
			{  
				//监控程序
				if(MonitoringState) //如果开启了监控
				{
					if(tskmgr.ClockTool(record_monitoring_cycle,1)) //一秒检查一次
					{
				    if(pressure[1]>threshold_state && BedState == true)  //离床
						{
							 //记录时间
							LeaveTime = tskmgr.Time();
							//修改当前床铺状态
							BedState = false ;
							//发送离床信息记录
							if(network)
								wifi.Send(5,CMCT_Tool.MonitoringToServer(2));
						}
						if(pressure[1]>threshold_state && BedState == false)  //离床期间
						{
							 if(tskmgr.ClockTool(LeaveTime,LeaveOutTime))  //离床超过了阀值
							 {
							   //报警处理
								 SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(1),6);
							 }
						}
						
						if(pressure[1]<threshold_state && BedState == false) //上床
						{
							BedState = true ;
							//发送上床记录
							if(network)
								wifi.Send(5,CMCT_Tool.MonitoringToServer(1));
						}
											
					}
				}
				else //如果未开启监控
				{
				   
				}
				
			}
	/*END******************************************************************************************/
			
		}		
	}
}


