// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// Button.cpp
//  See .h

//---------------------------------------------------------
#include "Button.h"
// ----------------------------------------------------------------------------
Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, colour colourOn, colour colourOff, const char* text) :
	mX(x),
	mY(y),
	mW(w),
	mH(h),
	mColourOn(colourOn),
	mColourOff(colourOff),
	mState(false)
{
  strcpy(mText, text);
}
// ----------------------------------------------------------------------------
bool/*state changed*/ Button::update(int16_t x, int16_t y)
{
  if (x >= mX && x < mX+mW &&
      y >= mY && y < mY+mH)
  {
    mState = true;
  }
  
  return mState;
}
// ----------------------------------------------------------------------------
void Button::draw(Adafruit_ILI9341& tft)
{
  //Serial.println("Button::draw");
  // Make the lock button
  tft.fillRect(mX, mY, mW, mH, mState ? mColourOn : mColourOff);
  tft.drawRect(mX, mY, mW, mH, ILI9341_WHITE); 
  // Text
  tft.setTextSize(1);
  if (mState) {
    tft.setCursor(mX + mW/2 - 5, mY + mH/2 - 5);
  } else {
    tft.setCursor(mX + mW/2 - 5, mY + mH/2 - 5);
  }
  tft.print(mText);
}
// ----------------------------------------------------------------------------
