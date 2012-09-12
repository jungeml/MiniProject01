// C script for reading an analog value on the beagle bone
//
//
//Created by Mike Junge, 9 September 2012

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SYSFS_ANALOG_DIR "/sys/devices/platform/omap/tsc"

FILE *fp; 


void analog(int Pin)
{
	char AIN[100];
	char value[5];

	sprintf(AIN, SYSFS_ANALOG_DIR"/ain%d", Pin );
		
	//Read Value
	if ((fp = fopen( AIN, "rb")) == NULL)
	{
		printf("Cannot open analog file.\n");
		exit(1);
	}
	//Set prints out the value from the analog pin
	
	fscanf(fp, "%s", &value);    			
	fclose(fp);
	printf("the analog value is %s\n\n\n", value);
}
