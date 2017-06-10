/*

 */

// import the library
//#include <Servo.h>
#include <PCJoy.h>
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
// create an instance of the servo library
//Servo leftServo;
//Servo headServo;
PCJoy myJoy(A0, A1, 6, 7);

const int leftLed = 4;    // pin the left LED is attached to
const int rightLed = 5;    // pin the right LED is attached to
//const int leftServoPin = 0; // pin the Servo is attached to
//const int headServoPin = 0; // pin the Servo is attached to
//const int headMoveDelay = 10; // speed
//int pos = 90;

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 1
#define SFX_RX 2

// Connect to the RST pin on the Sound Board
#define SFX_RST 0
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

void setup() {
  // attach the servo 
//  headServo.attach(headServoPin);
//  leftServo.attach(leftServoPin);

  // make the LED pins outputs
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);

  // start serial communication for debugging
  Serial.begin(9600);

  // cycle LEDs
  digitalWrite(leftLed, HIGH);
  delay(500);
  digitalWrite(leftLed, LOW);
  digitalWrite(rightLed, HIGH);
  delay(500);
  digitalWrite(rightLed, LOW);
  ss.begin(9600);
  sfx.reset();
  delay(500);
  sfx.playTrack(1);
  // print status to the serial monitor
  Serial.println("the system is ready!");
}

void loop() {
  PCJoy_State joyState = myJoy.getState();
  if (joyState.isConnected){
    if (joyState.aDown){
      fire(); 
    }
//    Serial.print("Servo at :");
//    Serial.print(headServo.read());
//    Serial.print(" Joy at :");
//    Serial.println(joyState.yPos);
////    pos = headServo.read();
//    while(joyState.yPos == 99){
//      if (pos <= 180){
//        pos += 1;
//        headServo.write(pos);              // tell servo to go to position in variable 'pos'
//        delay(headMoveDelay);                       // waits 15ms for the servo to reach the position        
//        pos = headServo.read();
//      } 
//      joyState = myJoy.getState();
//    }
//    while(joyState.yPos == -99){
//      if (pos >= 0){
//        pos -= 1;
//        headServo.write(pos);              // tell servo to go to position in variable 'pos'
//        delay(headMoveDelay);                       // waits 15ms for the servo to reach the position
//        pos = headServo.read();
//      }
//      joyState = myJoy.getState();
//    }
  }
}

void playSound() {
  sfx.playTrack(1);
//  delay(10);
}

void fire() {     
  // change the status LEDs
  Serial.println("firing started");
  digitalWrite(leftLed, HIGH);
 
  playSound();
 
  digitalWrite(leftLed, LOW);
//  leftServo.write(90);
  delay(100);
//  leftServo.write(180);
  digitalWrite(rightLed, HIGH);
  delay(200);
  digitalWrite(rightLed, LOW);
//  leftServo.write(0);
  digitalWrite(rightLed, LOW);

  
  // print out status
  Serial.println("firing finished");
  Serial.println("done!");
}


