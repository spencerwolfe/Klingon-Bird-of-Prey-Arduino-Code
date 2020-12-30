# Klingon-Bird-of-Prey-Arduino-Code-and-Build-Files
## This is the Arduino Code for my 1:350ish Klingon Bird of Prey Lighting Effects   

S.A. Wolfe  
Final Version - 12/26/2020 
MacOS 10.14.5 - Arduino 1.8.9  
Using core files from [SpenceKonde/ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) (No Relation :)) 

My code for lighting effects for the 1:350ish Klingon Bird of Prey model
kit from AMT/Round 2. The code is written for an ATtiny85 microcontroller.
A button, when pushed, fires the photon torpedo launcher and, when pushed
and held, fires the disruptors in short bursts for a time. The main engines
also fade slowly with faster pulsations over top of that. Some of this code 
I discovered online and I take no credit for sections where I use it.  
Specifically, the original code for "push and hold" button switching can be found [here](http://jmsarduino.blogspot.com/2009/05/click-for-press-and-hold-for-b.html).  

Pinout (Attiny85):  
Pin 1 = RESET  
Pin 2 = Code Pin 3 = Torpedo Flash  
Pin 3 = Code Pin 4 (PWM) = Torpedo Ramp  
Pin 4 = GND  
Pin 5 = Code Pin 0 (PWM) = Engine Pulse  
Pin 6 = Code Pin 1 (PWM) = Disruptor Flash  
Pin 7 = Code Pin 2 = Pushbutton (using the internal PULLUP)  
Pin 8 = VCC  

Sketch uses 3852 bytes (47%) of program storage space. Maximum is 8192 bytes.  
Global variables use 61 bytes (11%) of dynamic memory, leaving 451 bytes for local variables. Maximum is 512 bytes.  

A version of the schematic can be found [here.](https://i.imgur.com/BocrYRs.jpg)  
A video of the lighting effects concept can be viewed [here](https://youtu.be/PGcJWlzBHdg) and [here.](https://youtu.be/N_Pehfjpc3A)  
