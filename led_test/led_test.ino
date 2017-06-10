const int leftLed = 4;    // pin the left LED is attached to
const int rightLed = 5;    // pin the right LED is attached to


void setup() {
  // put your setup code here, to run once:
 pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  digitalWrite(leftLed, HIGH);
  delay(500);
  digitalWrite(leftLed, LOW);
  digitalWrite(rightLed, HIGH);
  delay(500);
  digitalWrite(rightLed, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(leftLed, HIGH);
  delay(500);
  digitalWrite(leftLed, LOW);
  delay(500);
}
