
#include<SoftwareSerial.h>

SoftwareSerial s(8,9);
int data; //Initialized variable to store recieved data

void setup() {
  Serial.begin(9600);
  //Serial Begin at 9600 Baud 
  s.begin(4600);
  
}

void loop() {
  data = s.read(); //Read the serial data and store it
  Serial.println(data);
  delay(1000);
}
