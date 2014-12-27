Chronobox.arduino
=================

Arduino code based on specific hardware. This includes a somewhat generic code for a virtual keyboard (on screen).

Concept
-------

The box is lock from the inside and will only open between two dates.
In between the "opening" dates the screen displays riddles that have to be solved in order to open the box. The riddles can be set to show at a certain date.
When the last riddles is answered a servo unlock the box.

Hardware
--------

The box was hand made. 
For the electronics :
  - 2.8" capacitive touch screen (from Adafruit http://www.adafruit.com/product/1651)
  - RTC chipset (from Adafruit http://www.adafruit.com/products/255)
  - Servo motor
  - Arduino Uno (http://arduino.cc/en/Main/arduinoBoardUno)
  
Software
--------

The code has been cleaned from the actually deployed (and working) version but it is still very peculiar to my cases.
That said, the virtual keyboard and riddle system can be reused. And the hardware-specific code is small enough to be replaced if need be

Licence
-------

MIT Licence, do whatever you want with it.
