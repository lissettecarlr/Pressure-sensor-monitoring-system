#include "transmission.h"

Transmission CMCT_Tool;

Transmission::Transmission()
{
	for(int i=0;i<6;i++)
	{
		MtoW[i] = 0;
	}
	
	for(int i=0;i<5;i++)
	{
		MtoS[i] = 0;
	}
	WarmingModule = 3;
}


u8 *Transmission::MonitoringToWarning(u8 Command)
{
	MtoW[0] = 0xaa;
	MtoW[1] = 0xbb;
	
	MtoW[2] = BEDNO;
	MtoW[3] = Command;
	MtoW[4] = 0xff;
	MtoW[5] = 0;
	
	for(int i=0;i<5;i++)
	{
		MtoW[5]+= MtoW[i];
	}
	
	return MtoW;
}

u8 *Transmission::MonitoringToServer(u8 BadState)
{
	MtoS[0] = 0XAA;
	MtoS[1] = 0xAA;
	
	MtoS[2] = BEDNO;
	MtoS[3] = BadState;
	MtoS[4] = 0xff;
	return MtoS;

}

u8 Transmission::CommandParsing(u8 command[6])
{
	if(command[0]==0xaa&&command[1]==0xcc && command[2]== BEDNO) //包头 床位都符合的话
	{
		u8 sum=0;
		for(u8 i=0;i<5;i++)
			sum+= command[i];
		if(sum == command[5]) //校验和正确
			return command[4];
		else
			return 0;
	}
	else
		return 0;
}
	
	
//监听一个端口，返回一个命令
u8 Transmission::GetStateOrder(USART &ListeningCOM)
{
		u8 comand[6]={0};
		u8 ch=0;
		u8 num = ListeningCOM.ReceiveBufferSize();
		if(num>5)  
		{
				ListeningCOM.GetReceivedData(&ch,1);
			if(ch == 0xaa)
			{
				ListeningCOM.GetReceivedData(&ch,1);
				if(ch == 0xcc)
				{
					while(ListeningCOM.ReceiveBufferSize()<4);//等待数据
					comand[0]=0xaa;
					comand[1]=0xcc;
					ListeningCOM.GetReceivedData(comand+2,4);
					ListeningCOM.ClearReceiveBuffer();
					return CommandParsing(comand);  //解包
				}
				else return 0;
			}
			else
				return 0;
		}
		else 
			return 0;
}

u8 Transmission::ListeningWarmingModule(USART &ListeningCOM)
{
	u8 comand[3]={0};
	u8 ch=0;
	u8 num = ListeningCOM.ReceiveBufferSize();
	if(num>4) 
	{
		ListeningCOM.GetReceivedData(&ch,1);
			if(ch == 0xbb)
			{
				ListeningCOM.GetReceivedData(&ch,1);
				if(ch == 0xaa)
				{
					while(ListeningCOM.ReceiveBufferSize()<3);//等待数据
					ListeningCOM.GetReceivedData(comand,3);
					u8 sum = 0xaa+0xbb+comand[0]+comand[1];
					if(sum == comand[2])
						{
							WarmingModule = comand[0];
							return WarmingModule;
						}
					else
						return WarmingModule;	
				}
				return WarmingModule;
			}
			return WarmingModule;
	}
	return WarmingModule;
}

void Transmission::SendAlive(esp8266 &esp)
{
	u8 alive[4] = {0xaa,0xff,BEDNO,0xff};
	esp.Send(4,alive);
}

bool Transmission::GetWifiNameAndPassword(char *name,char *password,USART &ListeningCOM)
{
	u8 ch=0;
	u8 i =0;
	ListeningCOM.GetReceivedData(&ch,1);
		if(ch == 0xFF)
		{
			tskmgr.DelayMs(100);
			ListeningCOM.GetReceivedData(&ch,1);
			if(ch == 0x03)
			{
				ListeningCOM.GetReceivedData(&ch,1);
				while(ch!=0xff){
					*(name+i)=ch;
					i++;
					ListeningCOM.GetReceivedData(&ch,1);
				}
					*(name+i)='\0';
					ListeningCOM.GetReceivedData(&ch,1);
					i=0;
				while(ch!=0xff){
					*(password+i)=ch;
					i++;
					ListeningCOM.GetReceivedData(&ch,1);
				}
					*(password+i)='\0';	
				return 1;
			}
			else return 0;
		}
		else
			return 0;
}
