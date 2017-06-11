/*

 */

// import the libraries needed
#include <PCJoy.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int leftLed = 4;    // pin the left LED is attached to
const int rightLed = 5;    // pin the right LED is attached to
#define AUDIOPIN 3

//Using Analog 0 and 1 AND Digital 6 and 7
PCJoy myJoy(A0, A1, 6, 7);

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  // make the LED pins outputs
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  //make Audiopin output
  pinMode(AUDIOPIN, OUTPUT);
  // Set the pin high as the default state
  digitalWrite(AUDIOPIN, HIGH); 
  
  // cycle LEDs
  digitalWrite(leftLed, HIGH);
  delay(500);
  digitalWrite(leftLed, LOW);
  digitalWrite(rightLed, HIGH);
  delay(500);
  digitalWrite(rightLed, LOW);

  //Servo Shield setup
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  yield();
}

void loop() {
  digitalWrite(AUDIOPIN, HIGH);
  PCJoy_State joyState = myJoy.getState();
  if (joyState.isConnected){
    if (joyState.aDown){
      fire(); 
    }
    //TODO: Need to figure out current position
    int pos0 = 0;
    
    while(joyState.yPos == 99){
      if (pos <= SERVOMAX){
        pos += 1;
        headServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(headMoveDelay);                       // waits 15ms for the servo to reach the position        
        pos = headServo.read();
      } 
      joyState = myJoy.getState();
    }
    while(joyState.yPos == -99){
      if (pos >= SERVOMIN){
        pos -= 1;
        headServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(headMoveDelay);                       // waits 15ms for the servo to reach the position
        pos = headServo.read();
      }
      joyState = myJoy.getState();
    }
  }
}

void fire() {     
  // change the status LEDs
  Serial.println("firing started");
  digitalWrite(leftLed, HIGH);
  // bring the pin low to begin the activation
  digitalWrite(AUDIOPIN, LOW); 
  delay(300);
  digitalWrite(leftLed, LOW);

  digitalWrite(rightLed, HIGH);
  delay(200);
  digitalWrite(rightLed, LOW);
  // bring the pin high again to end the activation
  digitalWrite(AUDIOPIN, HIGH); 
  digitalWrite(rightLed, LOW);

}

