// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// Button.cpp
//  Simple library to display and use a two state button
// ----------------------------------------------------------------------------

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Driver display

#include <stdint.h>

typedef uint16_t colour;

class Button 
{
public:
	Button(int16_t x, int16_t y, int16_t w, int16_t h, colour colourOn, colour colourOffm, const char* text);
  
	bool/*state changed*/ update(int16_t x, int16_t y);
	void		      draw(Adafruit_ILI9341& tft);
        bool                  state() { return mState; }
        void                  reset() { mState = false; }

private:
	int16_t mX, mY, mW, mH;
	colour mColourOn;
	colour mColourOff;
	char mText[6]; // memory restricted. Overflow unchecked.
	bool mState; // two state
};

#endif //_BUTTON_H_
