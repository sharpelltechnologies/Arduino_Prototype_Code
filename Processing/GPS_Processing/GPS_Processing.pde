/* This a messy Processing file reads gps data directly from the serial port 
 * on an Arduino runiong 'GPS_Tracker'. Data is parsed and added to a CSV file where each line 
 * represents a single oberservation of data. 
 * 
 * Usage: 
 * 1. Create/locate 'data' folder inside of 'GPS_Processing'
 * 2. Set the port number to read data from serial (see below)
 * 3. Run 'GPS_Tracker'; do NOT open the serial monitor on the Arduino IDE
 * 4. Run 'GPS_Processing'; sometimes you have to click play more than once
 * 
 * NOTE: files will be saved to `~/Processing/GPS_Processing/data/`
 *
 * Created by Tanner Larson.
 */ 

import processing.serial.*; 

Serial port; 
Table gpsTable;
int numReadings = 1;    // Number of readings/observations before a new csv file is created
int readingCount = 0;   // Total number of readings
String fileName;    

void setup() {
  String portName = Serial.list()[7]; // SET correct port number to read data from serial
  //printArray(Serial.list());        // use this to print all ports
  port = new Serial(this, portName, 19200); 
  gpsTable = new Table(); 
  
  gpsTable.addColumn("id"); 
  gpsTable.addColumn("year");
  gpsTable.addColumn("month");
  gpsTable.addColumn("day");
  gpsTable.addColumn("hour");
  gpsTable.addColumn("min");
  gpsTable.addColumn("sec");
  gpsTable.addColumn("latitude");
  gpsTable.addColumn("longitude");
  gpsTable.addColumn("altitude");
}

void serialEvent(Serial myPort) {
  String output = myPort.readStringUntil('\n'); 
  if (output != null) {
    println(output); 
    // Parse
    output = trim(output);    
    String values[] = split(output, ','); 
    String year = values[0].substring(0, 4); 
    String month = values[0].substring(4, 6); 
    String day = values[0].substring(6, 8); 
    String hour = values[0].substring(8, 10); 
    String min = values[0].substring(10, 12); 
    String sec = values[0].substring(12, 14); 
    
    // Add row
    TableRow newRow = gpsTable.addRow(); 
    newRow.setInt("id", gpsTable.lastRowIndex());
    newRow.setInt("year", int(year)); 
    newRow.setInt("month", int(month)); 
    newRow.setInt("day", int(day)); 
    newRow.setInt("hour", int(hour)); 
    newRow.setInt("min", int(min)); 
    newRow.setInt("sec", int(sec));     
    newRow.setFloat("latitude", float(values[1])); 
    newRow.setFloat("longitude", float(values[2])); 
    newRow.setFloat("altitude", float(values[3])); 

    // Create file
    readingCount++; 
    if (readingCount % numReadings  == 0) {
      fileName = "./data/" + year + month + day + str(gpsTable.lastRowIndex()) + ".csv"; 
      saveTable(gpsTable, fileName);
    }
  }
}

void draw()
{
  // TODO: add visualization here
  //       removing this function will break serialEvent()
  
}
