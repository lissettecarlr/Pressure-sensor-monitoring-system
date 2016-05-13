#include "ESP8266.h"

esp8266::esp8266(USART &usart)
:mUsart(usart)
{
	
}


void esp8266::ClearBuffer()
{
	unsigned int i=0;
	for(;i<ESP8266_RECEIVE_BUFFER_SIZE;++i)
		mReceiveBuffer[i]=0;
}

/*********************************************************************************************/
	bool esp8266::kick(void)
{
	mUsart<<"AT\r\n";
	return RecvFind("OK");
}

	bool esp8266::restart(void)
{
	mUsart<<"AT+RST\r\n";
	return RecvFind("OK");
}


//是否回显 1 是 0 
bool esp8266::setEcho(bool echo)
{
	mUsart<<"ATE"<<(echo?1:0)<<"\r\n";
	return RecvFind("OK");
}



bool esp8266::SetMode(esp8266_MODE mode,esp8266_pattern pattern)
{
	if(pattern>esp8266_PATTERN_DEF)
		return false;
		
	if(pattern == esp8266_PATTERN_CUR)
	{
		mUsart<<"AT+CWMODE_CUR=";
	}
	else if(pattern == esp8266_PATTERN_DEF)
	{
		mUsart<<"AT+CWMODE_DEF=";
	}
	else
	{
		mUsart<<"AT+CWMODE=";
	}
	mUsart<<(int)mode<<"\r\n";
	if(!ReceiveAndWait("OK", "ERROR"))
		return false;
	if(strstr(mReceiveBuffer,"OK"))
		return true;
	return false;
}


bool esp8266::SetMUX(bool isEnableMUX)
{
	mUsart<<"AT+CIPMUX="<<(isEnableMUX?1:0)<<"\r\n";							
	return RecvFind("OK");
}

bool esp8266::JoinAP(char* apJoinSsid,char* apJoinPasswd)
{

	mUsart<<"AT+CWJAP=";

	mUsart<<"\""<<apJoinSsid<<"\",\""<<apJoinPasswd<<"\"\r\n";
	if(!ReceiveAndWait("OK", "ERROR",20))
		return false;
	if(strstr(mReceiveBuffer,"OK"))
		return true;
	return false;
}

bool esp8266::CreateConnectMode(char* ipAddr,short port, signed char muxID)
{
	char type[4]="TCP";

	if(muxID!=-1)
		mUsart<<"AT+CIPSTART="<<muxID<<",\""<<type<<"\",\""<<ipAddr<<"\","<<port<<"\r\n";							
	else
		mUsart<<"AT+CIPSTART="<<"\""<<type<<"\",\""<<ipAddr<<"\","<<port<<"\r\n";							
	return RecvFind("OK","ALREAY CONNECT");
}




void esp8266::Send(char ID,int Lenth,u8 data[])
{
	ID=ID+48;//将数字转化为字符
	//Lenth=Lenth+48;
	mUsart<<"AT+CIPSEND=";
	mUsart<<ID<<","<<Lenth<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart.SendData(data,Lenth);
}

void esp8266::Send(int Lenth,u8 data[])
{
	mUsart<<"AT+CIPSEND=";
	mUsart<<Lenth<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart.SendData(data,Lenth);
}

void esp8266::Send(char ID,char * str)
{
	u8 number=0;
	while( (*str)!= '\0')
		{number++;str++;}	
	mUsart<<"AT+CIPSEND=";
	mUsart<<ID<<","<<number<<"\r\n";	
	tskmgr.DelayMs(100);	
	mUsart<<(str-number);
}

void esp8266::Send(char * str)
{
	u8 number=0;
	while( (*str)!= '\0')
		{number++;str++;}
	
	mUsart<<"AT+CIPSEND=";
	mUsart<<number<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart<<(str-number);
}





/// new add 
bool esp8266::RecvFind(char const *target, unsigned char timeout)
{
	if(!ReceiveAndWait((char*)target,timeout))
		return false;
	return true;
}
bool esp8266::RecvFind(char const *target, char const *target2,unsigned char timeout)
{
	if(!ReceiveAndWait((char*)target,target2,timeout))
		return false;
	return true;
}
bool esp8266::RecvFind(char const *target, char const *target2,char const *target3,unsigned char timeout)
{
	if(!ReceiveAndWait((char*)target,target2,target3,timeout))
		return false;
	return true;
}

