/*
 * This file contains an example of code that turns an LED on or off using a toggle switch.
 * 
 * The wiring for this project is as follows:
 * - 1 LED wired to pin #12 (pin #12 -> resistor -> positive LED leg; negative LED leg -> ground)
 * - 1 toggle switch wired to pin #11 (pin #11 -> toggle switch pin 1; toggle switch pin 2 -> ground)
 * 
 * See https://github.com/Beaver-Country-Day-School/arduino_examples for other examples. 
 */

const int LED_PIN = 12;
const int SWITCH_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // Here we use "INPUT_PULLUP" mode. This uses an internal resistor on the Arduino to
  // ensure that the switch reads low when on, and high when off.
  // If you use "INPUT" by accident, you will see the value of the switch change randomly,
  // because when the switch is toggled off, the signal is not pulled to ground.
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  const int buttonState = digitalRead(SWITCH_PIN);
  Serial.println(digitalRead(SWITCH_PIN));

  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
}
