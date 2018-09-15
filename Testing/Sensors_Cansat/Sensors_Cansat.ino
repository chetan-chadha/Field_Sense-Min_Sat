#include <Wire.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <LSM6.h>
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

}

void loop() {
  imu.read();
  mag.read();
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  snprintf(report, sizeof(report), "Accer: %6d %6d %6d    Gyro: %6d %6d %6d   Magno: %6d %6d %6d",
    imu.a.x, imu.a.y, imu.a.z, imu.g.x, imu.g.y, imu.g.z, mag.m.x, mag.m.y, mag.m.z);
  Serial.print(report);
   Serial.print("\tPressure: ");
  Serial.print(pressure);
  Serial.print(" mbar\tAltitude: ");
  Serial.print(altitude);
  Serial.print(" m\tTemp: ");
  Serial.print(temperature);
  Serial.println(" deg C");

  delay(1000);
}
