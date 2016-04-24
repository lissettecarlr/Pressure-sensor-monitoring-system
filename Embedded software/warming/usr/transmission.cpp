#include "transmission.h"

Transmission CMCT_Tool;

Transmission::Transmission()
{

}


u8 Transmission::CommandParsing(u8 command[6])
{
	if(command[0]==0xaa&&command[1]==0xbb )
	{
		u8 sum=0;
		for(u8 i=0;i<5;i++)
			sum+= command[i];
		if(sum == command[5]) //校验和正确
			return command[3];
		else
			return 0;
	}
	else
		return 0;
}
	
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
				if(ch == 0xbb)
				{
					while(ListeningCOM.ReceiveBufferSize()<4);//等待数据
					comand[0]=0xaa;
					comand[1]=0xbb;
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

void Transmission::SendState(USART &COM,u8 state)
{
	u8 alive[5] = {0xbb,0xaa,state,0xff,0};
	for(int i=0;i<4;i++)
		alive[4]+=alive[i];
	COM.SendData(alive,5);
}

/*状态
bb aa 01 ff 65   //离床
bb aa 02 ff 66   //按键
bb aa 03 ff 67   //待机
	
*/