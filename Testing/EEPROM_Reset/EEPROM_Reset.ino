#include <EEPROM.h>
int val;
void setup(){
  Serial.begin(9600);
  val = EEPROM.read(0);
  Serial.print("Starting; current EEPROM value is ");
  Serial.println(val);
  
//  if(val != 1){
//    Serial.println("EEPROM byte not set yet; Writing...");
//    EEPROM.write(0, 1);
//  } else if (val == 1){
//    Serial.println("EEPROM byte was set!");
//  }
//  Serial.println("Done.");
}

void loop(){
 val++;
 Serial.println(val);
 EEPROM.write(0, val);
 delay(2000);
}
