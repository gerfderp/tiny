

/*

 */

// import the libraries needed
#include <WiiChuck.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define leftLed 4    // pin the left LED is attached to
#define rightLed 5    // pin the right LED is attached to
#define AUDIOPIN 3
Nunchuck nunchuck(SDA, SCL);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Serial.println("Tiny waking up!");
  //setup Nunchuck
  nunchuck.begin();

  nunchuck.addMap(new Nunchuck::joyX(5,200,128,10)); // Servo pin, max servo value, zero center value, min servo value 
  nunchuck.addMap(new Nunchuck::joyY(6,200,128,10)); // Servo pin, max servo value, zero center value, min servo value                                                          
  nunchuck.addMap(new Nunchuck::buttonZ(7,200,128,10)); // Servo pin, max servo value, zero center value, min servo value 
  nunchuck.addMap(new Nunchuck::buttonC(8,200,128,10)); // Servo pin, max servo value, zero center value, min servo value 

  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency
 
  //make Audiopin output
  pinMode(AUDIOPIN, OUTPUT);
  // Set the pin high as the default state
  digitalWrite(AUDIOPIN, HIGH); 
  
  // cycle LEDs
  pwm.setPWM(leftLed, 4096, 0);
  delay(500);
  pwm.setPWM(leftLed, 0, 0);
  
  pwm.setPWM(rightLed, 0, 0);
  delay(500);
  pwm.setPWM(rightLed, 4096, 0);
  Serial.println("Tiny setup finish!");
}

void loop() {
  digitalWrite(AUDIOPIN, HIGH);
  nunchuck.readData();   // Read inputs and update maps

  if (nunchuck.checkButtonC()){
    fire(); 
  }

}

void fire() {     
  // change the status LEDs
  Serial.println("firing started");
  pwm.setPWM(leftLed, 4096, 0);
  // bring the pin low to begin the activation
  digitalWrite(AUDIOPIN, LOW); 
  delay(300);
  pwm.setPWM(leftLed, 0, 0);

  pwm.setPWM(rightLed, 0, 0);
  delay(200);
  pwm.setPWM(rightLed, 4096, 0);
  // bring the pin high again to end the activation
  digitalWrite(AUDIOPIN, HIGH); 

}

