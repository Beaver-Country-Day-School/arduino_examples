/*
 * This file contains an example of code that uses a potentiometer (knob) which controls how fast an LED blinks.
 * 
 * The wiring for this project is as follows:
 * - 1 LED wired to pin #12 (pin #12 -> resistor -> positive LED leg; negative LED leg -> ground)
 * - 1 potentiometer wired to analog input 1 (A1) (5V power -> potentiometer; potentiometer -> ground; potentiometer -> A1)
 * 
 * See https://github.com/Beaver-Country-Day-School/arduino_examples for other examples.
 */

const int LED_PIN = 12;
const int SLIDE_INPUT = A1; // analog pin 1

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
  int slideValue = analogRead(SLIDE_INPUT);
  Serial.println(slideValue);

  // The "map" function maps a value from one range into another.
  // The slide input will give us values from roughly 0 to 1000.
  // We want the delay in our blinks to be between 100 and 2000 milliseconds
  int blinkSpeed = map(slideValue, 0, 1000, 100, 2000);

  digitalWrite(LED_PIN, HIGH);
  delay(blinkSpeed);
  digitalWrite(LED_PIN, LOW);
  delay(blinkSpeed);  
}
