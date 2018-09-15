// Include the required Wire library for I2C<br>
#include <Wire.h>
String data= "";
void setup() {
  // Define the LED pin as Output
  // Start the I2C Bus as Slave on address 9
  Wire.begin(4); 
  Serial.begin(9600);
  Serial.print("hello");
  // Attach a function to trigger when something is received.
//    Wire.onReceive(receiveEvent);
}
void receiveEvent(int howMany) {
data= "";
  while( Wire.available()){
    data += (char)Wire.read();
  }
 Serial.println(data);
}
void loop() {
   Wire.onReceive(receiveEvent);
//  Serial.print("hello");

  delay(100);
}

