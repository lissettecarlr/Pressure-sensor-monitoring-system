#ifndef __ESP8266_H
#define __ESP8266_H



#include "TaskManager.h"
#include "USART.h"
#include "string.h"


#define ESP8266_RECEIVE_BUFFER_SIZE  1000
#define ESP8266_DEFAULT_TIMEOUT 3
class esp8266
{
	public:
		

			
		enum esp8266_pattern{esp8266_PATTERN_NULL=0,esp8266_PATTERN_CUR=1,esp8266_PATTERN_DEF=2};
		enum esp8266_MODE{esp8266_MODE_STATION=1,esp8266_MODE_AP=2,esp8266_MODE_STATION_AP=3};
		enum esp8266_ENCRYPTION{esp8266_ENCRYPTION_OPEN=0,esp8266_ENCRYPTION_WEP=1,esp8266_ENCRYPTION_WPA_PSK=2,esp8266_ENCRYPTION_WPA2_PSK=3,esp8266_ENCRYPTION_WPA_WPA2_PSK=4};
		enum esp8266_ROLE{esp8266_ROLE_SERVER=1,esp8266_ROLE_CLIENT=2};	
		void ClearBuffer();

		esp8266(USART &usart);
		bool kick(void); //OK？
		bool restart(void);	//复位
		bool setEcho(bool echo);	//是否返回显示
		bool SetMode(esp8266_MODE,esp8266_pattern = esp8266_PATTERN_DEF);//设置模式
		bool SetMUX(bool isEnableMUX);//选择是否开启多路访问
			
		bool JoinAP(char* apJoinSsid,char* apJoinPasswd);//加入AP
		bool CreateConnectMode(char* ipAddr,short port, signed char muxID = -1); //当muxID为-1 表示单路连接
			
			
		void Send(char ID,int Lenth,u8 data[]); //发送命令，前一个为ID号，后一个为发送字节长度
		void Send(int Lenth,u8 data[]); //发送命令，发送字节长度
	  void Send(char ID,char * str); 
		void Send(char * str); //发送命令，发送字节长度
	   
	  
//	//指令集
//	u8 ConnectNetwork_client(char *WifiName,char* WifiPassword,char *IP,int COM); //连接服务器
//	u8 ConnectNetwork_server(int port,int time);//作为服务器
	
	private:
		USART &mUsart;
		unsigned int mReceiveBufferIndex;
		char mReceiveBuffer[ESP8266_RECEIVE_BUFFER_SIZE];
	
		bool RecvFind(char const *target, unsigned char timeout=ESP8266_DEFAULT_TIMEOUT);
		bool RecvFind(char const *target,char const *target2, unsigned char timeout=ESP8266_DEFAULT_TIMEOUT);
		bool RecvFind(char const *target,char const *target2,char const *target3, unsigned char timeout=ESP8266_DEFAULT_TIMEOUT);
		bool RecvFindAndFilter(char const *target, char const * begin, char const * end, char* Data, float timeout=ESP8266_DEFAULT_TIMEOUT);
	
		bool ReceiveAndWait(char const* targetString,unsigned char timeOut=ESP8266_DEFAULT_TIMEOUT);
		bool ReceiveAndWait(char const* targetString,char const* targetString2,unsigned char timeOut=ESP8266_DEFAULT_TIMEOUT);
		bool ReceiveAndWait(char const* targetString,char const* targetString2,char const* targetString3,unsigned char timeOut=ESP8266_DEFAULT_TIMEOUT);
	  
};


#endif
