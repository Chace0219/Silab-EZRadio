#include <SPI.h>
#include <MFRC522.h>
#include <TinyGPS++/TinyGPS++.h>
#include <ParticleSoftSerial.h>
#include "FBD.h"
#include "FSM.h"
#include "PIRSensor.h"
#include "DFRobotDFPlayerMini.h"
#include "neopixel.h"

#include "RH_RF24.h"


const uint8_t MCUSOUND = DAC;
const uint8_t RADIOCS = A2;
const uint8_t RADIOIRQ = A1;
const uint8_t PIRPIN = A0;
const uint8_t RFID_CS = D4;
const uint8_t RFID_RST = D3;
const uint8_t CS_AMP = D2;

const uint8_t RFINPUT = D3;

const char debugEvent[] = "debug";
/*  C
const uint8_t BUTTONPIN1 = C3;
const uint8_t BUTTONPIN2 = C2;
const uint8_t DISPLAY_RX = C1;
const uint8_t DISPLAY_TX = C0;
*/

// MFRC522 mfrc522(RFID_CS, RFID_RST);   // Create MFRC522 instance.

const uint8_t PIXEL_COUNT = 100;
const uint8_t LEDPIN = D7;
#define PIXEL_TYPE WS2812B

const uint8_t GPS_RXD = D5;
const uint8_t GPS_TXD = D4;
const uint32_t GPSBaud = 4800;
#define PROTOCOL SERIAL_8N1

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
ParticleSoftSerial gpsSerial(GPS_RXD, GPS_TXD);

PIRSensor pirMotion(PIRPIN);
DFRobotDFPlayerMini myDFPlayer;
Adafruit_NeoPixel strip(PIXEL_COUNT, LEDPIN, PIXEL_TYPE);

// Singleton instance of the radio driver
RH_RF24 rf24(A2, A1);

//
TON rfInputTON(100);
Rtrg rfInputTrg;

//

void setup() {
  pinMode(CS_AMP, OUTPUT);
  strip.begin();
  strip.show();

  gpsSerial.begin(GPSBaud, PROTOCOL);
  Serial1.begin(9600);
  if (!myDFPlayer.begin(Serial1))
  {
    Particle.publish(debugEvent, "Unable to begin DFPlayer");
    Particle.publish(debugEvent, "1.Please recheck the connection!");
    Particle.publish(debugEvent, "2.Please insert the SD card!");

    /*
    while(true){
      delay(100);
    }
    // */
  }
  delay(1000);

  Serial.begin(115200);
  Serial.println(F("Program started"));
  delay(1000);
  if (!rf24.init())
    Serial.println(F("rf init failed"));
  else
    Serial.println(F("rf init success"));

  //
  pinMode(RFINPUT, INPUT);
}

//
int pos = 0, dir = 1;
bool animating = false;
bool blinkStatus = false;
static const int32_t segmentCnt = 33;

TON bootTON(3000);
void loop() {

  static uint32_t lastAnimatingTime = millis();

  //
  bootTON.IN = true;
  bootTON.update();

  rfInputTON.IN = digitalRead(RFINPUT) == LOW;
  rfInputTON.update();
  rfInputTrg.IN = rfInputTON.Q;
  rfInputTrg.update();

  if(rfInputTrg.Q && bootTON.Q)
  {
    Particle.publish(debugEvent, "rf interrupt has triggered, sound will be playing");
    //

    digitalWrite(CS_AMP, LOW);
    myDFPlayer.volume(30);  //Set volume value. From 0 to 30
    myDFPlayer.play(1);  //Play the first mp3

    //
    animating = true;
    lastAnimatingTime = millis();
    pos = 0;
    dir = 1;
  }

  static uint32_t lastNeoPixelTime = millis();

  if(millis() - lastAnimatingTime > 10000 && animating)
  {
    animating = false;
  }

  if(millis() - lastNeoPixelTime > 30)
  {
    if(animating)
    {

      if(blinkStatus)
      {
        blinkStatus = false;
        for(uint8_t idx = 0; idx < strip.numPixels(); idx++)
          strip.setPixelColor(idx, strip.Color(0x00, 0x00, 0x00));
      }
      else
      {
        for(uint8_t idx = 0; idx < strip.numPixels(); idx++)
          strip.setPixelColor(idx, strip.Color(0xFF, 0x00, 0x00));
        blinkStatus = true;
      }


      /*
      int j;
      for(j = -(segmentCnt / 2); j <= segmentCnt / 2; j++)
        strip.setPixelColor(pos + j, 0);
      pos += dir;
      if(pos < 0)
      {
        pos = segmentCnt / 2;
        dir = -dir;
      }
      else if(pos >= 100)
      {
        pos = strip.numPixels() - segmentCnt / 2;
        dir = -dir;
      }

      for(j = -(segmentCnt / 2); j <= segmentCnt / 2; j++)
        strip.setPixelColor(pos + j, strip.Color(0xFF, 0x00, 0x00));

      strip.setPixelColor(pos - segmentCnt / 2, strip.Color(0x10, 0x00, 0x00));
      strip.setPixelColor((pos - segmentCnt / 2) + 1, strip.Color(0x7F, 0x00, 0x00));
      strip.setPixelColor((pos + segmentCnt / 2) - 1, strip.Color(0x7F, 0x00, 0x00));
      strip.setPixelColor(pos + segmentCnt / 2, strip.Color(0x10, 0x00, 0x00));
      */
    }
    else
    {
      for(uint8_t idx = 0; idx < strip.numPixels(); idx++)
        strip.setPixelColor(idx, 0);
    }
    strip.show();
    lastNeoPixelTime = millis();
  }

}
