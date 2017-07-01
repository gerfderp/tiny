

/*

 */

// import the libraries needed
#include <WiiChuck.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define leftLed 2    // pin the left LED is attached to
#define leftServo 0 //pin the left servo is attached
#define rightLed 3    // pin the right LED is attached to
#define rightServo 1
#define AUDIOPIN 3

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

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
  // change the status LEDs           margie poo
  
  Serial.println("firing started");

  
  pwm.setPWM(leftLed, 4096, 0);
  
  // bring the pin low to begin the activation
  digitalWrite(AUDIOPIN, LOW); 
  recoil(leftServo);
  pwm.setPWM(leftLed, 0, 0);

  pwm.setPWM(rightLed, 4096, 0);
  recoil(rightServo);
  pwm.setPWM(rightLed, 0, 0);
 
  // bring the pin high again to end the activation
  digitalWrite(AUDIOPIN, HIGH); 

}

void recoil(int cannon){
  if (cannon == rightServo){
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen = pulselen- 10) {
      pwm.setPWM(cannon, 0, pulselen);
    }
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(cannon, 0, pulselen);
    }
  } else { 
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen = pulselen + 10) {
      pwm.setPWM(cannon, 0, pulselen);
    }
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(cannon, 0, pulselen);
    }
  }
}

