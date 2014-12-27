// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// VirtualLocksHelper.h
//  Helper to set virtual locks (riddles)
//---------------------------------------------------------
#ifndef _VIRTUAL_LOCKS_HELPER_H
#define _VIRTUAL_LOCKS_HELPER_H

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Driver display

#include <avr/pgmspace.h> //PROGPMEM to store text as the flash ram is only 2kb

#include "VirtualLock.h"

namespace VirtualLocksHelper 
{
  // -----------------------
  // Lock Data
  static const int LOCK_SZ = 3;
 
  // Riddles data 
  prog_char riddle_0[] PROGMEM = "Text of riffde 0";
  prog_char riddle_1[] PROGMEM = "Text of riffde 1";
  prog_char riddle_2[] PROGMEM = "Text of riffde 2";
  
  // Interface table
  PROGMEM const char *riddle_table[] = 	   // change "string_table" name to suit
  {   
    riddle_0,
    riddle_1,
    riddle_2
  };
  // Answer data
  const char* answer[LOCK_SZ] =
  {
    "SOLUTION0",
    "SOLUTION1",
    "SOLUTION2",
  };
  // Riddle buffer use to copy from PROGMEM. Must be large enough to get the biggest of the riddles.
  char riddle[256]; 
  // Table of virtual locks
  VirtualLock locks[LOCK_SZ] = 
  {
    VirtualLock(riddle, answer[0], DateTime(2014, 10, 22)),  
    VirtualLock(riddle, answer[1], DateTime(2014, 10, 26)),
    VirtualLock(riddle, answer[2], DateTime(2014, 11, 3)),
  };
  
  // -----------------------  
  // Runtime data
  int activeLock = 0;
  // -----------------------  
  // Helpers
  void drawLocksText(Adafruit_ILI9341& tft, int16_t _x, int16_t _y, const DateTime& time)
  {
     locks[activeLock].drawText(tft, _x, _y, time); 
  }
  
  void drawLocksState(Adafruit_ILI9341& tft, int16_t _x, int16_t _y)
  {
    tft.setCursor(_x, _y);
    tft.print("Riddles :");
    
    int16_t x = _x;
    int16_t y = _y + 20;
    
    for (int iLock = 0 ; iLock < LOCK_SZ ; iLock++) {
      locks[iLock].drawState(tft, x + (iLock%2)*15 , y+(iLock/2)*10);
    }    
  }
  
  bool update(const char* answer, const DateTime& time) 
  {
    if (locks[activeLock].unlock(answer, time)) {
      activeLock++;
      //Decompress text from PROGMEM
      if (activeLock != LOCK_SZ) {
        strcpy_P(riddle, (char*)pgm_read_word(&(riddle_table[activeLock])));
        locks[activeLock].setText(riddle);
      }
      return true;
    }
    return false;
  }
  
  void init() 
  {
    strcpy_P(riddle, (char*)pgm_read_word(&(riddle_table[activeLock])));
  }
}; // namespace VirtualLocksHelper

#endif //_VIRTUAL_LOCKS_HELPER_H
