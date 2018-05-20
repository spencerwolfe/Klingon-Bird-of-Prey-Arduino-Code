// ===================== Variables =============================================================//
// -------  Declaring Pins ----------------------------------------------//
static byte disruptorPin = 0;
static byte enginePin = 1;
static byte pushButtonPin = 2;
static byte torpPin[] = { 3, 4 };

// -------  User Inputs ------------------------------------------------//
static unsigned long torpUpTime = 1750;
static unsigned long torpFlashTime = 200;
static unsigned long torpDownTime = 150;
static long double torpIdleBrightness = 10;
static long double torpMaxBrightness = 255;
static unsigned long engineFadePeriod = 6000;
static unsigned long disruptorFiringTime = 8000;

// -------  For the Button Pushing -------------------------------------//
unsigned long debounce = 30;
unsigned long holdTime = 1500;

// -------  Bookeeping ------------------------------------------------//
unsigned long currentMillis;
boolean buttonValue = false;
boolean buttonLast = false;
boolean ignoreUp = false;
unsigned long buttonUpTime;
unsigned long buttonDownTime;
unsigned int torpedoPushes = 0;
unsigned int disruptorPushes = 0;
unsigned long torpedoTime;
unsigned long disruptorTime;
unsigned long torpedoMillis;
unsigned long disruptorMillis;
unsigned long disruptorFlashTime;
boolean disruptorState = 0;
// ==================== End Variables ========================================================= //



// ===================== Setup ================================================================ //
void setup() {
  pinMode(disruptorPin,OUTPUT);
  pinMode(enginePin,OUTPUT);
  pinMode(pushButtonPin,INPUT_PULLUP);     // Enables internal pull-up resistor
  pinMode(torpPin[0],OUTPUT);
  pinMode(torpPin[1],OUTPUT);
  //DDRB = DDRB | (1 <<  disruptorPin) | (1 << enginePin) | ( 1 << torpPin[0] ) | ( 1 << torpPin[1] );
  //DDRB = DDRB & ~(1 << pushButtonPin);
  //PORTB = PORTB | (1 << pushButtonPin);

}
// ===================== End Setup ============================================================ //



// ===================== Main Loop ============================================================ //
void loop() {
  currentMillis = millis();         // get current time
  
 // ---------- Push Buttoon Code --------------------------------------------------------//
 // Found Most of This Online. I Take No Credit for It.
  buttonValue = digitalRead(pushButtonPin);
  //buttonValue = (PINB & (1 << pushButtonPin)) >> pushButtonPin;
  
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
 // -------------------------------------------------------------------------------------//
  
  
  
 // ---------- Torpedo Firing ----------------------------------------------------------//
 // Ramp Up Red LED, Flash White LED, then a Ramp Down of Red LED
  // Ramp Up
  if ((currentMillis-torpedoTime) < torpUpTime && torpedoPushes > 0){
    analogWrite(torpPin[1],torpIdleBrightness+(torpMaxBrightness-torpIdleBrightness)/torpUpTime*(currentMillis-torpedoTime));
    digitalWrite(torpPin[0], LOW);
    //PORTB = PORTB & ~(1 << torpPin[0]);
  }  
  // Flash
  else if (((currentMillis-torpedoTime) > torpUpTime) && ((currentMillis-torpedoTime) < (torpUpTime+torpFlashTime)) && torpedoPushes > 0){
    analogWrite(torpPin[1], 0);
    digitalWrite(torpPin[0], HIGH);
    //PORTB = PORTB | (1 << torpPin[0]);
  } 
  // Ramp Down
  else if (((currentMillis-torpedoTime) > (torpUpTime+torpFlashTime)) && ((currentMillis-torpedoTime) < (torpUpTime+torpFlashTime+torpDownTime)) && torpedoPushes > 0){
    analogWrite(torpPin[1],torpMaxBrightness+(torpIdleBrightness-torpMaxBrightness)/torpDownTime*((currentMillis-torpedoTime)-(torpUpTime+torpFlashTime)));
    digitalWrite(torpPin[0], LOW);
    //PORTB = PORTB & ~(1 << torpPin[0]);
  }  
  // Idle
  else{
    analogWrite(torpPin[1], torpIdleBrightness);
    digitalWrite(torpPin[0], LOW);
    //PORTB = PORTB & ~(1 << torpPin[0]);
  }
 // ------------------------------------------------------------------------------------ //
 
 
 
 // ---------- Engine Fading ----------------------------------------------------------- //
  // Slow Up and Down Fade with Shorter Pusations
  int fadeValue = int(127.0+127.0/2.0*(1+(0.75*sin(2*PI*currentMillis/engineFadePeriod)+0.25*cos(14*PI*currentMillis/engineFadePeriod))));
  analogWrite(enginePin,fadeValue);
 // ------------------------------------------------------------------------------------ //
 
 
 
 // ---------- Disruptor Firing -------------------------------------------------------- //
  // Get Random On or Off Time Using getRandom() Function Below
  disruptorFlashTime = fmod(getRandom(), 4000UL) + 60UL;
  if (((currentMillis - disruptorTime) < disruptorFiringTime) && (disruptorPushes > 0)){
    if(currentMillis - disruptorMillis > disruptorFlashTime) {
      disruptorMillis = currentMillis;  
      digitalWrite(disruptorPin, disruptorState = !disruptorState);
      //PORTB = ( (disruptorState = !disruptorState) ? (PORTB | (1 << disruptorPin)) : (PORTB & ~(1 << disruptorPin)) );
     } 
   }
   else{
     analogWrite(disruptorPin,5);
     //PORTB = PORTB & ~(1 << disruptorPin);
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
