#include <SoftwareSerial.h>

#define DEBUG true
#define TX_PIN 7
#define RX_PIN 8
#define FETCH_DELAY 20000

char phone_no[] = "";  // INSERT PHONE NUMBER
String data[6];
String state, timegps, latitude, longitude, altitude;
SoftwareSerial sim808(TX_PIN, RX_PIN);

void setup() {
  sim808.begin(19200);
  Serial.begin(19200);
  delay(50);
  sim808.print("AT+CMGF=1\r");
  delay(400);
  sendData("AT+CGNSPWR=1", 1000, DEBUG);
  delay(50);
}

void loop() {
  sendData("AT+CGNSSEQ=RMC", 1000, DEBUG);
  delay(150);
  parseData("AT+CGNSINF", 1000, DEBUG);

  if (state != 0) {
    printData();
    sendSMS();
    resetData();
  }
  else
    Serial.println("GPS Initialising...");
}

String sendData (String command , const int timeout , boolean debug) {
  String response = "";
  long int time = millis();
  int i = 0;

  sim808.println(command);
  while ((time + timeout) > millis()) {
    while (sim808.available()) {
      char c = sim808.read();
      response += c;
    }
  }
  if (debug)
    Serial.print(response);
  return response;
}

void parseData(String command, const int timeout , boolean debug) {
  long int time = millis();
  int i = 0;
  int bytes = 0;

  sim808.println(command);
  while ((time + timeout) > millis()) {
    while ((bytes = sim808.available())) {
      char c = sim808.read();
      Serial.print(c);
      if (c != ',') {
        data[i] += c;

      }
      else
        i++;
      if (i == 6)
        goto exitL;
    }
  }
exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude = data[4];
    altitude = data[5];
  }
}

void printData() {
  Serial.println("State  :" + state);
  Serial.println("Time  :" + timegps);
  Serial.println("Latitude  :" + latitude);
  Serial.println("Longitude  :" + longitude);
  Serial.println("Altitude  :" + altitude);
}

void resetData() {
  // reset array
  for (int j = 0; j < sizeof(data) / sizeof(data[0]); j++)
    data[j] = "\0";
}

void sendSMS() {
  sim808.print("AT+CMGS=\"");
  sim808.print(phone_no);
  sim808.println("\"");
  sim808.print("http://maps.google.com/maps?q=");
  delay(300);
  sim808.print(latitude);
  sim808.print(",");
  sim808.print (longitude);
  sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
  sim808.flush();
  delay(FETCH_DELAY);
  Serial.println("Done");
}



