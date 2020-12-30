// Copyright (c) 2020 Stefano Guglielmetti
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <SplitFlapDisplay.h>

// Delay between palette flaps. 80 is a safe value
#define FLAP_DELAY 80

// Button pin. Doesn't require additional pull up resistors
#define BUTTON_PIN 12

// Number of display letters
#define DISPLAY_LENGTH 2

// Relay pins of the single letters
int letterPins[] = {10, 11};

// Hall sensor pins of the single letters
// They must follow the same order of letterPins
int hallPins[] = {6, 7};

// Initialize the display object
SplitFlapDisplay display(DISPLAY_LENGTH, letterPins, hallPins, FLAP_DELAY);

void setup() {
  // Initialize the button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  display.refresh();

  if (digitalRead(BUTTON_PIN) == LOW) {
    display.print("OK");
  }
}
