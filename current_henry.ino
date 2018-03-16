/*
Measuring AC Current Using ACS712
*/
const int sensorIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module


double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,4,3,2,1);


void setup(){ 
 //Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(){
 
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 lcd.setCursor(0, 0);
 //AmpsRMS=AmpsRMS*100;  // only this line modified by me to get rounf off value-----sundeep---
 lcd.print(AmpsRMS);
 lcd.print("  Amps");
 //Serial.print(AmpsRMS);
 //Serial.println(" Amps RMS");








//   AC VOLTAGE MEASUREMENT+                                                    both codes works only upto 8v.......i think thats the max sense capacity of sensor


 
  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (250.0 / 1024.0);                                // This code
  lcd.setCursor(0, 1);
  lcd.print(voltage);
  lcd.print(" Volts");
  delay(1000);



                                                                                //or



  /*float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; 
float R2 = 7500.0; 
int value = 0;
   value = analogRead(A1);
   vout = (value * 5.0) / 1024.0;                                                 //this code
   vin = vout / (R2/(R1+R2)); 
   lcd.setCursor(0, 1);
   lcd.print(vin);*/






 

}

float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   int start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
