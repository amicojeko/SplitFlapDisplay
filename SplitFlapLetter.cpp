// Copyright (c) 2020 Stefano Guglielmetti
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "SplitFlapLetter.h"

SplitFlapLetter::SplitFlapLetter() {}

SplitFlapLetter::SplitFlapLetter(int relayPin, int hallPin) {
  this->relayPin = relayPin;
  this->hallPin = hallPin;
  init();
}

SplitFlapLetter::SplitFlapLetter(int relayPin, int hallPin,
                                 Adafruit_MCP23008& mcp) {
  mcp.pinMode(relayPin, OUTPUT);
  mcp.pinMode(hallPin, INPUT);
  mcp.pullUp(hallPin, HIGH);

  this->relayPin = relayPin;
  this->hallPin = hallPin;
  this->mcp = mcp;
  init();
}

// This is hardcoded, and it's a static constant. This means that it's
// shared among all the istances of SplitFlapLetter. It saves a lot of
// memory, but in a real world scenario, each letter could have it's own
// array. In that case, this strategy should be revised as arduino will
// likely run out of memory.
const char SplitFlapLetter::ALPHABET[] = {
    ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-', '.', '/'};

// Assume that we are ready to receive new commands only when the letter is not
// flapping (STATE_IDLE). Maybe STATE_IDLE could be renamed as STATE_READY
bool SplitFlapLetter::isReady() { return (state == STATE_IDLE); }

// Resets the letter to the first character
// Will be ignored if the letter is still flapping
void SplitFlapLetter::reset() {
  if (state != STATE_IDLE) return;

  state = STATE_RESET;
}

// Sets the letter to the provided character
// Will be ignored if the letter is still flapping
void SplitFlapLetter::print(char letter) {
  if (state != STATE_IDLE) return;
  if (!isValidLetter(letter)) return;

  // The letter will keep flapping until it reaches the
  // requested character
  targetLetter = letter;
  state = STATE_PRINTING;
}

// invoked at each Arduino loop iteration.
void SplitFlapLetter::refresh() {
  switch (state) {
    case STATE_IDLE:
      break;
    case STATE_RESET:
      // When the state is STATE_RESET, the letter keeps flapping
      // until the hall sensor is false, meaning that the letter
      // reached the first character (usually " ")
      // Then the internal position counter currentPosition
      // is set to zero
      shouldFlap = mcp.digitalRead(hallPin);
      if (!shouldFlap) currentPosition = 0;
      break;
    case STATE_PRINTING:
      // When the state is STATE_PRINTING, the letter keeps flapping
      // until the current letter is the target letter
      shouldFlap = (currentLetter() != targetLetter);
      break;
    default:
      break;
  }

  // flaps the letter if required, otherwise assume that the state
  // should be STATE_IDLE
  if (shouldFlap) {
    flap();
  } else {
    state = STATE_IDLE;
  }
}

void SplitFlapLetter::flap() {
  // inverts the polarity at each flap
  relayState = !relayState;
  mcp.digitalWrite(relayPin, relayState);
  incrementPosition();
}

// increments the currentPosition
// if currentPosition reaches the last ALPHABET character
// it will be set to zero
void SplitFlapLetter::incrementPosition() {
  if (currentPosition == (sizeof(ALPHABET) - 1)) {
    currentPosition = 0;
  } else {
    currentPosition++;
  }
}

// current character (char)
char SplitFlapLetter::currentLetter() { return ALPHABET[currentPosition]; }

// verifies if the letter is available in the ALPHABET
bool SplitFlapLetter::isValidLetter(char letter) {
  for (int i = 0; i < sizeof(ALPHABET); i++) {
    if (letter == ALPHABET[i]) return true;
  }
  return false;
}