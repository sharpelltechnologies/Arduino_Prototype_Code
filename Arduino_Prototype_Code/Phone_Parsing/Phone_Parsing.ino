#include <SoftwareSerial.h>

SoftwareSerial SIM808(7,8);
int i = 0;
char inData[50];
String myString = "";
char phone_number[13];
void setup() {
  Serial.begin(19200); // for serial monitor
  SIM808.begin(19200); // for SIM808 shield
}

void loop() {
  while(SIM808.available()>=50) {
   readline(SIM808.read(), inData, 50);
   if(myString.length() >= 24) {
      for(i = 12; i < 23; i++) {
         phone_number[i-12] = inData[i];
      }
      Serial.println(phone_number);
      delay(1000);
      break;
      
   }
  }
  
}
int readline(int readch, char *buffer, int len) {
  static int pos = 0;
  int rpos;
  if(SIM808.available() > 0) {
    if (readch > 0) {
     switch (readch) {
      case '\r': // Ignore CR
        break;
      case '\n': // Return on new-line
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
         buffer[i++] = readch;
         myString+= buffer[i-1];
    }
  }
  else {
    Serial.println("No read");
  }
}
}
