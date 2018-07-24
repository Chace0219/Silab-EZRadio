
#ifndef ADAFRUIT_NEOPIXEL_H
#define ADAFRUIT_NEOPIXEL_H

#include "Particle.h"

// 'type' flags for LED pixels (third parameter to constructor):
#define WS2811         0x00 // 400 KHz datastream (NeoPixel)
#define WS2812         0x02 // 800 KHz datastream (NeoPixel)
#define WS2812B        0x02 // 800 KHz datastream (NeoPixel)
#define WS2813         0x02 // 800 KHz datastream (NeoPixel)
#define TM1803         0x03 // 400 KHz datastream (Radio Shack Tri-Color Strip)
#define TM1829         0x04 // 800 KHz datastream ()
#define WS2812B2       0x05 // 800 KHz datastream (NeoPixel)
#define SK6812RGBW     0x06 // 800 KHz datastream (NeoPixel RGBW)
#define WS2812B_FAST   0x07 // 800 KHz datastream (NeoPixel)
#define WS2812B2_FAST  0x08 // 800 KHz datastream (NeoPixel)

class Adafruit_NeoPixel {

 public:

  // Constructor: number of LEDs, pin number, LED type
  Adafruit_NeoPixel(uint16_t n, uint8_t p=2, uint8_t t=WS2812B);
  ~Adafruit_NeoPixel();

  void
    begin(void),
    show(void) __attribute__((optimize("Ofast"))),
    setPin(uint8_t p),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w),
    setPixelColor(uint16_t n, uint32_t c),
    setBrightness(uint8_t),
    setColor(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue),
    setColor(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aWhite),
    setColorScaled(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aScaling),
    setColorScaled(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aWhite, byte aScaling),
    setColorDimmed(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aBrightness),
    setColorDimmed(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aWhite, byte aBrightness),
    updateLength(uint16_t n),
    clear(void);
  uint8_t
   *getPixels() const,
    getBrightness(void) const;
  uint16_t
    numPixels(void) const,
    getNumLeds(void) const;
  static uint32_t
    Color(uint8_t r, uint8_t g, uint8_t b),
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
  uint32_t
    getPixelColor(uint16_t n) const;
  byte
    brightnessToPWM(byte aBrightness);

 private:

  bool
    begun;         // true if begin() previously called
  uint16_t
    numLEDs,       // Number of RGB LEDs in strip
    numBytes;      // Size of 'pixels' buffer below
  const uint8_t
    type;          // Pixel type flag (400 vs 800 KHz)
  uint8_t
    pin,           // Output pin number
    brightness,
   *pixels;        // Holds LED color values (3 bytes each)
  uint32_t
    endTime;       // Latch timing reference
};

#endif // ADAFRUIT_NEOPIXEL_H
