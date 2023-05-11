#include <HCSR04.h>

const int LED_PIN = 12;
const int BUTTON_PIN = 11;
//const int TWIST_POTENTIONMETER = 10;

const int TRIGGER_PIN = 10;
const int ECHO_PIN = 8;
UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //pinMode(TWIST_POTENTIOMETER, INPUT);

  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {

  const int buttonState = digitalRead(BUTTON_PIN);
  int knobValue = analogRead(A0);
  int slideValue = analogRead(A1);

  float distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);  

  Serial.print(knobValue);
  Serial.print(", ");
  Serial.print(slideValue);
  Serial.print(", ");
  Serial.print(distance);
  Serial.println();

  if(distance < 15.0 && distance > 0.0) {
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);
  } else if (buttonState == LOW) {
    int blinkOnSpeed = map(knobValue, 0, 1000, 100, 2000);
    int blinkOffSpeed = map(slideValue, 0, 1000, 100, 2000);
    digitalWrite(LED_PIN, HIGH);
    delay(blinkOnSpeed);
    digitalWrite(LED_PIN, LOW);
    delay(blinkOffSpeed);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
}
