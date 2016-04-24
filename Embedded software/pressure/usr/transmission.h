#ifndef __TRANSMISSION_H
#define __TRANSMISSION_H

#include "stm32f10x.h"
#include "USART.h"
#include "esp8266.h"

/*define**************************************************/
#define BEDNO 0x01


/*END*****************************************************/



class Transmission{
	
	private:
		u8 MtoW[6];
		u8 MtoS[5];
		u8 WarmingModule;
	public:
		Transmission();
		u8 *MonitoringToWarning(u8 Command);  //监测模块-->预警模块
		u8 *MonitoringToServer(u8 BadState);  //监测模块-->服务器
	
		u8 CommandParsing(u8 command[6]);//命令协议校验解包
	
		u8 GetStateOrder(USART &ListeningCOM);//监听某个端口 返回命令字节
		u8 ListeningWarmingModule(USART &ListeningCOM);


		void SendAlive(esp8266 &esp); 
		
		bool GetWifiNameAndPassword(char *name,char *password,USART &ListeningCOM);
	
};

extern Transmission CMCT_Tool;

#endif