bool esp8266::RecvFindAndFilter(char const *target, char const * begin, char const * end, char* Data, float timeout)
{
	if(!ReceiveAndWait((char*)target,timeout))
		return false;
	char* index1=strstr(mReceiveBuffer,begin);
	char* index2=strstr(mReceiveBuffer,end);

	if(index1&&index2)
	{
		index1+=strlen(begin);
		*index2='\0';
		strcpy(Data,index1);
		return true;
	}
	return false;
}

bool esp8266::ReceiveAndWait(char const* targetString,const char* targetString2,const char* targetString3,unsigned char timeOut)
{
		u8 temp;
		mReceiveBufferIndex = 0;
		ClearBuffer();
		double tartTime=TaskManager::Time();
		while((TaskManager::Time()-tartTime)<timeOut)
		{
			while(mUsart.ReceiveBufferSize()>0)
			{
				mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
				if(temp=='\0')
					continue;
				mReceiveBuffer[mReceiveBufferIndex++] = temp;//放入esp的缓冲区
				
			}
			
			if(strstr(mReceiveBuffer,targetString) ||
			   strstr(mReceiveBuffer,targetString2)||
			   strstr(mReceiveBuffer,targetString3))
				return true;	
				
		}
		if(mReceiveBufferIndex>0)//接收到了数据，加上结束标志
		{
			mReceiveBuffer[mReceiveBufferIndex] = '\0';
		}
		return false;
}

bool esp8266::ReceiveAndWait(const char* targetString,unsigned char timeOut)
{
		u8 temp;
		mReceiveBufferIndex = 0;
		ClearBuffer();
		double tartTime=TaskManager::Time();
		while((TaskManager::Time()-tartTime)<timeOut)
		{
			while(mUsart.ReceiveBufferSize()>0)
			{
				mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
				if(temp=='\0')
					continue;
				mReceiveBuffer[mReceiveBufferIndex++] = temp;//放入esp的缓冲区
				
			}
			
			if(strstr(mReceiveBuffer,targetString))
				return true;	
				
		}
		if(mReceiveBufferIndex>0)//接收到了数据，加上结束标志
		{
			mReceiveBuffer[mReceiveBufferIndex] = '\0';
		}
		return false;
}
bool esp8266::ReceiveAndWait(char const* targetString,const char* targetString2,unsigned char timeOut)
{
		u8 temp;
		mReceiveBufferIndex = 0;
		ClearBuffer();
		double tartTime=TaskManager::Time();
		while((TaskManager::Time()-tartTime)<timeOut)
		{
			while(mUsart.ReceiveBufferSize()>0)
			{
				mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
				if(temp=='\0')
					continue;
				mReceiveBuffer[mReceiveBufferIndex++] = temp;//放入esp的缓冲区
				
			}
			
			if(strstr(mReceiveBuffer,targetString) ||
			   strstr(mReceiveBuffer,targetString2))
				return true;	
				
		}
		if(mReceiveBufferIndex>0)//接收到了数据，加上结束标志
		{
			mReceiveBuffer[mReceiveBufferIndex] = '\0';
		}
		return false;
}







/*******************************************************************************************/
//u8 esp8266::ConnectNetwork_client(char *WifiName,char* WifiPassword,char *IP,int COM) //预计耗时26秒
//{
//	//网络连接
//	if(!kick())
//		return 0;
//	tskmgr.DelayMs(1000);
//	setEcho(1);//回显
//	tskmgr.DelayMs(1000);
//	setOprToStation();//设置为模式1
//	tskmgr.DelayMs(500);
//	restart();
//	tskmgr.DelayS(3);
//	if(!joinAP(WifiName,WifiPassword))
//		return 0;//WIFI连接 如果连接失败，返回0
//	//enableOrDisableMUX(1);
//	if( !ConnectServer("TCP",IP,COM) ) return false;  //服务器连接
//	return 1;
//}

//u8 esp8266::ConnectNetwork_server(int port,int time) //预计耗时7秒
//{
//	if(!kick())
//		return 0;
//	tskmgr.DelayMs(1000);
//	setOprToSoftAP();
//	tskmgr.DelayMs(500);
//	restart();
//	tskmgr.DelayS(3);
//	enableOrDisableMUX(1); //开启多路访问
//	tskmgr.DelayMs(1000);
//	OpenServer(port);
//	tskmgr.DelayMs(1000);
//	SetTimeout(time);
//	tskmgr.DelayMs(1000);
//	return 1;
//}


