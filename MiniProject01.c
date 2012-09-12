// Mini Project01
// created by Michael Junge
// Due date: Sept. 13, 2012

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "i2c.h"
#include "flash10.h"
#include "analog.h"


#define SYSFS_GPIO_DIR "/sys/class/gpio"


char keepgoing =1;




// Callback called when SIGINT is sent to the process (Ctrl-C)
void signal_handler(int sig)
{
	printf( "Ctrl-C pressed, cleaning up and exiting..\n" );
	keepgoing = 0;
}

void main(int argc, char** argv)
{
	//set up main variables
	int i2cbus, address, daddress;
	int res, far;
	int LedOnePin, timeMS;
	int AnalogPin, AnalogValue;

	if (argc < 5){
		printf("Please enter values: <i2c-bus> <i2c-address> <register>\n" 
		"<LedOnePin> <on/off time in ms>\n"
		"<Analog Pin>\n", argv[0]);
		exit(-1);
	}
	signal(SIGINT, signal_handler);

	i2cbus     = atoi(argv[1]);
	address    = atoi(argv[2]);
	daddress   = atoi(argv[3]);
	LedOnePin  = atoi(argv[4]);
	timeMS     = atoi(argv[5]);
	AnalogPin  = atoi(argv[6]);
	

	//flash10(LedOnePin, timeMS);

	while(keepgoing){
	res = i2c(i2cbus, address, daddress);
	far = res * 9/5 +32;
	printf("The tempature is: %d in degrees Celcius\n", res);
	printf("The tempature is: %d in degrees Farhrenheit\n",far);
	analog(AnalogPin);
	usleep(500000);	
	}
	
		
	
/*
PWM led settings:

use hardware pwm ehrpwm2:0
use given frequency to control pwm led
use 3 analog ranges to change LEDduty from 5, 50, 100 percent

pwm setup:

open file: /sys/ker/nel/debug/omap_mux/lcd_data0
change mode to 3
close file

open file: /sys/class/pwm/ehrpwm.2:0
change run=1, period_freq=LEDfreq, LEDduty based on analog value
close file  



*/

}















