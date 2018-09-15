#include <Wire.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <LSM6.h>
#include <Time.h>
#include <DS1307RTC.h>
unsigned int count=0;
LSM6 imu;
LPS ps;
LIS3MDL mag;
char report[120];
void setup() {
 Serial.begin(9600);
  Wire.begin();
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
}
uint32_t timer = millis();
void loop() {
  imu.read();
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  snprintf(report, sizeof(report), "%6d,%6d,%6d",
    imu.a.x, imu.a.y, imu.a.z);
      tmElements_t tm;
  Serial.print("1644");
  Serial.print(",");
    if (RTC.read(tm)) {
    //Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);

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
  count++;
  Serial.print(count);
  Serial.print(",");
  Serial.print(altitude);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print("5");
 Serial.print(",");
     if (RTC.read(tm)) {
    //Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);

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
        Serial.print(", ");
        Serial.print(lati);
      Serial.print(", "); 
      Serial.print(lon);
      Serial.print(", ");
      //////////////////////////
     // Serial.print("Location: "); 
       Serial.print(altitude);
       Serial.print(",");
       Serial.print("8");
int xAccl=imu.a.x;
int yAccl=imu.a.y;
int zAccl=imu.a.z;
float angleX = atan2(xAccl,(sqrt(pow(yAccl,2)+pow(zAccl,2))))*(180/PI);
float angleY = atan2(yAccl,(sqrt(pow(xAccl,2)+pow(zAccl,2))))*(180/PI);
float angleZ = atan2((sqrt(pow(xAccl,2)+pow(yAccl,2))),zAccl)*(180/PI);
 Serial.print(",");
 Serial.print(angleX);
 Serial.print(",");
 Serial.print(angleY);
 Serial.print(",");
 Serial.print(angleZ);
 Serial.println();
   }
  }
  delay(1000);
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
