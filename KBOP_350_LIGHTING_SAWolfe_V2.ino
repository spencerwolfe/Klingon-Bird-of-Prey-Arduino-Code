// S.A. Wolfe
// 7 - 11 - 2019
// MacOS 10.14.5 - Arduino 1.8.9
// Using SpenceKonde/ATTinyCore: https://github.com/SpenceKonde/ATTinyCore

// My code for lighting effects for the 1:350ish Klingon Bird of Prey model
//      kit from AMT/Round 2. The code is written for an ATtiny85 microcontroller.
//      A button, when pushed, fires the photon torpedo launcher and, when pushed
//      and held, fires the disruptors in short bursts for a time. The main engines
//      also fade slowly with faster pulsations over top of that. Some of this code 
//      I discovered online and I take no credit for sections where I use it.
//      Feel free to use and adapt as you see fit.

// Pinout (Attiny85):
// Pin 1 = RESET
// Pin 2 = Code Pin 3 = Torpedo Flash
// Pin 3 = Code Pin 4 (PWM) = Torpedo Ramp
// Pin 4 = GND
// Pin 5 = Code Pin 0 (PWM) = Engine Pulse
// Pin 6 = Code Pin 1 (PWM) = Disruptor Flash
// Pin 7 = Code Pin 2 = Pushbutton (using the internal PULLUP)
// Pin 8 = VCC

// Sketch uses 3852 bytes (47%) of program storage space. Maximum is 8192 bytes.
// Global variables use 61 bytes (11%) of dynamic memory, leaving 451 bytes for local variables. Maximum is 512 bytes.

// A version of the schematic can be found at: https://i.imgur.com/BocrYRs.jpg
// A video of the lighting effects concept can be viewed at: https://youtu.be/PGcJWlzBHdg


// ===================== Variables ============================================================ //
// -------  Declaring Pins ----------------------------------------------//
static byte disruptorPin = 0;
static byte enginePin = 1;
static byte pushButtonPin = 2;
static byte torpPin[] = { 3, 4 };

// -------  User Inputs ------------------------------------------------//
static unsigned long torpUpTime = 1750;
static unsigned long torpFlashTime = 300;
static unsigned long torpDownTime = 150;
static long double torpIdleBrightness = 10;
static long double torpMaxBrightness = 255;
static long double disruptorIdleBrightness = 5;
static unsigned long engineFadePeriod = 6000;
static unsigned long disruptorFiringTime = 8000;

// -------  For the Button Pushing -------------------------------------//
unsigned long debounce = 30;
unsigned long holdTime = 1500;

// -------  Bookeeping ------------------------------------------------//
boolean buttonValue = false;
boolean buttonLast = false;
boolean ignoreUp = false;
boolean disruptorState = false;
unsigned int torpedoPushes = 0;
unsigned int disruptorPushes = 0;
unsigned long currentMillis;
unsigned long buttonUpTime;
unsigned long buttonDownTime;
unsigned long torpedoTime;
unsigned long disruptorTime;
unsigned long torpedoMillis;
unsigned long disruptorMillis;
unsigned long disruptorFlashTime;
// ==================== End Variables ========================================================= //



// ===================== Setup ================================================================ //
void setup() {
  pinMode(disruptorPin,OUTPUT);
  pinMode(enginePin,OUTPUT);
  pinMode(pushButtonPin,INPUT_PULLUP);     // Enables internal pull-up resistor.
  pinMode(torpPin[0],OUTPUT);
  pinMode(torpPin[1],OUTPUT);
}
// ===================== End Setup ============================================================ //



