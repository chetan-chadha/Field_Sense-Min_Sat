int sensorPin = A0;   
int sensorValue = 0; 
float Vout=0;
float P=0;
void setup() {

  // declare the ledPin as an OUTPUT:
   Serial.begin(9600); 
}

void loop() {
    int i=0;
    int sum=0;
    int offset=0;
    Serial.println("init...");
    for(i=0;i<10;i++)
    {
         sensorValue = analogRead(sensorPin)-512;
         sum+=sensorValue;
    }
    offset=sum/10.0;
    Serial.println("Ok");
    while(1)
    {
       sensorValue = analogRead(sensorPin)-offset; 
       Vout=(5*sensorValue)/1024.0;
       P=Vout-2.5;           
       Serial.print("Presure = " );                       
       Serial.print(P*1000); 
       Serial.println("Pa");
       delay(1000);   
    }
}
