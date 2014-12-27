// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// VirtualKeyboard.h
//  Display a virtual keyboard at the bottom of the screen. QWERTY + DEL + RETURN.
//  The keyboard buffers the touch signal, considering one signal = one touche. This makes the kerboard slow but it
//  is required when dealing with unresponsive cheap hardware.
//  Record BUFFER_MAX string inputs.
//---------------------------------------------------------
#ifndef _VIRTUAL_KEYBOARD_H_
#define _VIRTUAL_KEYBOARD_H_

#include "Button.h"

class VirtualKeyboard 
{
public:
	VirtualKeyboard();
  
        // Clear input 
	bool clear();
	bool update(int16_t x, int16_t y);
	void draw(Adafruit_ILI9341& tft);
	const char* read();
        bool enter();
        void endOfTouch();
private:
	static const uint16_t BUFFER_MAX = 16;
	char mBuffer[BUFFER_MAX];
        uint16_t index;
        bool mEnter;
};

#endif //_VIRTUAL_KEYBOARD_H_
