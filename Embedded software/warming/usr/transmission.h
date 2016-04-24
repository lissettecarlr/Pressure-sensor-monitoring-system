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

	public:
		Transmission();

		u8 CommandParsing(u8 command[6]);//命令协议校验解包
	
		u8 GetStateOrder(USART &ListeningCOM);//监听某个端口 返回命令字节

		void SendState(USART &COM,u8 state); 
		
};

extern Transmission CMCT_Tool;

#endif
