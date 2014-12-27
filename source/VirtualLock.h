// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// VirtualLock.h
//  Lock that could only be unlock through the answer of a riddle. 
//  
//  For memory managment the object DO NOT allocate the memory needed for mText and mAnswer. User is responsible for managing those strings.
//---------------------------------------------------------
#ifndef _VIRTUAL_LOCK_H_
#define _VIRTUAL_LOCK_H_

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Driver display
#include <RTClib.h>

class VirtualLock 
{
public:
  VirtualLock(const char* _text, const char* _answer, DateTime _time);
  
  void setText(const char* _text);
  void setAnswer(const char* _answer);
  void drawText(Adafruit_ILI9341& tft, int16_t _x, int16_t _y, const DateTime& time);
  void drawState(Adafruit_ILI9341& tft, int16_t _x, int16_t _y);
  bool unlock(const char* answerTry, const DateTime& time);

private:
  const char* mText;
  const char* mAnswer;
  DateTime    mTime;
  bool        mOpen;
};

#endif// _VIRTUAL_LOCK_H_
