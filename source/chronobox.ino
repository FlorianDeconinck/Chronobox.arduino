// ---------------------------------------------------------
// Chronobox v1.0
// Florian Deconinck. 2014.
// Licensed under MIT.
// ---------------------------------------------------------
// Chronobox.ino
//  Entry point of the arduino board.
// ---------------------------------------------------------
// Screen lib
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Driver display
#include <Adafruit_STMPE610.h>// Driver touch
#include <SPI.h>              // Caching to RAM via SPI
#include <Wire.h>             // SPI dependancy
// RTC runtime lib
#include <RTClib.h>
// Servo control lib
#include <Servo.h> 
// Dev libraries
#include <MemoryFree.h>
// Helper libs
#include "Button.h"
#include "VirtualKeyboard.h"
#include "DrawHelpers.h"
#include "VirtualLocksHelper.h"
// ---------------------------------------------------------
// PINs and Global vars (ugly but fast and lightweight)

// SCREEN
// Calibration for screen coordinates
#define TS_MINX 180
#define TS_MINY 200
#define TS_MAXX 3900
#define TS_MAXY 3820

#define STMPE_CS 8 // The STMPE610STMPE610 uses hardware SPI on the shield, and #8
#define TFT_CS 10 // The display also uses hardware SPI, plus #9 & #10
#define TFT_DC 9

Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// SERVO
#define SERVO_IN 7 // Control pin
Servo servo;
int servoPos = 0;

// RTC
RTC_DS1307 rtc;

// Virtual Keyboard
VirtualKeyboard vk;

// Dates to lock
DateTime startTime(2014, 10, 22);
DateTime endTime(2014, 11, 19);

// ---------------------------------------------------------
// SETUP. Called once.
void setup(void) {
  // Serial debug port 
  Serial.begin(9600);

  // Screen setup.  
  tft.begin();

  while(true) {  // The touchscreen cqn be grumpy. Forcefull init.
    if (ts.begin()) {
      break;
    }
    Serial.println("Couldn't start touchscreen touch controller");
    delay(5);
  }
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1); // WARNING : Highly screen dependant
  Serial.println("Touchscreen started");

  // Servo setup.
  servo.attach(SERVO_IN);
  servo.write(0); //lock position

  // Chrono setup.
  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  // Time set : reset timer
  // rtc.adjust(DateTime(2014, 10,22, 19, 07, 0));

  // Virtual Locks
  VirtualLocksHelper::init();
}
// ---------------------------------------------------------
// LOCK
void unlock() {
   int angle = 40;
   for(; servoPos < angle; servoPos += 1)  
   {                                     
     servo.write(servoPos);              
     delay(20);                         
     Serial.println(servoPos);
   } 
}
// ---------------------------------------------------------

// ---------------------------------------------------------
// DEBUG PRINTs
void debugPrintTime()
{
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
// ---------------------------------------------------------

// ---------------------------------------------------------
// Touchscreen helper
bool mPressEvent = false;

TS_Point remap(Adafruit_STMPE610& ts)
{
  TS_Point p = ts.getPoint();
  if (p.z < 10 | ts.bufferEmpty()) {
    p.x = p.y = p.z = -1;
    mPressEvent = false;
    return p;
  }

  if (!mPressEvent) {
    mPressEvent = true;
    TS_Point raw_p = p;
    p.x = map(raw_p.y, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(TS_MAXY - raw_p.x, TS_MINY, TS_MAXY, 0, tft.height());
  } 
  else {
    p.x = p.y = p.z = -1;
    if (ts.bufferEmpty()) {
      mPressEvent = false;
    }
  }

  return p;
}
// ---------------------------------------------------------

// ---------------------------------------------------------
// DRAW.
// Run time display states
bool refreshDisplay = true;
bool refreshRiddle = true;
int lastSecond = 0; // draw time every second 

void drawTime() {
  DateTime now = rtc.now();
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(1);
  if (now.second() != lastSecond) {
    tft.fillRect(0, 10, tft.width(), 10, ILI9341_BLACK);
    lastSecond = now.second();
  } 
  tft.setCursor(0, 10);
  tft.print(now.year(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.print(now.day(), DEC);
  tft.print(' ');
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);
  tft.print(':');
  tft.print(now.second(), DEC);
  tft.println();
}

bool drawBckgdn = false;
void draw()
{
  tft.setCursor(0, 10);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(1);
  // Background fill
  if (drawBckgdn) {
    Serial.println("Draw background");  
    drawBckgdn = false;
    tft.fillScreen(ILI9341_BLACK);
  }
  if (refreshDisplay) {
    // Virtual keyboard
    vk.draw(tft);
    // Answer buffer
    const char* text = vk.read();
    DrawHelpers::answerBox(tft, text, 0, 160, 200, 20);
    // Kill multi refresh
    refreshDisplay = false;
  }
  
  if (refreshRiddle) {
    VirtualLocksHelper::drawLocksText(tft, 0, 40, rtc.now());
    VirtualLocksHelper::drawLocksState(tft, 240, 180);
    refreshRiddle = false;
  }
}

// ---------------------------------------------------------
boolean withinTimeFrame() {
  DateTime now = rtc.now();
  uint32_t normalizedNow = now.month()*100+now.day();  
  uint32_t normalizedStartTime = startTime.month()*100+startTime.day();
  uint32_t normalizedEndTime = endTime.month()*100+endTime.day();
  return normalizedNow >= normalizedStartTime && normalizedNow <= normalizedEndTime;
}

// ---------------------------------------------------------
// LOOP. Run until death.
int loopTick = 0;
int touchTick = 0;
void loop()
{
   // Time
  drawTime();
  if (!withinTimeFrame()) {
    tft.setCursor(0, 80);
    tft.print("Tic ? tac... ");
    tft.print(startTime.month(), DEC);
    tft.print('/');
    tft.print(startTime.day(), DEC);
    tft.print(" -- ");
    tft.print(endTime.month(), DEC);
    tft.print('/');
    tft.print(endTime.day(), DEC);
    return;
  }
  
  //Serial.print("freeMemory()=");
  //Serial.println(freeMemory());
  loopTick++;  
  draw();

  // Retrieve a point  
  TS_Point p = remap(ts);
  if (p.z < 10) {
    refreshDisplay = loopTick == touchTick+1;
    vk.endOfTouch();
    return;
  } 
  
  touchTick = loopTick;  
  refreshDisplay = vk.update(p.x, p.y);
  if (vk.enter()) {
    refreshRiddle = VirtualLocksHelper::update(vk.read(), rtc.now());
    vk.clear();
  }
  
  if (VirtualLocksHelper::activeLock >= VirtualLocksHelper::LOCK_SZ) {
    unlock();
  }
  
}

