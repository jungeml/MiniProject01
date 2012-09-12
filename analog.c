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


void main(int argc, char** argv)
{
	char AIN[100];
	char value[5];
	int Pin;
	if (argc < 2){
		printf("Please enter values: analog input\n", argv[0]);
		exit(-1);
	}
	

	Pin = atoi(argv[1]);

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
	//return value;
	printf("the analog value is %s\n", value);
}
