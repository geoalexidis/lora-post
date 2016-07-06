#include "TheThingsUno.h"
#include <SoftwareSerial.h>

// Set your DevAddr
const byte devAddr[4] = {0x01, 0x61, 0xB5, 0xFB}; //for example: {0x02, 0xDE, 0xAE, 0x00};
String inString = "";


// Set your NwkSKey and AppSKey
const byte nwkSKey[16] = {0x05, 0xED, 0x38, 0x5B, 0xF7, 0x83, 0xAA, 0x99, 0x98, 0x99, 0x29, 0xCA, 0xD7, 0x51, 0xA7, 0xF6}; //for example: {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
const byte appSKey[16] = {0x20, 0x49, 0x5A, 0x2B, 0x18, 0xD4, 0xDB, 0x74, 0x20, 0x85, 0xFA, 0x4F, 0xA9, 0x7F, 0xB8, 0x60}; //for example: {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

#define debugSerial Serial
#define loraSerial Serial1

#define debugPrintLn(...) { if (debugSerial) debugSerial.println(__VA_ARGS__); }
#define debugPrint(...) { if (debugSerial) debugSerial.print(__VA_ARGS__); }

TheThingsUno ttu;

void setup()
{
  debugSerial.begin(115200);
  loraSerial.begin(57600);

  delay(3000);

  ttu.init(loraSerial, debugSerial);
  ttu.reset();
  ttu.personalize(devAddr, nwkSKey, appSKey);
  ttu.showStatus();

  debugPrintLn("Setup for The Things Network complete");

  delay(2000);
}

void loop() {
  inString = Serial.readString();

  //____Split The String____

  
  String temp1 = inString.substring(inString.indexOf(',') + 1); // ,y,x
  String testnr = inString.substring(0, inString.indexOf(',')); //x

  String temp2 = temp1.substring(temp1.indexOf(',') + 1); //x
  String counter = temp1.substring(0, temp1.indexOf(',')); //Testnummer :12 Temp1 : 34, 56   Counter :34  Temp2 : 56   Scenario : 56

  String scenario = temp2.substring(0, temp2.indexOf(',')); // Security if more then one clcick on the GUI

// ____Setting the SF____
 int dr = -1;
  switch (scenario.toInt()) {
    case 7:
      dr = 5;
      break;
    case 8:
      dr = 4;
      break;
    case 9:
      dr = 3;
      break;
    case 10:
      dr = 2;
      break;
    case 11:
      dr = 1;
      break;
    case 12:
      dr = 0;
      break;
    default:
      debugPrintLn("Waiting for command");
      break;
  }
  if (dr > -1)
  { ttu.sendCommand("mac set dr " + String(dr)); 
  }
  

  if(inString != "")
  {
    // ____Seting the  Retry on____ 
    ttu.sendCommand("mac set retx 0");
    
    // ____Setting  the Counter from the device____
  
     ttu.sendCommand("mac set upctr " + String(counter) );
  
    // ____Setting Test number for Protocol Still outcomment____
    
    //ttu.sendCommand("mac tx cnf 4 " + testnr ); 
   
    ttu.sendString(testnr);
    inString = ""; 
  }
  delay(2000);
}
