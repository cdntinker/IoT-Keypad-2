/*
source from http://tech.scargill.net/mqtt-on-arduino/
Well...
That's where the ORIGINAL sketch came from...
I've kludged in a whole metric shitload of other shit.

Required Libraries:
  |-- <PubSubClient> 2.6      {#ID: 89}
  |-- <Ethernet> 1.1.2        {#ID: 872}
  |   |-- <SPI> 1.0           {#ID: }
  |-- <UIPEthernet> 2.0.6     {#ID: 1484}
  |   |-- <SPI> 1.0           {#ID: }
  |-- <Keypad> 3.1.1          {#ID: 165}
  PCD8544 {#ID: 428}
  FastLED {#ID: 126}
  ESPAsyncTCP {#ID: 305}
*/
#include <Arduino.h>

size_t freeRam();

#ifdef ArduinoUNO
#define EthW5100
#define KeyPadUNO
// #define Display1602
char ClientName[] = "unoClient";   // Must be unique
#endif

#ifdef ArduinoNano
#define EthENC28J60
#define KeyPadNano
char ClientName[] = "nanoClient";   // Must be unique
#endif

int sendit=0;
char msg[32]; //  Why in hell was this limited to 20 in the original?
              //  MQTT allows 268,435,456 bytes.
              //  hhhmmm... Apparently, Arduino has a limitation someplace below 100...
              //  AH HA!  higher numbers leave less free RAM dummy...
              //          & less free RAM (below about 180 bytes) means network fail
char Device[32];
char Speaker[32];
int SPK = 14;

#ifdef EthW5100
  #include <Ethernet.h>     // For Wiznet W5100
#endif
#ifdef EthENC28J60
  #include <UIPEthernet.h>  // For Microchip ENC28J60
#endif
#include <PubSubClient.h>

////////////////////////////////////////////
//  Setup Stuff
////////////////////////////////////////////
#include "Setup-Network.h"  // Do NOT forget to make mac address UNIQUE!
#include "Setup-Keypad.h"

#ifdef Display1602
  #include "Setup-Display-1602.h"
#endif

#include "Setup-Comm-MQTT.h"

#include "UI-input.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(F("+--------------------------+"));
  Serial.println(F("| Welcome to IoT Keypad 2  |"));
#ifdef ArduinoUNO
  Serial.println(F("| Running on an UNO        |"));
#endif
#ifdef ArduinoNano
  Serial.println(F("| Running on a Pro-Mini    |"));
#endif
  Serial.println(F("+--------------------------+"));
  Serial.print(F("Free RAM: ")); // If Free RAM is less than 180... it'll suck!
  Serial.println(freeRam());

  Ethernet.begin(mac);

  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());

  strcat(Topic_Out, ClientName);
  strcat(Topic_Out, "/Message");
  Serial.println(Topic_Out);

  // strcpy_P(Speaker, (char*)pgm_read_word(&(Topics_Device[SPK])));

  #ifdef Display1602
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.setCursor(6, 0);    lcd.print(Speaker);
    lcd.setCursor(0, 1);    lcd.print(F("Howdy, Universe!"));

    Serial.println(F("Display Initialized"));
  #endif
}

void loop()
{
  // this checks to see if you’re connected and connects
  // – will retry forever if need be.
  if (!client.connected())  {

    delay(1000);  // wait...for...it...
#ifndef SPACESAVING
    Serial.print(F("Connecting… "));
    Serial.print (client.connect(ClientName));
#endif
        if (client.connect(ClientName)) {
          client.publish(Topic_Out,"Hello world.");
        }

  client.subscribe("Arduino/In");

#ifndef SPACESAVING
  Serial.println(F(" Connected\n"));
#endif
  }

  client.loop();
  if (sendit) {
    sendit=0;
    #ifndef SPACESAVING
    Serial.println(F("Sending"));
    #endif
#ifdef Display1602
    lcd.setCursor(0, 0);    lcd.print(F("                "));
    lcd.setCursor(0, 0);    lcd.print(F("MQTT:"));
    lcd.setCursor(6, 0);    lcd.print(Speaker);
    lcd.setCursor(0, 1);    lcd.print(F("                "));
    lcd.setCursor(0, 1);    lcd.print(msg);
#endif
}
  KeyRead(); // see UI-input.h

}

// ------------------------------------------------------------------
// This is the routine that will display how much free SRAM you have.
// Ideally place in SETUP before the loop, but no hard rules.
//
// A "size_t" type can store the maximum size of any type. Commonly used for
// array indexing and loop counting. We could use an unsigned int here too.
// ------------------------------------------------------------------
size_t freeRam() {
	return RAMEND - size_t(__malloc_heap_start);
}
