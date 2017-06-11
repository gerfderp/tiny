/*

 */

// import the libraries needed
#include <PCJoy.h>

const int leftLed = 4;    // pin the left LED is attached to
const int rightLed = 5;    // pin the right LED is attached to
#define AUDIOPIN 3
PCJoy myJoy(A0, A1, 6, 7);

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
}

void loop() {
  digitalWrite(AUDIOPIN, HIGH);
  PCJoy_State joyState = myJoy.getState();
  if (joyState.isConnected){
    if (joyState.aDown){
      fire(); 
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

