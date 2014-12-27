// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// DrawHelpers.h
//  Helping function to draw some controls on screen.
//---------------------------------------------------------

#ifndef _DRAW_HELPERS_H_
#define _DRAW_HELPERS_H_

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Driver display

namespace DrawHelpers 
{
  void answerBox(Adafruit_ILI9341& tft, const char* text, int16_t _x, int16_t _y, int16_t _w, int16_t _h) {
    tft.fillRect(_x, _y, _w, _h, ILI9341_BLACK);
    tft.drawRoundRect(_x, _y, _w, _h, 1, ILI9341_WHITE);
    tft.setTextSize(1);
    tft.setCursor(_x+5, _y+_h-15);
    tft.print(text);
  }
}; // namespace DrawHelpers

#endif //_DRAW_HELPERS_H_

