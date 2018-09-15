#include <Wire.h>
int x = 0;
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
}
void loop() {
  Wire.beginTransmission(9);// transmit to device #9
  Wire.write("Hello hi how are you hdsah iusb shnfo hsnfd");              // sends x 
  Wire.endTransmission();// stop transmitting
  delay(500);
}

