// Copyright (c) 2020 Stefano Guglielmetti
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SPLIT_FLAP_DISPLAY_H
#define SPLIT_FLAP_DISPLAY_H

#include "SplitFlapLetter.h"

class SplitFlapDisplay {
 public:
  /*!
    @brief  SplitFlapDisplay constructor
    @param  lettersNumber the number of the total letters in the display
    @param  letterPins an array containing the relay pins of the single letters
    @param  lettehallPinsrPins an array containing the hall sensor pins of the
            single letters
    @param  flapDelay the delay between flaps in milliseconds. 80 has proven to
            be a safe value letters. Shorter times may result in flapping
            failures
  */
  SplitFlapDisplay(int lettersNumber, int letterPins[], int hallPins[], int flapDelay);

  /*!
    @brief   SplitFlapDisplay initialization. Automatically reset the display
    upon initialization.
  */
  void init();

  /*!
    @brief Resets the whole display to blank
  */
  void reset();

  /*!
    @brief  Refreshes the whole display. Must be called at each Arduino loop.
  */
  void refresh();
  
  /*!
    @brief  Cycles through all the letters ready state, and returns
            true if all the letters are ready.
    @return Display ready state (boolean).
  */
  bool isReady();

  /*!
    @brief  Displays the same character on all the display letters.
    @param  letter character to display (char).
  */
  void print(char letter);

  /*!
    @brief  Displays the provided char array on the display.
            Only the first <lettersNumber> will be displayed, all
            the remaining characters will be ignored.
    @param  letter characters to display (char array).
  */
  void print(char* letter);

  /*!
    @brief  Definitely could be removed. It's here only for demo purposes, to
            manually flap the display and play nice 1 note songs. When no
            parameters are provided, the whole display flaps.
  */
  void flap();

  /*!
    @brief   As above, but flaps only one letter
    @param   letter the id of the letter to flap, zero based.
  */
  void flap(int letter);

 private:
  byte lettersNumber;           ///< Number of letters in the display
  byte flapDelay;               ///< Delay between flaps
  unsigned long previousMillis; ///< Used by the internal non-blocking timer
  SplitFlapLetter letters[64];  ///< Letter objects
};

#endif