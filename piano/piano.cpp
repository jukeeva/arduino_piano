/**
   Mini Piano for Arduino with additional range of notes. 

   
*/

#include "pitches.h"

#define SPEAKER_PIN_1 8  // First speaker pin
#define SPEAKER_PIN_2 9  // Second speaker pin

// Pins for the piano buttons
const uint8_t BUTTON_PINS[] = { 12, 11, 10, 7, 6, 5, 4, 3, A0, A1, A2, A3, A4, A5, 2, A7 };

// Frequencies for the notes corresponding to each button
const int NOTE_FREQUENCIES[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5
};

const int NUM_BUTTONS = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);  // Number of buttons

void setup() {
  // Set up button pins as inputs with pull-up resistors
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  // Set up the speaker pins as outputs
  pinMode(SPEAKER_PIN_1, OUTPUT);
  pinMode(SPEAKER_PIN_2, OUTPUT);
}

void loop() {
  int currentNoteFrequency = 0;  // Variable to store the frequency of the pressed note

  // Check each button to see if it's pressed
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {  // Button is pressed (LOW because of pull-up)
      currentNoteFrequency = NOTE_FREQUENCIES[i];  // Set the corresponding note frequency
      break;  // Exit the loop once a pressed button is found
    }
  }

  // Play the note if a button is pressed, otherwise stop the sound
  if (currentNoteFrequency > 0) {
    // Alternate between speakers for a richer sound
    if (currentNoteFrequency <= NOTE_C4) {
      tone(SPEAKER_PIN_1, currentNoteFrequency);  // Play lower notes on the first speaker
    } else {
      tone(SPEAKER_PIN_2, currentNoteFrequency);  // Play higher notes on the second speaker
    }
  } else {
    noTone(SPEAKER_PIN_1);  // Stop the sound on the first speaker
    noTone(SPEAKER_PIN_2);  // Stop the sound on the second speaker
  }
}
