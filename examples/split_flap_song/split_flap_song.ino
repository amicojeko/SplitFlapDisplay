#include <SplitFlapDisplay.h>

// Delay between palette flaps. 80 is a safe value
#define FLAP_DELAY 80

// Reset button pin. Doesn't require additional pull up resistors
#define BUTTON_PIN 12

// Number of display letters
#define DISPLAY_LENGTH 2

#define LONG_NOTE 500
#define SHORT_NOTE 250

// Relay pins of the single letters
int letterPins[] = {10, 11};

// Hall sensor pins of the single letters
// They must follow the same order of letterPins
int hallPins[] = {6, 7};

// Buffer used to send the serial data to the display
char buf[DISPLAY_LENGTH];

// Initialize the display object
SplitFlapDisplay display(DISPLAY_LENGTH, letterPins, hallPins, FLAP_DELAY);

void setup() {
  /// Initialize the reset pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  display.refresh();

  if (digitalRead(BUTTON_PIN) == LOW) {
    
    display.flap();
    delay(LONG_NOTE);
    display.flap();
    delay(LONG_NOTE);

    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(LONG_NOTE);

    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(LONG_NOTE);

    display.flap();
    delay(SHORT_NOTE);
    display.flap();
    delay(LONG_NOTE);

    delay(5000);
  }
}
