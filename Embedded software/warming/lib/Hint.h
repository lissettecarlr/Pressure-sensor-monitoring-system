#ifndef __HINT_H
#define __HINT_H

#include "stm32f10x.h"
#include "GPIO.h"
#include "TaskManager.h"


class hint {

	private:
		GPIO led;
		GPIO beep;
	public:
		hint(GPIO LED,GPIO BEEP);
		void beepMode1();
		void ledFlicker_2s();
		void led_NO_2s();
};


#endif
