
#include <Adafruit_MCP23008.h>
#include <Arduino.h>
#include <SplitFlapDisplay.h>
#include <Wire.h>

// Delay between palette flaps. 80 is a safe value
#define FLAP_DELAY 80

// Reset button pin. Doesn't require additional pull up resistors
#define BUTTON_PIN 12

// Number of display letters
#define DISPLAY_LENGTH 2

// Relay pins of the single letters on the MCP23008
int letterPins[] = {0, 2};

// Hall sensor pins of the single letters on the MCP23008
// They must follow the same order of letterPins
int hallPins[] = {1, 3};

Adafruit_MCP23008 mcp;
SplitFlapDisplay display;

void setup() {
  mcp.begin();
  display.begin(DISPLAY_LENGTH, letterPins, hallPins, FLAP_DELAY, mcp);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    display.print("OK");
  }
  display.refresh();
}