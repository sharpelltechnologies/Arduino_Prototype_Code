#include <SoftwareSerial.h>

SoftwareSerial GPRS(7, 8);         //7 = TX, 8 = RX
unsigned char buffer[64];
int count=0;     
int i = 1;                         //if i = 0, send SMS.
void setup(){
  //delay(10000);
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  Serial.print("I'm ready\n");
  Serial.print("Hello?\n"); 
  sendSMS();
}

void loop(){

}

void sendSMS(){         // if data is available on hardwareserial port ==> data is comming from PC or notebook      // write it to the GPRS shield
    GPRS.print("AT+CMGF=1\r\n"); //sending SMS in text mode
    Serial.println("AT+CMGF=1\r\n"); 
    delay(1000);
    GPRS.print("AT+CMGS=\"+14083482622\"\r\n"); // phone number
    Serial.println("AT+CMGS=\"+14083482622\"\r"); 
    delay(1000);
    GPRS.print("Message from Arduino: Did it work?\r"); // message
    Serial.println("Message from Arduino: Did it work?\r"); 
    delay(1000);
    GPRS.write(0x1A); //send a Ctrl+Z(end of the message)
    delay(1000);
    Serial.println("SMS sent successfully");  
}

