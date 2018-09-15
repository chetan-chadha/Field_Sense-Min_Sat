#include <SoftwareSerial.h>    
#include <Adafruit_GPS.h>
//#include <SD.h> //Load SD card library
#include <Wire.h>
SoftwareSerial ss(3,2);

// what's the name of the hardware serial port?
#define GPSSerial ss
//chipSelect pin for the SD card Reader
//File mySensorData; //Data object you will write your sesnor data to
// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);
     
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

uint32_t timer = millis();


void setup()
{
  //while (!Serial);  // uncomment to have the sketch wait until Serial is ready
  
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(9600);
  Serial.println("Adafruit GPS library basic test!");
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  pinMode(10, OUTPUT); //Must declare 10 an output and reserve it
//  SD.begin(10); //Initialize the SD card reader
  delay(1000);
  
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
  Wire.begin(); 
}

void loop() // run over and over again
{
  String buf,buf1;
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
//    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis()) timer = millis();
     
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 1000) {
    timer = millis(); // reset the timer
    buf +=String(GPS.hour, DEC); 
//    buf +=String(':');
    buf +=String(GPS.minute, DEC); 
//    buf +=String(':');
    buf +=String(GPS.seconds, DEC);
    buf +=String(',');
    if (GPS.fix) {
//      mySensorData = SD.open("test.txt", FILE_WRITE);
      
//      Serial.print("hello");
      buf +=String(GPS.latitude, 2);
      buf +=String(GPS.lat);
      buf +=String(",");
      buf +=String(GPS.longitude, 2); buf +=String(GPS.lon);
      buf +=String(",");buf +=String(GPS.altitude, 0);
      buf +=String(",");buf +=String((int)GPS.satellites);
      
//      mySensorData.print(GPS.lat);                             //write temperature data to card
//      mySensorData.print(",");                               //write a commma
//      mySensorData.println(GPS.lon);                        //write pressure and end the line (println)
//      mySensorData.close();                                  //close the file
//

    }
    Wire.beginTransmission(4);// transmit to device #9
    Wire.write(buf.c_str());
    Wire.endTransmission();
    Serial.println(buf.c_str());
    delay(10);
//    Wire.endTransmission();// stop transmittin
  }
  
}
