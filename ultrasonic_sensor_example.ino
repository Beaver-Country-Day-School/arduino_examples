/*
 * This file contains an example of code that makes an LED blink rapidly when the ultrasonic sensor
 * senses something within 15cm. When nothing is detected, the LED stays on.
 * 
 * This project requires the HCSR04 library by Martin Sosic https://github.com/Martinsos/arduino-lib-hc-sr04. 
 * Install it through Tools->Manage Libraries. (Make sure you get the library by Martin Sosic, there are many
 * HC-SR04 libraries available)
 * 
 * The wiring for this project is as follows:
 * - 1 LED wired to pin #12 (pin #12 -> resistor -> positive LED leg; negative LED leg -> ground)
 * - 1 ultrasonic sensor (HC-SR04) with trigger wired to pin #10 and echo to pin #8
 *     (HC-SR04 "Gnd" pin -> ground; HC-SR04 "VCC" pin -> 5V power; HC-SR04 "Echo" pin -> pin #8; HC-SR04 "Trig" pin -> pin #10)
 * 
 * See https://github.com/Beaver-Country-Day-School/arduino_examples for other examples.
 */

#include <HCSR04.h>

const int LED_PIN = 12;
const int TRIGGER_PIN = 10;
const int ECHO_PIN = 8;

UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
  float distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);

  if(distance > 0.0 && distance < 15.0) {
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
  
}
