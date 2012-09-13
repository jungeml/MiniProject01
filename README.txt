MiniProject01
=============

Mini Project 01 from ECE497

Requirements

It's up to you to decide just what your mini project does, however it must:

    use at least 1 interupt driven gpio input (it could read a switch)
    use one gpio output (it could blink an LED)
    use a PWM output (maybe blink or dim and LED)
    use an i2c device (read a temperature?)
    use at least one analog in (read a voltage?)
    handle a ^C interrupt 

I plan to succeed in using all of these requirements. My plan is to 
constantly write a saying to the terminal that will include an analog 
value and the tempature using i2c in degrees Fahrenheit. The analog value 
will control the brightness of the LED in three steps, from low to medium 
to full brightness. I will also have an interupt driven switch that will cause 
an LED to blink 10 times after being pushed. To close the program I will use the 
classic ^C interrupt that properly closes the file and resets defaults.


How to use the finished code:

Compile MiniProject01.c or just use Mini01 which is already compiled. You must download all of the files listed below in order for the code to run properly. They are:

analog.h
i2c-dev.h
interupt.h
flash10.h i2c.h
MiniProject01.c
pwm.h

The code will not compile if even only one header file is forgotten.


When you run Mini01 without any inputs to main you recieve the following: 
"
Please enter values: 
<i2c-bus> <i2c-address> <register>
<InteruptLedPin> <time of flashes in ms>
<freq of pwm> <switch>
<Analog Pin>
"

i2c-bus/i2c-address/register is the same used in class for the TC74 tempature chip

InteruptLedPin is the gpio pin number for any gpio number which has an LED hooked up.

freq of pwm is any frequency the user chooses for the pwm LED to run at.

switch is the gpio pin number of any given switch the user has plugged into the bone.

Analog Pin is defined as: the user can set any ain pin number he would like.

However the user cannot set the gpio pin for the pwm LED. Since I could not figure out how
to input a random pin, check the mux setting, then relay back to the user. I choose to hard
code the pwm mux settings to use pwm 2.0, under lcd_data0 mux 3.



Note: the code gives the warnings during compiling: 

pwm.h:38:26: warning: unknown escape sequence: '\:'
pwm.h:39:27: warning: unknown escape sequence: '\:'
pwm.h:40:27: warning: unknown escape sequence: '\:'

However, the code runs fine if you ignore the warnings.
