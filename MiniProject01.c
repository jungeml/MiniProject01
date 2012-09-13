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
#include "pwm.h"


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
	int freq, duty;
	int An;

	if (argc < 8){
		printf("Please enter values: \n" 
		"<i2c-bus> <i2c-address> <register>\n" 
		"<LedOnePin> <on/off time in ms>\n"
		"<Analog Pin>\n"
		"<freq> \n", argv[0]);
		exit(-1);
	}
	signal(SIGINT, signal_handler);

	i2cbus     = atoi(argv[1]);
	address    = atoi(argv[2]);
	daddress   = atoi(argv[3]);
	LedOnePin  = atoi(argv[4]);
	timeMS     = atoi(argv[5]);
	AnalogPin  = atoi(argv[6]);
	freq       = atoi(argv[7]);
	
	
	

	
	flash10(LedOnePin, timeMS);
	

	while(keepgoing){
	res = i2c(i2cbus, address, daddress);
	far = res * 9/5 +32;
	printf("The tempature is: %d in degrees Celcius\n", res);
	printf("The tempature is: %d in degrees Farhrenheit\n",far);
	An = analog(AnalogPin);
	printf("the analog value is %d\n\n\n", An);		
	

// Depending on the analog value the duty cycle changes
// The Led has three setting low, medium, and high

	if (An >= 0 && An <=1365){
		duty = 10;
	} else if (An >= 1365 && An <= 2730){
		duty = 40;
	} else {
		duty = 100;
	}
	
	pwm(freq, duty);
	
	}
	
		
	

}















