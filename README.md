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
value and the tempature using i2c in degrees Fahrenheit. The analog value will control the brightness of the LED in three 
steps, from low to medium to full brightness. I will also have an 
interupt driven switch that will cause an LED to blink 10 times after 
being pushed. To close the program I will use the classic ^C interrupt that
properly closes the file and resets defaults.

