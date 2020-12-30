#include <SplitFlapDisplay.h>

// Delay between palette flaps. 80 is a safe value
#define FLAP_DELAY 80

// Reset button pin. Doesn't require additional pull up resistors
#define RESET_PIN 12

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
  pinMode(RESET_PIN, INPUT_PULLUP);

  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB
  }
  Serial.begin(115200);

  
}

void loop() {
  display.refresh();

  // If serial data are available, copy the first <DISPLAY_LENGTH> characters to
  // a buffer and send it to the display.
  // All the characters after <DISPLAY_LENGTH> will be ignored
  // Only uppercase characters, numbers, space, "/", "-" and "." will be
  // printed. All the other characters will be ignored.
  while (Serial.available()) {
    int size = Serial.readBytesUntil('\n', buf, 2);
    for (int i = 0; i < size; i++) {
      Serial.print(char(toupper(buf[i])));
      display.print(buf);
    }

    // flush remaining serial buffer
    while (Serial.available()) {
      Serial.read();
    }
  }

  if (digitalRead(RESET_PIN) == LOW) {
    // display.reset();
    // display.print("LAAZ");
    
    
    // display.flap();
    // delay(LONG_NOTE);
    // display.flap();
    // delay(LONG_NOTE);

    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(LONG_NOTE);

    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(LONG_NOTE);

    // display.flap();
    // delay(SHORT_NOTE);
    // display.flap();
    // delay(LONG_NOTE);

    // delay(5000);

    display.print('2');
  }

  // display.print('2');
}
