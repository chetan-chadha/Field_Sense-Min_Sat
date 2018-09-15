#include <SoftwareSerial.h>

float Output=0;
void setup() {
  Serial.begin(9600);
}
void loop() {  
   float sensorValue = analogRead(A0); 
   output=sqrt((2*sensorValue)/1.225);
   Serial.println(output);
   Serial.print("m/s");
   delay(100);
}
