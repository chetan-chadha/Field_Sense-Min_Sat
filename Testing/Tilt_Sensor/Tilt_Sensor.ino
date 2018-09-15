/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 15)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LSM6.h>
SoftwareSerial xbee(2, 3);
LSM6 imu;

char report[80];

void setup()
{
  Serial.begin(9600);
  xbee.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();

  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
    imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z);
//  Serial.println(report);
  int xAccl=imu.a.x;
  int yAccl=imu.a.y;
  int zAccl=imu.a.z;
  float angleX = atan2(xAccl,(sqrt(pow(yAccl,2)+pow(zAccl,2))))*(180/PI);
 float angleY = atan2(yAccl,(sqrt(pow(xAccl,2)+pow(zAccl,2))))*(180/PI);
 float angleZ = atan2((sqrt(pow(xAccl,2)+pow(yAccl,2))),zAccl)*(180/PI); 
 Serial.print("anglex");
 Serial.print(angleX);
 Serial.print(" angley");
 Serial.print(angleY);
 Serial.print(" anglez");
 Serial.print(angleZ);

 xbee.print("anglex");
xbee.print(angleX);
xbee.print(" angley");
xbee.print(angleY);
 Serial.print(" anglez");
 Serial.print(angleZ); Serial.println();
  delay(1000);
}
