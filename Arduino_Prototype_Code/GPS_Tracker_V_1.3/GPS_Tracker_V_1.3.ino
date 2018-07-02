#include <SoftwareSerial.h>
SoftwareSerial sim808(7,8);

char phone_no[13] = "14083482622";
String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;

void setup() {
 sim808.begin(19200);
 Serial.begin(19200);
 delay(50);

 //sim808.print("AT+CSMP=17,167,0,0");  // set this parameter if empty SMS received
 delay(100);
 sim808.print("AT+CMGF=1\r"); 
 delay(400);
 Serial.println("CLEARSHEET");
 Serial.println("LABEL,Date,Time,State,Latitude,Longitude,");
 
}

void loop() {
  int x = 0;
  sendData("AT+CGNSPWR=1",1000,DEBUG);
  delay(50);
  sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
  delay(150);
  sendTabData("AT+CGNSINF",1000,DEBUG);
  if (state !=0) {
    Serial.print("DATA,DATE,");
    Serial.print(timegps);
    Serial.print(",");
    Serial.print(state);
    Serial.print(",");
    Serial.print(latitude);
    Serial.print(",");
    Serial.println(longitude);
    sim808.println();
    delay(200);
    for (int x = 0; x < sizeof(data) / sizeof(data[0]); x++)
       {
         data[x] = "\0";
      }
    sim808.flush();
  } else {
    Serial.println("0");
  }
}

void sendTabData(String command , const int timeout , boolean debug){

  sim808.println(command);
  long int time = millis();
  int i = 0;

  while((time+timeout) > millis()){
    while(sim808.available()){
      char c = sim808.read();
      if (c != ',') {
         data[i] +=c;
         delay(100);
      } else {
        i++;  
      }
      if (i == 5) {
        delay(100);
        goto exitL;
      }
    }
  }exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude =data[4];  
  }
}
String sendData (String command , const int timeout ,boolean debug){
  String response = "";
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ( (time+timeout ) > millis()){
    while (sim808.available()){
      char c = sim808.read();
      response +=c;
    }
  }
  if (debug) {
     Serial.print(response);
     }
     return response;
}




