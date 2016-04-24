#ifndef __WIFI_MEMORY_H
#define __WIFI_MEMORY_H

#include "Memory.h"


class WifiMemory{

	private:
		Memory &infoSpace;
	  //每页保存的前三个基础属性
		u16 wifiNumber;//WIFI个数
		u16	dataLenth; //总长度
		u16 pageNumber; //总页数
	
		u16 Pointer; //当前所指位置 
		u16 PointerPage;//当前页数
	
		bool LoadSaveInfo(); //读取该页基本信息
		bool UpdataSaveInfo(); //读取该页基本信息
	
	public:
		WifiMemory(Memory &InfoSpace);
		bool Save(char* name,char* password);
		bool Load(char* name,char* password);
		u16 getWifiSum();//得到WIFI总数
		bool ClearAllData();//清空所有保存的WIFI数据
};

#endif
