// Copyright (c) 2020 Stefano Guglielmetti
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "SplitFlapDisplay.h"

SplitFlapDisplay::SplitFlapDisplay() {}

void SplitFlapDisplay::begin(int lettersNumber, int letterPins[], int hallPins[],
                        int flapDelay, Adafruit_MCP23008& mcp) {
  // here the pointer this->lettersNumber is used to disambiguate from the
  // lettersNumber parameter
  this->lettersNumber = lettersNumber;

  // same as above
  this->flapDelay = flapDelay;

  // initialize a new SplitFlapLetter object for each letter of the display
  for (int i = 0; i < lettersNumber; i++) {
    letters[i] = SplitFlapLetter(letterPins[i], hallPins[i], mcp);
  }

  previousMillis = 0;  // reset the internal non blocking delay timer

  reset();  // as soon as the display is initialized, resets all the letters
}

// the display is ready if all the letters are ready
bool SplitFlapDisplay::isReady() {
  for (int i = 0; i < lettersNumber; i++) {
    if (!letters[i].isReady()) return false;
  }
  return true;
}

// reset all the letters
void SplitFlapDisplay::reset() {
  for (int i = 0; i < lettersNumber; i++) {
    letters[i].reset();
  }
}

// print a single character on all the letters
// i.e. display.print('A');
void SplitFlapDisplay::print(char letter) {
  if (!isReady()) return;

  for (int i = 0; i < lettersNumber; i++) {
    letters[i].print(letter);
  }
}

// print an array of characters
// i.e. display.print("JEKO RULEZ");
void SplitFlapDisplay::print(char* letter) {
  if (!isReady()) return;

  for (int i = 0; i < lettersNumber; i++) {
    letters[i].print(letter[i]);
  }
}

// This must be invoked at each Arduino loop iteration, it will use a non
// blocking delay to send a refresh signal to all the letters each flapDelay
// milliseconds, so they will run (almost) simultaneously. We also achieve the
// nice to have side effect of non blocking the host Arduino script.
void SplitFlapDisplay::refresh() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= flapDelay) {
    previousMillis = currentMillis;

    for (int i = 0; i < lettersNumber; i++) {
      letters[i].refresh();
    }
  }
}

// This method will brutally flap all the letters, it shouldn't really be there
// and the corresponding SplitFlapLetter::flap() method should be private
// I've added it for demo purposes (see the split_flap_song example)
void SplitFlapDisplay::flap() {
  for (int i = 0; i < lettersNumber; i++) {
    letters[i].flap();
  }
}

// Same as above, but only flaps the specified letter
void SplitFlapDisplay::flap(int letter) { letters[letter].flap(); }