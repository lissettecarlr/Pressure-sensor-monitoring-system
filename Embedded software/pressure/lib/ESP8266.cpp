#include "ESP8266.h"

esp8266::esp8266(USART &usart)
:mUsart(usart)
{
	rx_empty();
}

void esp8266::rx_empty()
{
	mUsart.ClearReceiveBuffer();

	for(u16 i=0;i<mReceiveBuffer.Size();++i)//将队列中存放数据的数组擦除
	mReceiveBuffer._buf[i]=0;
	mReceiveBuffer.Clear();//清除队列信息
}

	/* 
	 * Recvive data from uart. Return all received data if target found or timeout. 
	 */
	char* esp8266::recvString(char const *target, float timeout)
{
	u8 temp;

	double tartTime=TaskManager::Time();
	while((TaskManager::Time()-tartTime)<timeout)
	{
		while(mUsart.ReceiveBufferSize()>0)
		{
			mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
			if(temp=='\0')
				continue;
			mReceiveBuffer.Put(temp);//放入esp的缓冲区
			
		}
		
		if(strstr(mReceiveBuffer._buf,target)) //判断字符串2是否为字符串1的字串
			break;				
	}
	if(mReceiveBuffer.Size()>0)//接收到了数据，加上结束标志
		mReceiveBuffer.Put('\0');
	return mReceiveBuffer._buf;
}
	
	/* 
	 * Recvive data from uart. Return all received data if one of target1 and target2 found or timeout. 
	 */
	char* esp8266::recvString(char const *target1, const char* target2, float timeout )
{
	u8 temp;
	double tartTime=TaskManager::Time();
	while((TaskManager::Time()-tartTime)<timeout)
	{
		while(mUsart.ReceiveBufferSize()>0)
		{
			mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
			if(temp=='\0')
				continue;
			mReceiveBuffer.Put(temp);//放入esp的缓冲区
		}
		if(strstr(mReceiveBuffer._buf,target1) || strstr(mReceiveBuffer._buf,target2))//找到目标数据
			break;
		
	}
	if(mReceiveBuffer.Size()>0)//接收到了数据，加上结束标志
		mReceiveBuffer.Put('\0');
	return mReceiveBuffer._buf;
}
	
	/* 
	 * Recvive data from uart. Return all received data if one of target1, target2 and target3 found or timeout. 
	 */
	char* esp8266::recvString(char const *target1, const char* target2,const  char* target3, float timeout)
{
	u8 temp;
	double tartTime=TaskManager::Time();
	while((TaskManager::Time()-tartTime)<timeout)
	{
		while(mUsart.ReceiveBufferSize()>0)
		{
			mUsart.GetReceivedData(&temp,1);//从串口接收缓冲区接收数据
			if(temp=='\0')
				continue;
			mReceiveBuffer.Put(temp);//放入esp的缓冲区
		}
		if(strstr(mReceiveBuffer._buf,target1) || strstr(mReceiveBuffer._buf,target2) || strstr(mReceiveBuffer._buf,target3))//找到目标数据
			break;
		
	}
	if(mReceiveBuffer.Size()>0)//接收到了数据，加上结束标志
		mReceiveBuffer.Put('\0');
	return mReceiveBuffer._buf;
}


	bool esp8266::recvFind(char const *target, float timeout)
{
	char* data_temp=recvString(target,timeout);
	//mUsart<<data_temp<<"2"<<"\r\n";
	if(strstr(data_temp,target))
		return true;
	return false;
}

/* 
	 * Recvive data from uart and search first target and cut out the substring between begin and end(excluding begin and end self). 
	 * Return true if target found, false for timeout.
	 */
	bool esp8266::recvFindAndFilter(char const *target, char const * begin, char const * end, char** Data, float timeout)
{

	char* data_temp=recvString(target,timeout);
	if(strstr(data_temp,target))
	{
		char* index1=strstr(data_temp,begin);
		char* index2=strstr(data_temp,end);

		if(index1&&index2)
		{
			index1+=strlen(begin);
			*index2='\0';
			*Data=index1;
			return true;
		}
	}
	
	Data=0;
	return false;
}
/*********************************************************************************************/
	bool esp8266::kick(void)
{
	rx_empty();
	mUsart<<"AT\r\n";
	return recvFind("OK");
}

	bool esp8266::restart(void)
{
		rx_empty();
		mUsart<<"AT+RST\r\n";
		return recvFind("OK");
}

//是否回显 1 是 0 
bool esp8266::setEcho(uint8_t mode)
{
	rx_empty();
	mUsart<<"ATE"<<mode<<"\r\n";
	return recvFind("OK");
}

