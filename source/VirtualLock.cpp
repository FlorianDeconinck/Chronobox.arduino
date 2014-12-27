// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// VirtualLock.cpp
//    see .h
//---------------------------------------------------------
#include "VirtualLock.h"
// ----------------------------------------------------------------------------
VirtualLock::VirtualLock(const char* _text, const char* _answer, DateTime _time)
{
  mText = _text;
  mAnswer = _answer;
  mTime = _time;
  mOpen = false;
}
// ----------------------------------------------------------------------------
void VirtualLock::setText(const char* _text)
{
  mText = _text;
}

// ----------------------------------------------------------------------------
void VirtualLock::setAnswer(const char* _answer)
{
  mAnswer = _answer;
}

// ----------------------------------------------------------------------------
void VirtualLock::drawText(Adafruit_ILI9341& tft, int16_t _x, int16_t _y, const DateTime& time)
{
  tft.fillRect(_x, _y, 320, 150, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setCursor(_x, _y);
  uint32_t normalizedNow = time.month()*100+time.day();  
  uint32_t normalizedTime = mTime.month()*100+mTime.day();
  if (normalizedNow >= normalizedTime) {
    tft.print(mText);
  } else {
    tft.println();
    tft.println("Tic ? Tac...");
    tft.println();
    tft.print(mTime.month(), DEC);
    tft.print('/');
    tft.print(mTime.day(), DEC);
    tft.println();
  }
}

// ----------------------------------------------------------------------------
void VirtualLock::drawState(Adafruit_ILI9341& tft, int16_t _x, int16_t _y)
{
  tft.fillRect(_x, _y, 20, 20, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setCursor(_x, _y);
  tft.setTextColor(mOpen ? ILI9341_GREEN : ILI9341_RED); 
  tft.print(mOpen ? "O" : "X");
}

// ----------------------------------------------------------------------------
bool VirtualLock::unlock(const char* answerTry, const DateTime& time)
{
  uint32_t normalizedNow = time.month()*100+time.day();  
  uint32_t normalizedTime = mTime.month()*100+mTime.day();
  if (normalizedNow >= normalizedTime) {
    if (NULL != answerTry && !strcmp(answerTry, mAnswer)) {
      mOpen = true;
    }
    return mOpen;
  }
  return false;
}
// ----------------------------------------------------------------------------


