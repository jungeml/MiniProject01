// C script for a pwm controlled LED on the beagle bone
// LED port is specifically defined for gpio2_6
//
//
//Created by Mike Junge, 9 September 2012

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp; 

#define LedMux "/sys/kernel/debug/omap_mux/lcd_data0"
#define LedPath "/sys/class/pwm/ehrpwm.2\:0"

void pwm(int freq, int duty)
{
	char freqPath[100];
	char dutyPath[100];
	char runPath[100];
	char set_value[5]; 
	
	
	
	if ((fp = fopen(LedMux, "ab")) == NULL)
		{
			printf("Cannot open export file.\n");
			exit(1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	
	sprintf(set_value,"%d", 3);	//hard code for changing gpio_2_6 to pwm 2.0
	fwrite(&set_value, sizeof(char), 3, fp);
	fclose(fp);
	
	sprintf(runPath, LedPath"/run");
	sprintf(freqPath, LedPath"/period_freq");
	sprintf(dutyPath, LedPath"/duty_percent");
	

	if ((fp = fopen(runPath, "rb+")) == NULL)
		{
			printf("Cannot open export file.\n");
			exit(1);
		}
	//Set pointer to begining of the file
		rewind(fp);
		//Write run=1
		sprintf(set_value,"1");
		fwrite(&set_value, sizeof(char), 3, fp);
		fclose(fp);

	if ((fp = fopen(freqPath, "rb+")) == NULL)
		{
			printf("Cannot open export file.\n");
			exit(1);
		}
	//Set pointer to begining of the file
		rewind(fp);
		//Write freq= given
		sprintf(set_value,"%d", freq);
		fwrite(&set_value, sizeof(char), 3, fp);
		fclose(fp);

	if ((fp = fopen(dutyPath, "rb+")) == NULL)
		{
			printf("Cannot open export file.\n");
			exit(1);
		}
	//Set pointer to begining of the file
		rewind(fp);
		//Write duty= given duty
		sprintf(set_value,"%d", duty);
		fwrite(&set_value, sizeof(char), 3, fp);
		fclose(fp);

		usleep(500000);

		if ((fp = fopen(runPath, "rb+")) == NULL)
		{
			printf("Cannot open export file.\n");
			exit(1);
		}
	//Set pointer to begining of the file
		rewind(fp);
		//Write run=0
		sprintf(set_value,"0");
		fwrite(&set_value, sizeof(char), 3, fp);
		fclose(fp);

}























