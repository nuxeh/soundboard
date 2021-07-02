#include <Arduino.h>

/* Constants, may be changed as desired */

const int buttonPins[] = {
  A1, A2, A3, A4,
  10, 11, 12, A0,
  9,  8,  7,  6,
  2,  3,  4,  5
};

const int buttonMidiNotes[] = {
  72, 73, 74, 75,
  68, 69, 70, 71,
  64, 65, 66, 67,
  60, 61, 62, 63,
};

// Midi note 60 is middle C (C4), bottom left button

// Number of times a button must be observed to be in a consistent state to send MIDI notes
// This may be tweaked to alter debouncing performance - lower results in lower
// latency, but higher chance of falsely repeated triggers
const int changeThreshold = 8;

/* State */
// This is mostly state to track button states, and perform switch debouncing.
// In general they shouldn't be changed manually

int buttonState[16] = {HIGH}; // All off
int buttonLastState[16] = {HIGH}; // All off
int buttonUnchangedCount[16] = {0};

// HIGH represents off, since the input pins are pulled high by default, and
// switched to ground when pressed.

void setup() {
  // Start-up flash sequence (three times long, three times short)
  flash(100);
  flash(100);
  flash(100);
  flash(50);
  flash(50);
  flash(50);

  // Set all pins as inputs, enable internal pull up resistors to positive supply (Vdd)
  for (int i=0; i<16; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Loop through all buttons to read all button states
  for (int i=0; i<16; i++) {
    // Detect the current state for the current button
    int state = digitalRead(buttonPins[i]);

    if (state == buttonLastState[i]) {
      // The button is in the same state as previous round of measurements,
      // increment counter.
      buttonUnchangedCount[i]++;
    } else {
      // The button has changed state, reset the counter
      buttonUnchangedCount[i] = 0;
    }

    // Check to see if we've reached the detection threshold for debouncing
    if (buttonUnchangedCount >= changeThreshold) {
      // Stash the last state into a local variable
      lastState = buttonState[i];

      // We have reached the trigger threshold, send MIDI notes
      if (state == LOW && lastState == HIGH) {
        sendNoteOn(buttonMidiNotes[i]);
      } else if (state == HIGH && lastState == LOW) {
        sendNoteOff(buttonMidiNotes[i]);
      } else { /* Do nothing, no state change */ }
      
      // Update the button's current state
      buttonState[i] = state;
    }

    // Update the last checked instantaneous button state
    buttonLastState[i] = state;
  }
}

void sendNoteOn(int note) {

}

void sendNoteOff(int note) {

}

void flash(int d) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(d);
  digitalWrite(LED_BUILTIN, LOW);
  delay(d);
}
