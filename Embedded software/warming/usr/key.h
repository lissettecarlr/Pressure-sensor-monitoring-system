#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

class Key{
	private:
		GPIO_TypeDef *mExitPort;  //GPIO Port of exit pin
		u16 mExitPin;             //GPIO pin for exit
	
	
	public:
		Key(GPIO_TypeDef *exitPort, u8 exitPin, u8 itGroup=3,u8 prePriority=5,u8 subPriority=0);
		void IRQ();
};

#endif
