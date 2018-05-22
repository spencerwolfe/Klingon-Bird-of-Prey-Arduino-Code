# Klingon-Bird-of-Prey-Arduino-Code-and-Build-Files
## This is the Arduino Code for my 1:350ish Klingon Bird of Prey Lighting Effects  
## **Uploaded to GitHub on 5 - 19 - 2018**  


S. A. Wolfe  
1 - 26 - 2017  
MacOSX 10.11.6 - Arduino 1.0.5 - Atmel ATtiny85 - Arduino-Tiny Hardware Files  

**IMPORTANT** - You will need Arduino 1.0.5 or earlier for the *tiny* hardware  
files to work. Put the *tiny* folder in /Documents/Arduino/hardware/ or  
whatever folder Arduino stores your sketches. If the hardware folder doesn't  
exist, simply create it and move *tiny* into it. The original source for the *tiny*  
hardware folder can be found [here](http://highlowtech.org/?p=1695). I've reposted it for convenience.     

My code for lighting effects for the 1:350ish Klingon Bird of Prey model
kit from AMT/Round 2. The code is written for an ATtiny85 microcontroller.
A button, when pushed, fires the photon torpedo launcher and, when pushed
and held, fires the disruptors in short bursts for a time. The main engines
also fade slowly with faster pulsations over top of that. Some of this code 
I discovered online and I take no credit for sections where I use it.
Feel free to use and adapt as you see fit. Specifically, the original code for "push and hold" button switching can be found [here](http://jmsarduino.blogspot.com/2009/05/click-for-press-and-hold-for-b.html).  

Pinout (Attiny85):
Pin 1 = RESET, Pin 2 = Arduino Pin 3, Pin 3 = Arduino Pin 4 (PWM), Pin 4 = GND  
Pin 5 = Arduino Pin 0 (PWM), Pin 6 = Arduino Pin 1 (PWM), Pin 7 = Arduino Pin 2, Pin 8 = VCC

Binary sketch size: 3,368 bytes (of a 8,192 byte maximum)

**NOTE** - You will need to select "ATtiny85 @ 8MHz" as your board and use whatever ISP  
you want to burn a bootloader and program the ATtiny85. I use the Atmel AVRISP mkII.

A version of the schematic can be found [here](https://flic.kr/p/22k9aGt).  
A video of the lighting effects concept can be viewd [here](https://flic.kr/p/E6YUmz).  
