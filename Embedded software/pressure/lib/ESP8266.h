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
		esp8266(USART &usart);
		bool kick(void); //OK？
		bool restart(void);	//复位
		bool setEcho(uint8_t mode);	//是否返回显示
		bool setOprToStation();//设置为从模式
		bool setOprToSoftAP();//设置为主模式
		bool setOprToStationSoftAP();//设置为主从模式
	  bool joinAP( char* ssid,  char* pwd);//连入WIFI
		//设置AP模式下的参数 ，  名字、密码、通道、加密方式
    bool setSoftAPParam( char* ssid,  char* pwd, uint8_t chl = 7, uint8_t ecn = 4);
	  bool enableOrDisableMUX(u8 choose);//选择是否开启多路访问
		bool ConnectServer(char*  type, char*  addr, int port); //在为开启多路访问下链接服务器
    bool ConnectServerID(int mux_id, char*  type, char*  addr, int port);//连接到服务器(由于多路访问，需要选择ID号)
		void Send(char ID,int Lenth,u8 data[]); //发送命令，前一个为ID号，后一个为发送字节长度
		void Send(int Lenth,u8 data[]); //发送命令，发送字节长度
	  void Send(char ID,char * str); 
		void Send(char * str); //发送命令，发送字节长度
	   
	  bool SetTimeout(int time); //设置超时时间 0表示永不超时
   	bool OpenServer(int port); //开启服务模式
	
		bool SetIpAddr(char* str); //设置IP地址
   		
	//指令集
	u8 ConnectNetwork_client(char *WifiName,char* WifiPassword,char *IP,int COM); //连接服务器
	u8 ConnectNetwork_server(int port,int time);//作为服务器
	
	private:
		USART &mUsart;
		FIFOBuffer<char,ESP8266_RECEIVE_BUFFER_SIZE> mReceiveBuffer;
	
		void rx_empty();//清空发送缓存
		char* recvString(char const *target, float timeout = ESP8266_DEFAULT_TIMEOUT);//当接收数据为target时返回接收的数据
		char* recvString(char const *target1, const char* target2, float timeout = ESP8266_DEFAULT_TIMEOUT);//两者之一
		char* recvString(char const *target1, const char* target2, const char* target3, float timeout = ESP8266_DEFAULT_TIMEOUT);//三者之一
		bool recvFind(char const *target, float timeout = ESP8266_DEFAULT_TIMEOUT);//寻找target 有则返回true
		bool recvFindAndFilter(char const *target, char const * begin, char const * end, char** data, float timeout = ESP8266_DEFAULT_TIMEOUT);
	  
};


#endif
