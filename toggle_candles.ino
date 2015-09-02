// Cribbed the IR transmit routine from http://www.instructables.com/id/How-To-Useemulate-remotes-with-Arduino-and-Raspber/
// so I'm unsure of the license.

// and then hacked in some quick on/off for my candles for checking my hardware.
// TODO: Refactor, add the wifi parts.
 
 // IR DEFINITIONS
int IRledPin =          13;           // Pin for IR LED

uint16_t IRsignalOn[] = 
{
     // ON, OFF (in microseconds)
             9100,    4450,     600,     500,     650,     500,
              600,     500,     600,     500,     650,     500,
              600,     550,     600,     500,     650,     500,
              600,    1650,     600,    1650,     600,    1650,
              600,    1600,     650,    1650,     600,    1600,
              600,    1650,     650,    1600,     600,     550,
              600,     500,     600,     550,     600,     500,
              650,     500,     600,     550,     550,     550,
              600,     550,     550,    1650,     650,    1650,
              550,    1650,     600,    1650,     600,    1650,
              600,    1650,     600,    1650,     600,    1650,
              600
};

uint16_t IRsignalOff[] = 
{
     // ON, OFF (in microseconds)
             9150,    4400,     650,     500,     650,     500,
              600,     500,     650,     500,     600,     550,
              600,     500,     600,     550,     600,     500,
              600,    1650,     600,    1650,     600,    1650,
              600,    1650,     600,    1650,     600,    1650,
              600,    1650,     600,    1650,     600,    1650,
              600,     500,     650,     500,     600,     550,
              550,     550,     600,     500,     600,     550,
              600,     500,     650,     500,     600,    1650,
              600,    1650,     600,    1650,     600,    1650,
              600,    1650,     600,    1650,     600,    1650,
              600
};

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs)
{
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0)
  {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

void SendIRCodeOn()
{
  int arraySize = sizeof(IRsignalOn)/2;
  for (int i = 0; i < arraySize; i++)
  {
    pulseIR(IRsignalOn[i++]);
    delayMicroseconds(IRsignalOn[i]);
  }
}

void SendIRCodeOff()
{
  int arraySize = sizeof(IRsignalOff)/2;
  for (int i = 0; i < arraySize; i++)
  {
    pulseIR(IRsignalOff[i++]);
    delayMicroseconds(IRsignalOff[i]);
  }
}

void setup(void)
{
  pinMode(IRledPin, OUTPUT);      
  //Serial.begin(9600);
  //Serial.println("Ready to recreate IR!!!");
}

void loop(void)
{
  SendIRCodeOn();
  SendIRCodeOn();
  delay(1000);
  SendIRCodeOff();
  SendIRCodeOff();
  delay(1000);
}
