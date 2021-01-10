// Copyright (c) 2020 Stefano Guglielmetti
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SPLIT_FLAP_LETTER_H
#define SPLIT_FLAP_LETTER_H

#include <Adafruit_MCP23008.h>
#include <Arduino.h>

#define STATE_IDLE 0
#define STATE_RESET 1
#define STATE_PRINTING 2

class SplitFlapLetter {
 public:
  /*!
    @brief  SplitFlapLetter constructor when no parameters are provided
            used to initialize the internal array of letters in
            SplitFlapDisplay
  */
  SplitFlapLetter();

  /*!
    @brief  SplitFlapLetter constructor
    @param  relayPin arduino pin of the letter's relay
    @param  hallPin  arduino pin of the letter's relay
  */
  SplitFlapLetter(int relayPin, int hallPin);
  SplitFlapLetter(int relayPin, int hallPin, Adafruit_MCP23008& mcp);

  /*!
    @brief Resets the letter to blank
  */
  void reset();

  /*!
    @brief Refreshes the letter state. Usyal be called at each Arduino loop,
           usually invoked by SplitFlapDisplay
  */
  void refresh();

  /*!
    @brief  Letter's ready state, true if the letter is not flapping (state is
            STATE_IDLE).
    @return Letter ready state (boolean).
  */
  bool isReady();

  /*!
    @brief  Show the provided character, only if present in the ALPHABET
    array.
    @param  letter the charater to display.
  */
  void print(char letter);

  /*!
    @brief  Flaps the letter. Definitely should be private. It's public only
    for demo purposes, to manually flap the display and play nice 1 note
    songs.
  */
  void flap();

 private:
  static const char ALPHABET[40];
  Adafruit_MCP23008 mcp;

  byte state;     ///< Internal state, could be STATE_IDLE, STATE_RESET,
                  ///< STATE_PRINTING
  byte relayPin;  ///< Arduino pin of the relay
  byte hallPin;   ///< Arduino pin of the hall sensor
  byte currentPosition = 0;  ///< index of active character
  char targetLetter = ' ';   ///< character to display
  bool relayState = 0;  ///< internal state of the relay. Changes at every flap.
  bool shouldFlap = 0;  ///< wheter it should flap or not in the next iteration

  /*!
    @brief  increments current position and resets it to 0 when reaches the
    total letters number
  */
  void incrementPosition();

  /*!
    @brief  active character
    @return active character (char)
  */
  char currentLetter();

  /*!
    @brief  verifies if the provided character is present it the ALPHABET
    array
    @return true or false
  */
  bool isValidLetter(char letter);
};

#endif