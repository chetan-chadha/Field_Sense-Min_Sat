#include <Wire.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <LSM6.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SD.h>
File tempsFile;
//#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(3, 2);
unsigned int count=0;
float GPS_LAt=30.68;
float GPS_Long=76.66;
//Adafruit_GPS GPS(&mySerial);
//#define GPSECHO false
boolean usingInterrupt = false;
LSM6 imu;
LPS ps;
LIS3MDL mag;
char report[120];
void setup() {
 Serial.begin(9600);
  Wire.begin();
//  GPS.begin(9600);
//  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
//  GPS.sendCommand(PGCMD_ANTENNA);
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
    Serial.print("Initializing SD card...");
  if(!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
delay(1000);
//Serial.println(PMTK_Q_RELEASE);

}
uint32_t timer = millis();
void loop() {
  imu.read();
   int i;
   tempsFile = SD.open("test.txt", FILE_WRITE);
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  snprintf(report, sizeof(report), "%6d,%6d,%6d",
    imu.a.x, imu.a.y, imu.a.z);
      tmElements_t tm;

  Serial.print("1644");
  tempsFile.print("1644");
  Serial.print(",");
   tempsFile.print(",");
    if (RTC.read(tm)) {
    //Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    tempsFile.print(tm.Hour);
    Serial.print(':');
     tempsFile.print(":");
    print2digits(tm.Minute);
    tempsFile.print(tm.Minute);
    Serial.write(':');
     tempsFile.print(":");
    print2digits(tm.Second);
    tempsFile.print(tm.Second);
  }
    else {
    if (RTC.chipPresent()) {
     // Serial.println("The DS1307 is stopped.  Please run the SetTime");
     // Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
     // Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  Serial.print(",");
  tempsFile.print(",");
  count++;
  Serial.print(count);
   tempsFile.print(count);
  Serial.print(",");
  tempsFile.print(",");
  Serial.print(altitude);
  tempsFile.print(altitude);
  Serial.print(",");
  tempsFile.print(",");
  Serial.print(pressure);
  tempsFile.print(pressure);
  Serial.print(",");
  tempsFile.print(",");
  Serial.print(temperature);
  tempsFile.print(temperature);
  Serial.print(",");
  tempsFile.print(",");
  Serial.print("5");
  tempsFile.print("5");
 Serial.print(",");
 tempsFile.print(",");
if (RTC.read(tm)) {
    //Serial.print("Ok, Time = ");
print2digits(tm.Hour);
    tempsFile.print(tm.Hour);
    Serial.print(':');
    print2digits(tm.Minute);
    tempsFile.print(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    tempsFile.print(tm.Second);

  }
    else {
    if (RTC.chipPresent()) {
     // Serial.println("The DS1307 is stopped.  Please run the SetTime");
     // Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
     // Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
 Serial.print(",");
  tempsFile.print(",");
 Serial.print(GPS_LAt);
 tempsFile.print(GPS_LAt);
 Serial.print(",");
  tempsFile.print(",");
 Serial.print(GPS_Long);
  tempsFile.print(GPS_Long);
 Serial.print(",");
  tempsFile.print(",");
 Serial.print((altitude+30));
 tempsFile.print((altitude+30));
 Serial.print(",");
  tempsFile.print(",");
 Serial.print("8");
  tempsFile.print("8");
 Serial.print(",");
  tempsFile.print(",");
 
int xAccl=imu.a.x;
int yAccl=imu.a.y;
int zAccl=imu.a.z;
float angleX = atan2(xAccl,(sqrt(pow(yAccl,2)+pow(zAccl,2))))*(180/PI);
float angleY = atan2(yAccl,(sqrt(pow(xAccl,2)+pow(zAccl,2))))*(180/PI);
float angleZ = atan2((sqrt(pow(xAccl,2)+pow(yAccl,2))),zAccl)*(180/PI);
 Serial.print(angleX);
 tempsFile.print(angleX);
 Serial.print(",");
  tempsFile.print(",");
 Serial.print(angleY);
 tempsFile.print(angleY);
 Serial.print(",");
  tempsFile.print(",");
 Serial.print(angleZ);
 tempsFile.print(angleZ);
 Serial.print(",");
  tempsFile.print(",");
 if(count>50)
 {
 Serial.print("3");
 }
 else
 {
 Serial.print("2");
 }
  Serial.print(",0,1");
   tempsFile.print(",0,1");
   Serial.println(" ");
   tempsFile.println();
    tempsFile.close();
  delay(1000);
  
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
