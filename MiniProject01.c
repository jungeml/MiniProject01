// Mini Project01
// created by Michael Junge
// Due date: Sept. 13, 2012

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "i2c.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define LED1	 "/sys/class/gpio"   //  LEDpath=/sys/class/gpio/gpio${GPIO}



void main(int argc, char** argv)
{
	
	//set up main variables
	int i2cbus, address, daddress;
	int res, far;
	if (argc < 3){
		printf("Please enter %s <i2cbus>  <address> <daddress>\n", argv[0]);
		exit(-1);
	}


	i2cbus   = atoi(argv[1]);
	address  = atoi(argv[2]);
	daddress = atoi(argv[3]);
	
	
	res = i2c(i2cbus, address, daddress);
		
	printf("The tempature is: %d in degrees C\n", res);

	far = res * 9/5 +32;
	printf("The tempature is: %d in degrees Farhrenheit\n",far);


	




/*	cleanup code

	printf("Ctrl-c pressed, cleaning up and exiting...\n");
	
*/
}















