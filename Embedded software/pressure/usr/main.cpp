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
#define GETWIFI					0x01  //获取wifi
#define SETOUTTIME      0x02  //设置阀值
#define RST							0xff	//复位
#define CLEARWIFI       0x03	//清空wifi信息

/*状态*/

#define SERVER_IP				"113.250.97.197"                          //"120.27.119.115"
#define SERVER_COM 			9999    

/*状态判断的阀值*/
#define threshold_state   3  //小于该值，判断有人，大于该值判断无人



/*END********************************************************/

USART SstCom(1,115200,true); 
USART SeriaNet(2,115200,true);   //USART1  433模块
USART WIFI(3,115200,true);   //USART3  ESP8266模块

GPIO Beep(GPIOB,5,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
GPIO Led_red(GPIOB,8,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
GPIO Led_green(GPIOB,7,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);

GPIO MonitoringState_switch(GPIOB,1,GPIO_Mode_IPD,GPIO_Speed_50MHz);

ADC pressure(1); //PA1读取AD值



Memory InfoStore(0x08000000+100*MEMORY_PAGE_SIZE,true);//ip存储，长度+IP地址的存档格式，先读取出字符串长度
WifiMemory wifimemory(InfoStore);

Key warning(GPIOB,0);

esp8266 wifi(WIFI);

hint Hint(Led_green,Beep);

void EXTI0_IRQ()
{
	warning.IRQ();
}

int main(){
	
	SystemInit();
	u8 order=0;
	double record_getwifi=0; //wifi命令时间记录
	double record_monitoring_cycle=0;//离床时间监控记录
//	double record_alive = 0; //存在确认命令时间记录
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
		tskmgr.DelayS(2);
	if(wifimemory.getWifiSum()!=0)//判断表中是否已经保存wifi信息
	{
		while( wifimemory.Load(WifiName,WifiPassword) )
		 {
				SstCom<<"connet "<<WifiName<<"\n";
			  if(wifi.ConnectNetwork_client(WifiName,WifiPassword,SERVER_IP,SERVER_COM)) //每次连接历时20秒
				{
					SstCom<<"connet succeed"<<"\n";
					network=true;  
					break;
				}
				else
					SstCom<<"connet fail!"<<"\n";
		 }
		 if(network ==false) {
		 }
	}
  else
	{
	}
	
/*END*********************************************************************************/	
	

	/*Hint**红灯亮起则表明未连上服务器***************************************************/
	if(!network)
		Led_red.SetLevel(1); 
	else
		{
				for(int i=0;i<5;i++)
				{
						Led_red.SetLevel(1);
						tskmgr.DelayMs(200);
						Led_red.SetLevel(0);
						tskmgr.DelayMs(200);
				}
		}
	
/*END********************************************************************************/	
	
	
	
	while(1)
	{		
		order=CMCT_Tool.GetStateOrder(SstCom);//监控设置模式
		warmingModuleState=CMCT_Tool.ListeningWarmingModule(SeriaNet); //监控预警模块状态
	
		if(warning.LeaveState == true && warmingModuleState ==3)//当检测到需要报警且报警模块处于待机状态
		{
			//报警处理
			SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(2),6);
			tskmgr.DelayS(1);
		}
		
		if(warning.LeaveState == false && warmingModuleState ==2)//当检测到解除报警且报警模块处于报警状态
		{
			//解除报警
			SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(3),6);
			tskmgr.DelayS(1);
		}
		
//		if(network)
//			if(tskmgr.ClockTool(record_alive,30))//30秒发送一次存活确认
//			{
//				CMCT_Tool.SendAlive(wifi);
////				Hint.led_NO_1ms();
//			}
		
/*离床监测是否开启判断，插上跳线帽则开启******************************************************/
		if(MonitoringState_switch.GetLevel() == 1)
				MonitoringState = true;
		else 
				MonitoringState = false;
/*END*****************************************************************************************/
		
		if(MonitoringState && !BedState) //如果启动了监控且离床了 则将绿灯点亮
			Led_green.SetLevel(1);
		else 
			Led_green.SetLevel(0);
		
		
		switch(order)
		{
	/*获取WIFI信息*********************************************************************************/		
			case GETWIFI:{//得到wifi账号密码
				record_getwifi=tskmgr.Time();
					while(1)
					{
						if(CMCT_Tool.GetWifiNameAndPassword(WifiName,WifiPassword,SstCom) )
						{
							//保存WIFI账号密码
							wifimemory.Save(WifiName,WifiPassword);
							SstCom<<"save wifi massage :"<<WifiName<<"\n";
							break;
						}
						if(tskmgr.ClockTool(record_getwifi,60)) //超时60秒退出
						{
						  	SstCom<<"outtime quit !!"<<"\n";
								break;
						}
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
							SstCom<<"set succeed :Timeout = "<<LeaveOutTime<<"\n";
							break;
						}
						if(tskmgr.ClockTool(record_outtime,60)) //超时60秒退出
						{
							SstCom<<"outtime quit !!"<<"\n";
							break;
						}
				 }
			}break;
	/*END******************************************************************************************/
			
			
	 /*复位******************************************************************************************/
			case RST:{//复位
					SstCom<<"restoration !!"<<"\n";
					tskmgr.DelayMs(200);
					*((u32 *)0xE000ED0C) = 0x05fa0004;
			}break;
	/*END******************************************************************************************/
		
					
	 /*清空wifi信息******************************************************************************************/
			case CLEARWIFI:{
					wifimemory.ClearAllData(); //清空所有保存信息
					SstCom<<"clear wifi massage"<<"\n";
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
								wifi.Send(0,5,CMCT_Tool.MonitoringToServer(2));
							SstCom<<"leave bed!"<<"\n";
						}
						if(pressure[1]>threshold_state && BedState == false)  //离床期间
						{
							 if(tskmgr.ClockTool(LeaveTime,LeaveOutTime))  //离床超过了阀值
							 {
							   //报警处理
								 SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(1),6);
								 SstCom<<"outtime ! send warning"<<"\n";
							 }
						}
						
						if(pressure[1]<threshold_state && BedState == false) //上床
						{
							BedState = true ;
							//发送上床记录
							if(network)
								wifi.Send(0,5,CMCT_Tool.MonitoringToServer(1));
							SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(3),6);//解除报警				
							SstCom<<"go to bed!"<<"\n";
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


//防冲突的预警命令发送方式
u8 SendWaring(int order)
{
		u8 replay=0;
		int oldtime = 0,nowtime=0;
		wifi.Send(0,5,CMCT_Tool.requestWarning(order,1));
		tskmgr.DelayMs(200);
		oldtime = tskmgr.Time();
		while(1) 
		{
			 nowtime = tskmgr.Time();
			 replay=CMCT_Tool.GetReplay(WIFI);
			 if(replay)
				 break;
			if(nowtime - oldtime>1)
			{
				replay=0xff;
				break;
			}
		}
		return replay;
		
//			switch(order)
//			{
//				case 0x01:
//						{return 1;}break; //允许
//				
//				case 0x02:
//						{return 2;}break;//拒绝
//				
//				case 0xff:
//					{return 0xff;}break;//超时
//			}

}

