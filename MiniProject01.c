// Mini Project01
// created by Michael Junge
// Due date: Sept. 13, 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>

//personal header files for this project
#include "i2c.h"
#include "flash10.h"
#include "analog.h"
#include "pwm.h"
#include "interupt.h"


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT 0
#define MAX_BUF 64

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

	struct pollfd fdset[2];
	int nfds = 2;
	int gpio_fd, timeout, rc;
	char *buf[MAX_BUF];
	unsigned int gpio;
	int len;



	if (argc < 9){
		printf("Please enter values: \n" 
		"<i2c-bus> <i2c-address> <register>\n" 
		"<InteruptLedPin> <time of flashes in ms>\n"
		"<freq of pwm> <switch>\n"
		"<Analog Pin>\n", argv[0]);
		exit(-1);
	}
	signal(SIGINT, signal_handler);

	i2cbus     = atoi(argv[1]);
	address    = atoi(argv[2]);
	daddress   = atoi(argv[3]);
	LedOnePin  = atoi(argv[4]);
	timeMS     = atoi(argv[5]);
	freq       = atoi(argv[6]);
	gpio       = atoi(argv[7]);
	AnalogPin  = atoi(argv[8]);
	
	//duty = 50;	
	
	gpio_export(gpio);
	gpio_set_dir(gpio, 0);
	gpio_set_edge(gpio, "rising");  // Can be rising, falling or both
	gpio_fd = gpio_fd_open(gpio);

	timeout = POLL_TIMEOUT;

	
	while(keepgoing){
	
		memset((void*)fdset, 0, sizeof(fdset));

		fdset[0].fd = STDIN_FILENO;
		fdset[0].events = POLLIN;
      
		fdset[1].fd = gpio_fd;
		fdset[1].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);      

		
            
		if (fdset[1].revents & POLLPRI) {
			lseek(fdset[1].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[1].fd, buf, MAX_BUF);
			printf("\nGPIO %d interrupt occurred\n", gpio);
			flash10(LedOnePin, timeMS);
		}

		if (fdset[0].revents & POLLIN) {
			(void)read(fdset[0].fd, buf, 1);
			printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		}

		fflush(stdout);	
	
		//end of interupt code
		//
		//now on to the rest of the code

		res = i2c(i2cbus, address, daddress);
		far = res * 9/5 +32;
		printf("The tempature is: %d in degrees Celcius\n", res);
		printf("The tempature is: %d in degrees Farhrenheit\n",far);
		An = analog(AnalogPin);
		printf("the analog value is %d\n\n\n", An);		
		
	// Depending on the analog value the duty cycle changes
	// The Led has three setting low, medium, and high

		if (An >= 0 && An <=2000){
			duty = 10;
		} else if (An >= 2000 && An <= 3500){
			duty = 40;
		} else {
			duty = 90;
		}

		pwm(freq, duty);
	
	}		
	
	gpio_fd_close(gpio_fd);
}















