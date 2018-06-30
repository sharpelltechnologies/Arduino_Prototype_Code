#include <SoftwareSerial.h>

SoftwareSerial SIM808(7,8);
int i = 0;
int j = 0;
char inData[50];
char phone_number[13];
void setup() {
  Serial.begin(19200); // for serial monitor
  SIM808.begin(19200); // for SIM808 shield
  SIM808.println("AT\r");
  SIM808.println("AT+CLIP=1\r");
}

void loop() {
  while(SIM808.available() >= 63) {
   readline(SIM808.read(), inData);
   if(inData[j-1] == '"') {
      for(i = 0; i < 13; i++) {
         phone_number[i] = inData[j-1];
         readline(SIM808.read(), inData);
      }
      Serial.println(phone_number);
      SIM808.println("ATH\r");
      SIM808.flush();
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
         buffer[j++] = readch;
         
    }
  }
  else {
    Serial.println("No read");
  }
}
}
