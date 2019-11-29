/* 
 *  Creator : Kenny Brown
 *  University of Virginia - Mechanical and Aerospace Engineering
 *  Title : Spooling Fiber Distributor
 *  This sketch controls the speed and direction of a motor attached to a linear rail
 *  Limit switches are used to make the rail carriage traverse back and forth between a distance set by the physical position of the limit switches

 Hardware:
 Motor/Guide/Carriage: Upcycled from Epson Expression XP-440 Printer
 Controller: Arduino Uno R3
 Motor Driver: Adafruit DRV8871
 Limit Switches: 

** NOTE: MOTOR_IN1, LOW = Forward, MOTOR_IN2, LOW = Backward
*/

// Pin Callouts
const int buttonPin = 2;    // Motor On/Off Buttom
const int limitSwitch1 = 3; // Limit switch 1
const int limitSwitch2 = 4; // Limit switch 2
const int potPin = A0;      // Motor speed trim pot
const int MOTOR_IN1 = 9;    // Motor driver input 1
const int MOTOR_IN2 = 10;   // Motor driver input 2

//Variables
byte button;          // Button condition on this loop
byte oldbutton = 0;   // Previous button condition
byte state = 0;       // State of "on/off" switch

byte limit1;          // Limit switch #1 condition on this loop
byte oldlimit1 = 0;   // Previous limit switch #1 condition
byte limit2;          // Limit switch #2 condition on this loop
byte oldlimit2 = 0;   // Previous limit switch #2 condition
byte dir = 0;         // Motor direction state

int potValue = 0;     // Variable for trim pot value

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(limitSwitch1, INPUT);
  pinMode(potPin, INPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
}

void loop() {
  
  potValue = map(analogRead(potPin),0,1023,0,255);
  Serial.println(potValue);
  button = digitalRead(buttonPin);
  limit1 = digitalRead(limitSwitch1);
  limit2 = digitalRead(limitSwitch2);
  Serial.println(dir);
/*  ---------------------------------------------------------------------------
 *   ON/OFF BUTTON
 *  ---------------------------------------------------------------------------
 */
if(button && !oldbutton) // same as if(button == high && oldbutton == low)
 {
   //we have a new button press
   if(state == 0) // if the state is off, turn it on
   {
     //do stuff
     state = 1;
     Serial.println("Motor On");
   }
   else // if the state is on, turn it off
   {
     //do stuff
     state = 0;
     digitalWrite(MOTOR_IN1, LOW);
     digitalWrite(MOTOR_IN2, LOW);
     Serial.println("Motor Off"); 
   }
   oldbutton = 1;
 }
 else if(!button && oldbutton) // same as if(button == low && oldbutton == high)
 {
   // the button was released
   oldbutton = 0;
 }

 /* ---------------------------------------------------------------------------
 *   LIMIT SWITCH #1
 *  ---------------------------------------------------------------------------*/

if(limit1 && !oldlimit1) // same as if(limimt == high && oldlimit == low)
 {
   //we have a new button press
   if(dir == 0) // if the state is CCW, turn it CW
   {
     dir = 1;
     Serial.println("Motor CW");
   }
   else // if the state is CW, turn it CCW
   {
     dir = 0;
     Serial.println("Motor CCW"); 
   }
   oldlimit1 = 1;
 }
 else if(!limit1 && oldlimit1) // same as if(limit == low && oldlimit == high)
 {
   // the limit switch was released
   oldlimit1 = 0;
 }

  /* ---------------------------------------------------------------------------
 *   LIMIT SWITCH #2
 *  ---------------------------------------------------------------------------*/

if(limit2 && !oldlimit2) // same as if(limit == high && oldlimit == low)
 {
   //we have a new button press
   if(dir == 0) // if the state is CCW, turn it CW
   {
     dir = 1;
     Serial.println("Motor CW");
   }
   else // if the state is CW, turn it CCW
   {
     dir = 0;
     Serial.println("Motor CCW"); 
   }
   oldlimit2 = 1;
 }
 else if(!limit2 && oldlimit2) // same as if(limit == low && oldlimit == high)
 {
   // the limit switch was released
   oldlimit2 = 0;
 }
 
  /* ---------------------------------------------------------------------------
 *   SYSTEM OPERATION
 *  ---------------------------------------------------------------------------*/
 
if(state == 1) //If the motor is on then...
{
     if(dir == 1) //if the motor direction is clockwise...
          {
           digitalWrite(MOTOR_IN1, LOW);
           analogWrite(MOTOR_IN2, potValue);
          }
         else //if the motor direction is counterclockwise...
          {
           digitalWrite(MOTOR_IN2, LOW);
           analogWrite(MOTOR_IN1, potValue);
          }
}
     else // otherwise the motor is off
     {
     digitalWrite(MOTOR_IN1, LOW);
     digitalWrite(MOTOR_IN2, LOW);
     }
//---------------------------------------------------------------------------------------------

}

/*REFERENCES:
 * Example of button for on/off state: https://forum.arduino.cc/index.php?topic=114316.0
 * Tutorial for motor driver: https://learn.adafruit.com/adafruit-drv8871-brushed-dc-motor-driver-breakout/overview
 * TrimPot Control of a Motor: https://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/
