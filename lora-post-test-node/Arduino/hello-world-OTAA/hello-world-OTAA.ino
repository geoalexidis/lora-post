#include "TheThingsUno.h"

// Set your AppEUI and AppKey
const byte appEui[8] = {0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1B, 0x0D, 0x56}; //for example: {0x70, 0xB3, 0xD5, 0x7E, 0xE0, 0xE0, 0x01, 0x4A1};
const byte appKey[16] = {0x82, 0x48, 0xF9, 0x86, 0xAC, 0xE0, 0xAE, 0x62, 0x94, 0x26, 0xC6, 0x7B, 0xF4, 0x12, 0xAA, 0xDF}; //for example: {0x73, 0x6D, 0x24, 0xD2, 0x69, 0xBE, 0xE3, 0xAE, 0x0E, 0xCE, 0xF0, 0xBB, 0x6C, 0xA4, 0xBA, 0xFE};

#define debugSerial Serial
#define loraSerial Serial1

#define debugPrintLn(...) { if (debugSerial) debugSerial.println(__VA_ARGS__); }
#define debugPrint(...) { if (debugSerial) debugSerial.print(__VA_ARGS__); }

TheThingsUno ttu;

void setup()
{
  debugSerial.begin(115200);
  loraSerial.begin(57600);

  delay(1000);
  ttu.init(loraSerial, debugSerial);
  ttu.reset();
  ttu.join(appEui, appKey);

  delay(1000);
  ttu.showStatus();
  debugPrintLn("Setup for The Things Network complete");

  delay(1000);
}

void loop() {
  ttu.sendString("Hello world!");

  delay(2000);
}
