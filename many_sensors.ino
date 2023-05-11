/*
 * This file contains an example of code that controls the blinking of an LED based on
 * several input sensors.
 * 
 * This project requires the HCSR04 library by Martin Sosic https://github.com/Martinsos/arduino-lib-hc-sr04. 
 * Install it through Tools->Manage Libraries. (Make sure you get the library by Martin Sosic, there are many
 * HC-SR04 libraries available)
 * 
 * The wiring for this project is as follows:
 * - 1 LED wired to pin #12
 * - 1 toggle switch wired to pin #11
 * - 1 (knob) potentiometer wired to analog input #0 (A0)
 * - 1 slide potentiometer wired to analog input #1 (A1)
 * - 1 ultrasonic sensor (HC-SR04) with trigger wired to pin #10 and echo to pin #8
 * 
 * See https://github.com/Beaver-Country-Day-School/arduino_examples for simpler examples 
 * that go more in-depth on each sensor type.
 */

#include <HCSR04.h>

const int LED_PIN = 12;
const int SWITCH_PIN = 11;

const int TRIGGER_PIN = 10;
const int ECHO_PIN = 8;

const int KNOB_INPUT = A0; // analog pin 0
const int SLIDE_INPUT = A1; // analog pin 1

UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {

  const int buttonState = digitalRead(SWITCH_PIN);
  int knobValue = analogRead(KNOB_INPUT);
  int slideValue = analogRead(SLIDE_INPUT);

  float distance = distanceSensor.measureDistanceCm();

  Serial.print("Knob: ");
  Serial.print(knobValue);
  Serial.print(", Slide: ");
  Serial.print(slideValue);
  Serial.print(", Distance (cm): ");
  Serial.print(distance);
  Serial.println();

  if(distance > 0.0 && distance < 15.0) {
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
