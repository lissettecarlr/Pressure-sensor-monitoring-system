#include "Hint.h"

hint::hint(GPIO LED,GPIO BEEP):led(LED),beep(BEEP)
{
	
}

void hint::beepMode1()
{

}


void hint::ledFlicker_2s()
{
	u8 i =5;
	while(i--)
	{
		led.SetLevel(0);//mie
		tskmgr.DelayMs(200);
		led.SetLevel(1);//mie
		tskmgr.DelayMs(200);
	}
}


void hint::led_NO_2s()
{
		led.SetLevel(0);
		tskmgr.DelayMs(1000);
		tskmgr.DelayMs(1000);
		led.SetLevel(1);
}


void hint::led_NO_1ms()
{
		led.SetLevel(1);
		tskmgr.DelayMs(100);
		led.SetLevel(0);
}

