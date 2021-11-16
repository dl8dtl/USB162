/*
 * USBMassStorage.cpp
 * LEDS PD5 und PD4
 * Aktueller Stand: S. 194
 * Created: 25.10.2021 16:57:50
 * Author : Marvin
 * https://beyondlogic.org/usbnutshell/usb5.shtml
 * https://www.mikrocontroller.net/topic/527292#6879223
 */ 

/*
Used sources:
https://www.kampis-elektroecke.de/mikrocontroller/avr8/at90usb1287-usb/usb-device/anmeldung-beim-host-teil-1/
https://www.usb.org/defined-class-codes#anchor_BaseClass00h
https://beyondlogic.org/usbnutshell/usb5.shtml
*/

#include <avr/io.h>
#include "usbl.h"

void setup()
{
	DDRD = 0xFF; // Port for debugging LEDs
	setupUSB();
}

void loop()
{
	
}

int main(void)
{
	setup();
    while (1) 
    {
		loop();
	}
}
