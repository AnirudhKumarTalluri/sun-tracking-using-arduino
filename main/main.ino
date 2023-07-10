//Servo motor library
#include <Servo.h>

#include<SoftwareSerial.h>

SoftwareSerial s(5,6);
int data; //Initialized variable to store recieved data


//Initialize variables

int ldrtopr= 0;                // top-right LDR                          
int ldrtopl = 1;               // top-left LDR                          
int ldrbotr = 3;               // bottom-right LDR                     
int ldrbotl = 5;               // bottom-left LDR                   
int topl = 0;
int topr = 0; 
int botl = 0;
int botr = 0;

//Declare two servos
Servo servo_updown;
Servo servo_rightleft;

int threshold_value=10;           //measurement sensitivity


void automaticsolartracker(){
  
     //capturing analog values of each LDR
     topr= analogRead(ldrtopr);         //capturing analog value of top right LDR
     topl= analogRead(ldrtopl);         //capturing analog value of top left LDR
     botr= analogRead(ldrbotr);         //capturing analog value of bot right LDR
     botl= analogRead(ldrbotl);         //capturing analog value of bot left LDR

     Serial.print("l1 : ");
     Serial.print(topr);
     Serial.print(" l2 : ");
     Serial.print(topl);
     Serial.print(" l3 : ");
     Serial.print(botr);
     Serial.print(" l4 : ");
     Serial.print(botl);
     Serial.println();
     
    // calculating average
     int avgtop = (topr + topl) / 2;     //average of top LDRs
     int avgbot = (botr + botl) / 2;     //average of bottom LDRs
     int avgleft = (topl + botl) / 2;    //average of left LDRs
     int avgright = (topr + botr) / 2;   //average of right LDRs
   
    //Get the different 
     int diffelev = avgtop - avgbot;      //Get the different average betwen LDRs top and LDRs bot
     int diffazi = avgright - avgleft;    //Get the different average betwen LDRs right and LDRs left
    
    //left-right movement of solar tracker
     
      if (abs(diffazi) >= threshold_value){        //Change position only if light difference is bigger then the threshold_value
       if (diffazi > 0) {
        if (servo_rightleft.read() < 180) {
          servo_rightleft.write((servo_updown.read() + 2));
        }
      }
      if (diffazi <  0) {
        if (servo_rightleft.read() > 0) {
          servo_rightleft.write((servo_updown.read() - 2));
        }
      }
    }
             
      //up-down movement of solar tracker

      if (abs(diffelev) >= threshold_value){    //Change position only if light difference is bigger then thethreshold_value
       if (diffelev > 0) {
        if (servo_updown.read() < 180) {
          servo_updown.write((servo_rightleft.read() - 2));
        }
      }
      if (diffelev <  0) {
        if (servo_updown.read() > 0) {
          servo_updown.write((servo_rightleft.read() + 2));
        }
      }
    }       
 }  


 

void setup()
{
  Serial.begin(9600);                                //serial connection setup  //opens serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");  

  s.begin(9600);  

  servo_updown.attach(9);             //Servo motor up-down movement
  servo_rightleft.attach(10);          //Servo motor right-left movement
}
void loop()
{
    /*float volt = analogRead(A5)*5.0/1023;
    float voltage = 2*volt;                //  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt)
    float current = voltage/20;            //  I=voltage/(R1+R2) 
    float power = voltage*current;
    Serial.print("DATA,TIME,"); // PLX-DAQ command
    Serial.print(voltage);    //send the voltage to serial port
    Serial.print(",");
    Serial.print(current);    //send the current to serial port
    Serial.print(",");
    Serial.print(power);  //send the power to serial port
    Serial.print(",");*/

    /*data=s.read();
    Serial.println(data);*/
    automaticsolartracker();
}
