#include <SoftwareSerial.h>

SoftwareSerial SIM808(7,8);
int i = 0;
char inData[50];
String myString = "";
char phone_number[13];
void setup() {
  Serial.begin(19200); // for serial monitor
  SIM808.begin(19200); // for SIM808 shield
  SIM808.println("AT\r");
  SIM808.println("AT+CLIP=1\r");
  SIM808.flush();
}

void loop() {
  while(SIM808.available()>=50 && myString.length() < 38) {
   readline(SIM808.read(), inData);
   if(myString.length() >= 38) {
      SIM808.println("ATH\r");
      for(i = 27; i < 38; i++) {
         phone_number[i-27] = inData[i];
      }
      Serial.println(phone_number);
      delay(1000);
      break;
      
   }
  }
  
}
int readline(int readch, char *buffer) {
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
