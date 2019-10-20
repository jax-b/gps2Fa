#include "sha1.h"
#include "TOTP.h"
#include <Arduino_MKRGPS.h>

// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72};

TOTP totp = TOTP(hmacKey, 6);
char code[7];


void setup() {
  
  Serial.begin(9600);
  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
}

void loop() {
  Serial.print("delay ");
  for (int i = 0; i < 10; i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  long GMT = getGPSTime();
  char* newCode = totp.getCode(GMT);
  if(strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.println(code);
  }  
}
float getGPSTime() {
  //Serial.println("Wakey Wakey");
  GPS.wakeup();
  while (!GPS.available());
  float gpstime = GPS.getTime(); 
  //Serial.println("Bedy by BEEP");
  GPS.standby();
  return gpstime;
}
