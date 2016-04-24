#include "WIFI_Memory.h"

WifiMemory::WifiMemory(Memory &InfoSpace):infoSpace(InfoSpace)
{
	LoadSaveInfo();
}


bool WifiMemory::Save(char* name,char* password)
{
	u16 Lenth1=0,Lenth2=0,LenthSum=0;
	u16 nowPageLenth=0;
	wifiNumber++;//更新量信息
	
	if(dataLenth==0xffff ||dataLenth==0)
	{
			nowPageLenth=0;
	}
	else
			nowPageLenth=dataLenth%MEMORY_PAGE_SIZE;//计算出在也中的位置

	
	if(pageNumber==0)
		pageNumber++;

	  while( (*name)!= '\0')
		{Lenth1++;name++;}
		
		name=name-Lenth1;
		
		while( (*password)!= '\0')
		{Lenth2++;password++;}
		
		password=password-Lenth2;
		
		if(Lenth1%2==0)//如果为偶数则仅仅加上两个长度位
			Lenth1+=2;
		else//如果是是奇数
			Lenth1+=3;
		
				
		if(Lenth2%2==0)//如果为偶数则仅仅加上两个长度位
			Lenth2+=2;
		else//如果是是奇数
			Lenth2+=3;
		
		LenthSum=Lenth1+Lenth2;	
		
		if(nowPageLenth+LenthSum>MEMORY_PAGE_SIZE) //如果这页装不下了
		{
			 dataLenth=pageNumber*MEMORY_PAGE_SIZE;
			 pageNumber++;//更新页码信息
			 
			infoSpace.Write(pageNumber,0,name);
			infoSpace.Write(pageNumber,Lenth1,password);	
		}
		else
		{		
			infoSpace.Write(pageNumber,nowPageLenth,name);
			infoSpace.Write(pageNumber,nowPageLenth+Lenth1,password);
		}
		
		dataLenth+=LenthSum;//更新长度信息	
		UpdataSaveInfo();
	
	return true;
}
	

bool WifiMemory::Load(char* name,char* password)
{
	if(wifiNumber==0)
		return false;
	
	u16 lenth=0;
	infoSpace.Read(PointerPage,Pointer,&lenth,1); //读取name长度
	
	if(lenth==0xffff)//已经读取完
	{
		PointerPage=1;
		Pointer=0;
		return false ;
	}
	
	infoSpace.Read(PointerPage,Pointer,name);//读取IP
	
	if(lenth%2==0)
		Pointer=Pointer+lenth+2;
	else
		Pointer=Pointer+lenth+3;	
	
	infoSpace.Read(PointerPage,Pointer,&lenth,1); //读取name长度
	infoSpace.Read(PointerPage,Pointer,password);//读取IP
	
	if(lenth%2==0)
		Pointer=Pointer+lenth+2;
	else
		Pointer=Pointer+lenth+3;
	
	infoSpace.Read(PointerPage,Pointer,&lenth,1); //读取name长度
	if(PointerPage<pageNumber &&lenth==0xffff) //翻页
	{
		PointerPage++;
		Pointer=0;
		return true;
	}
	 
	return true;
}

//读取存储信息
bool WifiMemory::LoadSaveInfo()
{
	 infoSpace.Read(0,0,&wifiNumber,1);
		if(wifiNumber== 0xffff) //如果为空
		{
			wifiNumber=0;
			dataLenth=0;
			pageNumber=0;
			Pointer=0;
			PointerPage=1;
			UpdataSaveInfo();
			return false;
		}
		else{
			infoSpace.Read(0,2,&dataLenth,1);
			infoSpace.Read(0,4,&pageNumber,1);
			Pointer=0;//将读取指针放到数据开始位置
			PointerPage=1;
				return true;
		}
}

//更新存储信息
bool WifiMemory::UpdataSaveInfo() //读取该页基本信息
{
		infoSpace.Write(0,0,&wifiNumber,1);//对开始位置写入时会擦除该页
		infoSpace.Write(0,2,&dataLenth,1);
		infoSpace.Write(0,4,&pageNumber,1);
		Pointer=0;
		PointerPage=1;
		return true;
}


u16 WifiMemory::getWifiSum()
{
	 return wifiNumber;
}

bool WifiMemory::ClearAllData()
{
		infoSpace.Read(0,4,&pageNumber,1);
		while(pageNumber>0) //擦除所以
		{
			infoSpace.Clear(pageNumber);
			pageNumber--;
		}
			infoSpace.Clear(0);//擦除信息页
		
		LoadSaveInfo();
		UpdataSaveInfo();
	 return true;
}