// ===================== Main Loop ============================================================ //
void loop() {
  currentMillis = millis();         // Get current time.
  
 // ---------- Push Buttoon Code ------------------------------------------------------- //
 // Found the insipration for this online, so I do not take full credit for it.
  buttonValue = digitalRead(pushButtonPin);
  
  // Record Time of Push
  if (buttonValue == LOW && buttonLast == HIGH && (millis() - buttonUpTime) > debounce){
    buttonDownTime = millis();
  }
  
  // Record Time of Release
  if (buttonValue == HIGH && buttonLast == LOW && (millis() - buttonDownTime) > debounce){
    buttonUpTime = millis();
    if (ignoreUp == false){
      torpedoTime = millis();        // If released early, fire torpedoes!
      torpedoPushes++;
     }
     else{
       ignoreUp = false;
      }
   }

  // If push time is longer than threshold, fire dusruptors!
  if (buttonValue == LOW && (millis() - buttonDownTime) > long(holdTime)){
    buttonDownTime = millis();
    disruptorTime = millis();
    disruptorPushes++;
    ignoreUp = true;
   }
  
  // Record the button state for comparison in the next cycle
  buttonLast = buttonValue;    
 // ------------------------------------------------------------------------------------ //
  
  
 // ---------- Torpedo Firing --------------------------------------------------------- //
 // Ramp Up Red LED, Flash White LED, then a Ramp Down of Red LED
  // Ramp Up
  if ((currentMillis-torpedoTime) < torpUpTime && torpedoPushes > 0){
    analogWrite(torpPin[1],torpIdleBrightness+(torpMaxBrightness-torpIdleBrightness)/torpUpTime*(currentMillis-torpedoTime));
    digitalWrite(torpPin[0], LOW);
  }  
  // Flash
  else if (((currentMillis-torpedoTime) > torpUpTime) && ((currentMillis-torpedoTime) < (torpUpTime+torpFlashTime)) && torpedoPushes > 0){
    analogWrite(torpPin[1], 0);
    digitalWrite(torpPin[0], HIGH);
  } 
  // Ramp Down
  else if (((currentMillis-torpedoTime) > (torpUpTime+torpFlashTime)) && ((currentMillis-torpedoTime) < (torpUpTime+torpFlashTime+torpDownTime)) && torpedoPushes > 0){
    analogWrite(torpPin[1],torpMaxBrightness+(torpIdleBrightness-torpMaxBrightness)/torpDownTime*((currentMillis-torpedoTime)-(torpUpTime+torpFlashTime)));
    digitalWrite(torpPin[0], LOW);
  }  
  // Idle
  else{
    analogWrite(torpPin[1], torpIdleBrightness);
    digitalWrite(torpPin[0], LOW);
  }
 // ------------------------------------------------------------------------------------ //
 
 
 // ---------- Engine Fading ----------------------------------------------------------- //
  // Slow Up and Down Fade with Shorter Pusations
  int fadeValue = int(127.0+127.0/2.0*(1.0+(0.75*sin(2.0*PI*currentMillis/engineFadePeriod)+0.25*cos(14.0*PI*currentMillis/engineFadePeriod))));
  analogWrite(enginePin,fadeValue);
 // ------------------------------------------------------------------------------------ //
 
 
 // ---------- Disruptor Firing -------------------------------------------------------- //
  // Get Random On or Off Time Using getRandom() Function Below
  disruptorFlashTime = fmod(getRandom(), 4000UL) + 80UL;
  if (((currentMillis - disruptorTime) < disruptorFiringTime) && (disruptorPushes > 0)){
    if(currentMillis - disruptorMillis > disruptorFlashTime) {
      disruptorMillis = currentMillis;
      digitalWrite(disruptorPin, disruptorState = !disruptorState);
     } 
   }
   else{
     analogWrite(disruptorPin,disruptorIdleBrightness);
    }
 // ------------------------------------------------------------------------------------ //
}
// ===================== End Main Loop ======================================================== //



// ===================== Pseduo-Random Generator ============================================== //
// Found This Online. I Take No Credit for It.
unsigned long m_w = 1;
unsigned long m_z = 2; 

unsigned long getRandom()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}
// ===================== End Pseduo-Random Generator ========================================== //
