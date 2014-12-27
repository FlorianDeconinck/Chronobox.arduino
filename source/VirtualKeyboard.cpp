// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// VirtualKeyboard.cpp
//  See .h
// ----------------------------------------------------------------------------
#include "VirtualKeyboard.h"
// ----------------------------------------------------------------------------
static const int16_t ButtonsSz = 28;
Button buttons[ButtonsSz] = {

Button (0,   180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "Q"),
Button (20,  180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "W"),
Button (40,  180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "E"),
Button (60,  180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "R"),
Button (80,  180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "T"),
Button (100, 180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "Y"),
Button (120, 180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "U"),
Button (140, 180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "I"),
Button (160, 180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "O"),
Button (180, 180, 20, 20, ILI9341_BLUE, ILI9341_GREY, "P"),

Button (0,   200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "A"),
Button (20,  200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "S"),
Button (40,  200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "D"),
Button (60,  200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "F"),
Button (80,  200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "G"),
Button (100, 200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "H"),
Button (120, 200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "J"),
Button (140, 200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "K"),
Button (160, 200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "L"),
Button (180, 200, 20, 20, ILI9341_BLUE, ILI9341_GREY, "<"),

Button (0,   220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "Z"),
Button (20,  220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "X"),
Button (40,  220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "C"),
Button (60,  220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "V"),
Button (80,  220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "B"),
Button (100, 220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "N"),
Button (120, 220, 20, 20, ILI9341_BLUE, ILI9341_GREY, "M"),
Button (140, 220, 60, 20, ILI9341_BLUE, ILI9341_GREY, "Enter")
};

enum VK_BUTTONS_INDEX {
  Q = 0,
  W,
  E,
  R,
  T,
  Y,
  U,
  I,
  O,
  P,
  
  A,
  S,
  D,
  F,
  G,
  H,
  J,
  K,
  L,
  DEL,
  
  Z,
  X,
  C,
  V,
  B,
  N,
  M,
  
  ENTER
};

// ----------------------------------------------------------------------------
VirtualKeyboard::VirtualKeyboard()
{
  clear();
}
// ----------------------------------------------------------------------------
bool VirtualKeyboard::clear()
{
  index = 0;
  for (int i = 0 ; i < BUFFER_MAX ; i++) {
    mBuffer[i] = '\0';	
  }
  mEnter = false;
}
// ----------------------------------------------------------------------------
bool VirtualKeyboard::update(int16_t _x, int16_t _y)
{
  _y += 10; //HACK : misconfig of touchscreen

  // Check size of buffer already in use
  if (index >= BUFFER_MAX) {
    return false;
  }
    
  if (buttons[Q].update(_x, _y)) { mBuffer[index++] = 'Q'; return true; }
  if (buttons[W].update(_x, _y)) { mBuffer[index++] = 'W'; return true; }
  if (buttons[E].update(_x, _y)) { mBuffer[index++] = 'E'; return true; }
  if (buttons[R].update(_x, _y)) { mBuffer[index++] = 'R'; return true; }
  if (buttons[T].update(_x, _y)) { mBuffer[index++] = 'T'; return true; }
  if (buttons[Y].update(_x, _y)) { mBuffer[index++] = 'Y'; return true; }
  if (buttons[U].update(_x, _y)) { mBuffer[index++] = 'U'; return true; }
  if (buttons[I].update(_x, _y)) { mBuffer[index++] = 'I'; return true; }
  if (buttons[O].update(_x, _y)) { mBuffer[index++] = 'O'; return true; }
  if (buttons[P].update(_x, _y)) { mBuffer[index++] = 'P'; return true; }

  if (buttons[A].update(_x, _y)) { mBuffer[index++] = 'A'; return true; }
  if (buttons[S].update(_x, _y)) { mBuffer[index++] = 'S'; return true; }
  if (buttons[D].update(_x, _y)) { mBuffer[index++] = 'D'; return true; }
  if (buttons[F].update(_x, _y)) { mBuffer[index++] = 'F'; return true; }
  if (buttons[G].update(_x, _y)) { mBuffer[index++] = 'G'; return true; }
  if (buttons[H].update(_x, _y)) { mBuffer[index++] = 'H'; return true; }
  if (buttons[J].update(_x, _y)) { mBuffer[index++] = 'J'; return true; }
  if (buttons[K].update(_x, _y)) { mBuffer[index++] = 'K'; return true; }
  if (buttons[L].update(_x, _y)) { mBuffer[index++] = 'L'; return true; }
  if (buttons[DEL].update(_x, _y)) { mBuffer[index-1] = '\0'; index = index < 0 ? 0 : index-- ; return true; }

  if (buttons[Z].update(_x, _y)) { mBuffer[index++] = 'Z'; return true; }
  if (buttons[X].update(_x, _y)) { mBuffer[index++] = 'X'; return true; }
  if (buttons[C].update(_x, _y)) { mBuffer[index++] = 'C'; return true; }
  if (buttons[V].update(_x, _y)) { mBuffer[index++] = 'V'; return true; }
  if (buttons[B].update(_x, _y)) { mBuffer[index++] = 'B'; return true; }
  if (buttons[N].update(_x, _y)) { mBuffer[index++] = 'N'; return true; }
  if (buttons[M].update(_x, _y)) { mBuffer[index++] = 'M'; return true; }
  if (buttons[ENTER].update(_x,_y)){ mEnter = true; return true; }
  
  return false;
}
// ----------------------------------------------------------------------------
void VirtualKeyboard::draw(Adafruit_ILI9341& tft)
{
    for (int16_t i = 0 ; i < ButtonsSz ; i++) {
      buttons[i].draw(tft);
    }
}
// ----------------------------------------------------------------------------
const char* VirtualKeyboard::read()
{
   return mBuffer;
}
// ----------------------------------------------------------------------------
bool VirtualKeyboard::enter() 
{
  if (mEnter) {
    mEnter = false;
    return true;
  }
  return false;
}
// ----------------------------------------------------------------------------
void VirtualKeyboard::endOfTouch()
{
    for (int16_t i = 0 ; i < ButtonsSz ; i++) {
      buttons[i].reset();
    }
}
// ----------------------------------------------------------------------------

