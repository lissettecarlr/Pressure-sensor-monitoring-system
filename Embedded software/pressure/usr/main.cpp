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

#define SERVER_IP				"113.250.96.222"                      //"120.27.119.115"
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

u8 SendWaring(int order,int ToModuleOrder);

int main(){
	
	SystemInit();
	u8 order=0;
	double record_getwifi=0; //wifi命令时间记录
	double record_monitoring_cycle=0;//离床时间监控记录
	double record_getModuleState = 0 ;//得到模块状态监控间隔
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
//	if(wifimemory.getWifiSum()!=0)//判断表中是否已经保存wifi信息
//	{
//		while( wifimemory.Load(WifiName,WifiPassword) )
//		 {
//				SstCom<<"connet "<<WifiName<<"\n";
//			  if(wifi.ConnectNetwork_client(WifiName,WifiPassword,SERVER_IP,SERVER_COM)) //每次连接历时20秒
//				{
//					SstCom<<"connet succeed"<<"\n";
//					network=true;  
//					break;
//				}
//				else
//					SstCom<<"connet fail!"<<"\n";
//		 }
//		 if(network ==false) {
//		 }
//	}
//  else
//	{
//	}
		
		if(wifi.CreateConnectMode(SERVER_IP,SERVER_COM))
		{
			SstCom<<"connet succeed"<<"\n";
			network=true;  
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
		
		if(tskmgr.ClockTool(record_getModuleState,10)) //一秒检查一次
		if(!network)	//如果没网
			warmingModuleState=CMCT_Tool.ListeningWarmingModule(SeriaNet); //监控预警模块状态
	
		if(warning.LeaveState == true && warmingModuleState ==3)//当检测到需要报警且报警模块处于待机状态
		{
			//报警处理
			if(network)
			{
				u8 tempRelay1 = SendWaring(1,2);
				if(tempRelay1 == 2 || tempRelay1 ==1) //如果被拒绝
				{
					warmingModuleState =2; //标记为待机状态
//					tskmgr.DelayS(5);
				}
			}
			else
			{
				
			}

		}
		
		if(warning.LeaveState == false && warmingModuleState ==2)//当检测到解除报警且报警模块处于报警状态
		{
			if(network)
			{
				u8 tempRelay2 = SendWaring(2,3);
				if(tempRelay2 == 2 ||tempRelay2 ==1) //如果被拒绝
					warmingModuleState =3; //标记为待机状态
			}
			else
			{
				
			}
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
//							wifimemory.Save(WifiName,WifiPassword);
							SstCom<<"send success ,please wait . . . ."<<"\n";
							if(wifi.JoinAP(WifiName,WifiPassword))
									SstCom<<"join wifi success :"<<WifiName<<"\n";
							else
									SstCom<<"join wifi fail :"<<WifiName<<"\n";
							break;
						}
						if(tskmgr.ClockTool(record_getwifi,30)) //超时60秒退出
						{
						  	SstCom<<"outtime quit !!"<<"\n";
								break;
						}
					}
			}break;
	/*END******************************************************************************************/
			
	/*设置阀值*************************************************************************************/
			case SETOUTTIME:{
				 u8 ch =0;
				 while(1)
				 {
						if(SstCom.ReceiveBufferSize()>=4)
						{
							SstCom.GetReceivedData(&ch,1);
						if(ch == 0xaa)
						{
								SstCom.GetReceivedData(&ch,1);
							if(ch == 0x01)
								SstCom.GetReceivedData(&ch,1);
						}						
								LeaveOutTime =ch;
							SstCom<<"set succeed :Timeout = "<<LeaveOutTime<<"\n";
							break;
						}
						if(tskmgr.ClockTool(record_outtime,30)) //超时60秒退出
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
								wifi.Send(5,CMCT_Tool.MonitoringToServer(2));
							SstCom<<"leave bed!"<<"\n";
						}
						if(pressure[1]>threshold_state && BedState == false)  //离床期间
						{
							 if(tskmgr.ClockTool(LeaveTime,LeaveOutTime))  //离床超过了阀值
							 {
							   //报警处理
								 SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(1),6);
//								 if(SendWaring(1,1))
										SstCom<<"outtime ! send warning"<<"\n";
							 }
						}
						
						if(pressure[1]<threshold_state && BedState == false) //上床
						{
							BedState = true ;
							//发送上床记录
							if(network)
								wifi.Send(5,CMCT_Tool.MonitoringToServer(1));
							  SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(3),6);//解除报警	
//								if(SendWaring(2,3))						
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
//order:发送给服务器的请求命令  1：请求预警 2：请求停止
//ToModuleOrder：发送给预警模块的命令 1-超时报警  2-手动报警  3-解除报警
u8 SendWaring(int order,int ToModuleOrder)
{
		u8 replay=0;
		double oldtime = 0,nowtime=0;
		wifi.Send(5,CMCT_Tool.requestWarning(order,1));
		tskmgr.DelayMs(200);
		oldtime = tskmgr.Time();
		while(1) 
		{
			 nowtime = tskmgr.Time();
			 replay=CMCT_Tool.GetReplay(WIFI);
			 if(replay ==1 ||replay ==2)
				 break;
			if(nowtime - oldtime>5)
			{
				replay=0xff;
				break;
			}
		}
		
		if(replay == 1) //如果允许
				SeriaNet.SendData(CMCT_Tool.MonitoringToWarning(ToModuleOrder),6);
		else if(replay == 0xff)
			{
				SstCom<<"outtime!!"<<"\n";
			}
		else
			{
				SstCom<<"Forbidden send!!"<<"\n";
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

