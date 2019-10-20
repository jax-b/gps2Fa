/*
  This sketch uses the GPS to determine the time
  and prints it to the Serial monitor.

  Circuit:
   - MKR board
   - MKR GPS attached via I2C cable

*/

#include <Arduino_MKRGPS.h>
#include <time.h>

time_t rawtime = 1262304000;
struct tm  ts;
char       buf[80];

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // If you are using the MKR GPS as shield, change the next line to pass
  // the GPS_MODE_SHIELD parameter to the GPS.begin(...)
  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
}

void loop() {
  // check if there is new GPS data available
  Serial.print("delay ");
  for (int i = 0; i < 10; i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  rawtime = getGPSTime();
  Serial.print("GPS Time: ");
  Serial.println(getGPSTime());

  ts = *localtime(&rawtime);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %I:%M:%S %P %Z", &ts);
  Serial.print(buf);
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
