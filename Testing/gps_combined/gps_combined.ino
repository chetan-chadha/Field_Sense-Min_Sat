// Test code for Adafruit Flora GPS modules
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Flora GPS module
// ------> http://adafruit.com/products/1059
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada
unsigned int count=0;
#include <Wire.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <LSM6.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);

// If using hardware serial (e.g. Arduino Mega), comment out the
// above SoftwareSerial line, and enable this line instead
// (you can change the Serial number to match your wiring):

//HardwareSerial mySerial = Serial1;


Adafruit_GPS GPS(&mySerial);
     
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false
     
// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
LSM6 imu;
LPS ps;
LIS3MDL mag;
char report[120];   
void setup()
{
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(9600);
  //Serial.println("Adafruit GPS library basic test!");
     
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
     
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);
  Serial.println(PMTK_Q_RELEASE);
  Serial.begin(9600);
  Wire.begin();
  int i=1;
  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }
  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
  mag.enableDefault();
  ps.enableDefault(); 
  delay(1000);
  // Ask for firmware version
 Serial.println(PMTK_Q_RELEASE);
}
     
     
     
uint32_t timer = millis();
void loop() // run over and over again
{
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
 // if (GPSECHO)
   // if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
   Serial.println("hello"); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis()) timer = millis();
     
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
     Serial.println("hello2");
    timer = millis(); // reset the timer
   // Serial.print("\nTime: ");
   // Serial.print(GPS.hour, DEC); Serial.print(':');
   // Serial.print(GPS.minute, DEC); Serial.print(':');
   // Serial.print(GPS.seconds, DEC); Serial.print('.');
   // Serial.println(GPS.milliseconds);
   // Serial.print("Date: ");
    //Serial.print(GPS.day, DEC); Serial.print('/');
    //Serial.print(GPS.month, DEC); Serial.print("/20");
   // Serial.println(GPS.year, DEC);
    //Serial.print("Fix: "); Serial.print((int)GPS.fix);
    ///Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
       Serial.println("hello3");
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.print(GPS.lon);
      Serial.print("Speed (knots): "); Serial.print(GPS.speed);
      //Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.print(GPS.altitude);
      Serial.print("Satellites: "); Serial.print((int)GPS.satellites);
      Serial.write(', ');
    }
  }
  imu.read();
   int i;
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  snprintf(report, sizeof(report), "%6d,%6d,%6d",
    imu.a.x, imu.a.y, imu.a.z);
      tmElements_t tm;
//  Serial.print("1644");
//  Serial.print(",");
//    if (RTC.read(tm)) {
//    //Serial.print("Ok, Time = ");
//    print2digits(tm.Hour);
//    Serial.write(':');
//    print2digits(tm.Minute);
//    Serial.write(':');
//    print2digits(tm.Second);
//
//  }
//   else {
//    if (RTC.chipPresent()) {
//     // Serial.println("The DS1307 is stopped.  Please run the SetTime");
//     // Serial.println("example to initialize the time and begin running.");
//      Serial.println();
//    } else {
//     // Serial.println("DS1307 read error!  Please check the circuitry.");
//      Serial.println();
//    }
//    delay(9000);
//  }
//  Serial.print(",");
//  count++;
//  Serial.print(count);
//  Serial.print(",");
//  Serial.print(altitude);
//  Serial.print(",");
//  Serial.print(pressure);
//  Serial.print(",");
//  Serial.print(temperature);
//  Serial.print(",");
//  Serial.print("5");
//  int xAccl=imu.a.x;
//int yAccl=imu.a.y;
//int zAccl=imu.a.z;
//float angleX = atan2(xAccl,(sqrt(pow(yAccl,2)+pow(zAccl,2))))*(180/PI);
//float angleY = atan2(yAccl,(sqrt(pow(xAccl,2)+pow(zAccl,2))))*(180/PI);
//float angleZ = atan2((sqrt(pow(xAccl,2)+pow(yAccl,2))),zAccl)*(180/PI);
// Serial.print(",");
// Serial.print(angleX);
// Serial.print(",");
// Serial.print(angleY);
// Serial.print(",");
// Serial.print(angleZ);
// Serial.println();
  delay(1000);
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
