# Klingon-Bird-of-Prey-Arduino-Code
This is the Arduino Code for my 1:350ish Klingon Bird of Prey Lighting Effects

S. A. Wolfe
1 - 26 - 2017
MacOSX 10.11.6 - Arduino 1.0.5 - Arduino-Tiny Hardware Files


My code for lighting effects for the 1:350ish Klingon Bird of Prey model
kit from AMT/Round 2. The code is written for an ATtiny85 microcontroller.
A button, when pushed, fires the photon torpedo launcher and, when pushed
and held, fires the disruptors in short bursts for a time. The main engines
also fade slowly with faster pulsations over top of that. Some of this code 
I discovered online and I take no credit for sections where I use it.
Feel free to use and adapt as you see fit.

Pinout (Attiny85):
Pin 1 = RESET, Pin 2 = Arduino Pin 3, Pin 3 = Arduino Pin 4 (PWM), Pin 4 = GND
Pin 5 = Arduino Pin 0 (PWM), Pin 6 = Arduino Pin 1 (PWM), Pin 7 = Arduino Pin 2, Pin 8 = VCC

Binary sketch size: 3,368 bytes (of a 8,192 byte maximum)

A version of the schematic can be found at: https://flic.kr/p/22k9aGt.
A video of the lighting effects concept can be viewd at: https://flic.kr/p/E6YUmz.
