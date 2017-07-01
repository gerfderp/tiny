#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define leftLed 2    // pin the left LED is attached to
#define rightLed 3    // pin the right LED is attached to

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency
}

void loop() {
  // put your main code here, to run repeatedly:
pwm.setPWM(leftLed, 4096, 0);
  delay(500);
  pwm.setPWM(leftLed, 0, 0);
  delay(500);
  pwm.setPWM(rightLed, 4096, 0);
  delay(500);
  pwm.setPWM(rightLed, 0, 0);
  delay(500);
  
}
