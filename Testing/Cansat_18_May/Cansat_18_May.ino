#include <Wire.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <LSM6.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Servo.h>
#include <SPI.h>
#include <SD.h> 
const int chipSelect = 7; 
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
unsigned int count=0;
float voltage =0;
signed int alt=0;
int buzz=5;
int ss=0;
int ldr=1;
String data= "";
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
    float pressure = ps.readPressureMillibars();
    alt = ps.pressureToAltitudeMeters(pressure);
    pinMode(buzz, OUTPUT);
    servo1.attach(6);
    servo2.attach(11);
    servo3.attach(12); 
    delay(1000);
    Wire.begin(4);
    if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // don't do anything more:
    return;
  }
  Serial.println(F("card initialized.")); 
}
uint32_t timer = millis();
void receiveEvent(int howMany) {
data= "";
  while( Wire.available()){
    data += (char)Wire.read();
  }

}
void loop() {
    imu.read();
    float pressure = ps.readPressureMillibars();
    signed int altitude = ps.pressureToAltitudeMeters(pressure);
    float temperature = ps.readTemperatureC();
    snprintf(report, sizeof(report), "%6d,%6d,%6d",
    imu.a.x, imu.a.y, imu.a.z);
    tmElements_t tm;
    if((altitude-alt)>-5 && (altitude-alt)<10 && ss==0)
    {
      ss=4;
      Serial.println(ss);
    }
    
    else if((5<(altitude-alt)) && ((altitude-alt)<725) && (ss<3)){
//      servo1.write(90);
      ss=2;
      if((675<(altitude-alt)<725) && ss==2 && ldr){
        ss=3;
        servo1.write(90);
//        Serial.print("helllo");
//        Serial.print((altitude-alt));
        Serial.println(ss);
      }
    }
    else if(((altitude-alt)<725) && ss>2 && ss<6){
        Serial.print("1644,");
        if (RTC.read(tm)) {
        //Serial.print("Ok, Time = ");
        print2digits(tm.Hour);
//        Serial.print(':');
        print2digits(tm.Minute);
//        Serial.print(':');
        print2digits(tm.Second);
        Serial.print(',');
        }
        count++;
        Serial.print(count);
        Serial.print(",");
        Serial.print(altitude);
        Serial.print(",");
        Serial.print(pressure);
        Serial.print(",");
        Serial.print(temperature);
        Serial.print(",");
        voltage = analogRead(A0);
        
        voltage = map(voltage, 0, 1023, 0, 10);
        Serial.print(voltage);
        Serial.print(",");
        Wire.onReceive(receiveEvent);
         Serial.print(data);
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
        if((310<(altitude-alt)) && ((altitude-alt)<725) && ss==3){
          ss=4;
          Serial.println(ss);
         }
        else if((290<(altitude-alt)) && ((altitude-alt)<310) && ss==4){
        servo2.write(90);
        servo3.write(90);
        ss=5;
        Serial.println(ss);
        }
        else{
          Serial.println(ss);
       }
       File dataFile = SD.open("datalog.txt", FILE_WRITE);
     if (dataFile){
        dataFile.print("1644,");
        dataFile.print(tm.Hour);
        dataFile.print(':');
        dataFile.print(tm.Minute);
        dataFile.print(':');
        dataFile.print(tm.Second);
        dataFile.print(',');
        dataFile.print(count);
        dataFile.print(",");
        dataFile.print(altitude);
        dataFile.print(",");
        dataFile.print(pressure);
        dataFile.print(",");
        dataFile.print(temperature);
        dataFile.print(",");
        dataFile.print(voltage);
        dataFile.print(",");
        dataFile.print(data);
        dataFile.print(",");
        dataFile.print(angleX);
        dataFile.print(",");
        dataFile.print(angleY);
        dataFile.print(",");
        dataFile.print(angleZ);

   
    dataFile.close();

  }
    }
    else if((altitude-alt)<10 && ss==5){
      digitalWrite(buzz, LOW);
      ss=6; 
      Serial.println(ss);   
      }
 
    
    else{
      Serial.print("hello");
            Serial.print(altitude-alt);
      Serial.println(ss);

    }
    delay(1000);  
 
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