bool esp8266::setOprToStation()
{
	char* data_temp;
	rx_empty();  //清空发送缓存
	mUsart<<"AT+CWMODE=1"<<"\r\n";
	data_temp = recvString("OK", "ERROR");
	if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::setOprToSoftAP()
{
		char* data_temp;
	rx_empty();  //清空发送缓存
	mUsart<<"AT+CWMODE=2"<<"\r\n";
	data_temp = recvString("OK", "ERROR");
	if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::setOprToStationSoftAP()
{
	char* data_temp;
	rx_empty();  //清空发送缓存
	mUsart<<"AT+CWMODE=3"<<"\r\n";
	data_temp = recvString("OK", "ERROR");
	if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::joinAP( char* ssid,  char* pwd)
{
		char* data_temp;
		rx_empty();
		mUsart<<"AT+CWJAP=";
		mUsart<<"\""<<ssid<<"\",\""<<pwd<<"\"\r\n";
	for(int i=0;i<20;i++) //需要20秒的等待后判断是否连接上
		{
			tskmgr.DelayMs(1000);
		}
		data_temp = recvString("OK", "FAIL");
		if(strstr(data_temp,"FAIL"))
			return false;
		else
			return true;
}

bool esp8266::setSoftAPParam( char* ssid,  char* pwd, uint8_t chl , uint8_t ecn)
{
		char* data_temp;
		rx_empty();
		mUsart<<"AT+CWSAP=";
		mUsart<<"\""<<ssid<<"\",\""<<pwd<<"\","<<chl<<","<<ecn<<"\r\n";
		data_temp = recvString("OK", "ERROR");
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::enableOrDisableMUX(u8 choose)
{
		char * data_temp;
		rx_empty();
		mUsart<<"AT+CIPMUX="<<choose<<"\r\n";
		data_temp = recvString("OK", "ERROR");	
			if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
		
}

bool esp8266::ConnectServerID(int mux_id, char*  type, char*  addr, int port)
{
		char * data_temp;
		rx_empty();
		mUsart<<"AT+CIPSTART=";
		mUsart<<mux_id<<","<<"\""<<type<<"\",\""<<addr<<"\","<<port<<"\r\n";
		data_temp = recvString("OK", "ERROR");
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}
bool esp8266::ConnectServer(char*  type, char*  addr, int port)
{
		char * data_temp;
		rx_empty();
		mUsart<<"AT+CIPSTART=";
		mUsart<<"\""<<type<<"\",\""<<addr<<"\","<<port<<"\r\n";
		data_temp = recvString("OK", "ERROR");
	  tskmgr.DelayMs(1000);
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

void esp8266::Send(char ID,int Lenth,u8 data[])
{
	ID=ID+48;//将数字转化为字符
	//Lenth=Lenth+48;
	rx_empty();
	mUsart<<"AT+CIPSEND=";
	mUsart<<ID<<","<<Lenth<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart.SendData(data,Lenth);
}

void esp8266::Send(int Lenth,u8 data[])
{
	rx_empty();
	mUsart<<"AT+CIPSEND=";
	mUsart<<Lenth<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart.SendData(data,Lenth);
}

void esp8266::Send(char ID,char * str)
{
	rx_empty();
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
	rx_empty();
	u8 number=0;
	while( (*str)!= '\0')
		{number++;str++;}
	
	mUsart<<"AT+CIPSEND=";
	mUsart<<number<<"\r\n";
	tskmgr.DelayMs(100);
	mUsart<<(str-number);
}

bool esp8266::SetTimeout(int time)
{
	char * data_temp;
	rx_empty();
	mUsart<<"AT+CIPSTO="<<time<<"\r\n";
	data_temp = recvString("OK", "ERROR");
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::OpenServer(int port)
{
	char * data_temp;
	rx_empty();
	mUsart<<"AT+CIPSERVER=1,"<<port<<"\r\n";
	data_temp = recvString("OK", "ERROR");
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

bool esp8266::SetIpAddr(char* str) //设置IP地址
{
	char * data_temp;
	rx_empty();
	mUsart<<"AT+CIPSTO="<<str;
	data_temp = recvString("OK", "ERROR");
		if(strstr(data_temp,"OK"))
			return true;
		else
			return false;
}

/*******************************************************************************************/
u8 esp8266::ConnectNetwork_client(char *WifiName,char* WifiPassword,char *IP,int COM) //预计耗时26秒
{
	//网络连接
	if(!kick())
		return 0;
	tskmgr.DelayMs(1000);
	setEcho(1);//回显
	tskmgr.DelayMs(1000);
	setOprToStation();//设置为模式1
	tskmgr.DelayMs(500);
	restart();
	tskmgr.DelayS(3);
	if(!joinAP(WifiName,WifiPassword))
		return 0;//WIFI连接 如果连接失败，返回0
	//enableOrDisableMUX(1);
	if( !ConnectServer("TCP",IP,COM) ) return false;  //服务器连接
	return 1;
}

u8 esp8266::ConnectNetwork_server(int port,int time) //预计耗时7秒
{
	if(!kick())
		return 0;
	tskmgr.DelayMs(1000);
	setOprToSoftAP();
	tskmgr.DelayMs(500);
	restart();
	tskmgr.DelayS(3);
	enableOrDisableMUX(1); //开启多路访问
	tskmgr.DelayMs(1000);
	OpenServer(port);
	tskmgr.DelayMs(1000);
	SetTimeout(time);
	tskmgr.DelayMs(1000);
	return 1;
}


