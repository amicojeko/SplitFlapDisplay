# SplitFlapDisplay
Split flap display Arduino library

## Introduction

This is a simple high level library to drive split flap display letters with Arduino. 

### Note:

>It assumes that each letter uses 2 Arduino pins, one to make the letter flap through a relay, and one hall sensor, that will return 0 only when the display is at the first character. It is also assumes that the hall sensor is using a 20K pull up resistor. 

## Installation

- Go to the Releases page.
- Download the latest release.
- Extract the zip file
- In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Reference

`isReady();`

Returns false if any of the letters is still flapping.

**returns:** true|false


`print(char letter);`

Prints the same character on all the display letters.

**note:**
> The display will only print characters in the ALPHABET array (see SplitFlapLetter.cpp)

`print(char* letter);`

Displays the provided char array on the display.
           Only the first `lettersNumber` will be displayed, all
           the remaining characters will be ignored. 
           
**note:**
> The display will only print characters in the ALPHABET array (see SplitFlapLetter.cpp)  

`refresh();`

Refresh is intended as refresh in displays. Perhaps I should have called it `tick` or `loop`. By the wai, this is what keeps the display going, it must be called at each Arduino `loop()` iteration.

`reset();`

Resets all the letters in the display to the first character (usually " ")

## Example

```c++
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
```

## License

Copyright (c) 2020 Stefano Guglielmetti

This software is released under the MIT License.

https://opensource.org/licenses/MIT