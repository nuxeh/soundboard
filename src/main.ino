#include <Arduino.h>

const int buttonPins[] = {
  A1, A2, A3, A4,
  10, 11, 12, A0,
  9,  8,  7,  6,
  2,  3,  4,  5
};

void setup() {
  // Set all pins as inputs, enable internal pull up resistors to positive supply (Vdd)
  for (int i=0; i<16; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {

}
