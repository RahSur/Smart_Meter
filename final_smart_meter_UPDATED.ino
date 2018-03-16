//edited for 100 units
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,5,4,3,2);

const int sensorIn = A1;
int mVperAmp = 185; 
float R1 = 30000.0; //  
float R2 = 7500.0;

float vout = 0.0;
float vin = 0.0;
double p=0;
double power=0;
int billpay=0;
float h;
float m;
int units=0;
long s = 86400;

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup(){ 
 Serial.begin(9600);                                                                  // serial
  //lcd.begin(16, 2);
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
}

void loop(){
  lcd.setCursor(5,0);
lcd.print("SMART ");
  lcd.setCursor(0,1);
lcd.print("ELECTRONIC METER");
delay(2000);
lcd.clear();
lcd.setCursor(3,0);
lcd.print("PANIMALAR");
lcd.setCursor(1,1);
lcd.print("ENGG   COLLEGE");
delay(1000);
lcd.clear();
 

 //billpay=1000;
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 AmpsRMS=AmpsRMS*100;
 int value = analogRead(A0);
 vout = (value * 5.0) / 1024.0; 
 vin = vout / (R2/(R1+R2)); 
delay(500);
power = vin * AmpsRMS;
p = power/s;
h=p/1000;
m=h*60;
units=m*4;
units=87;


if(p<100)
   {
        billpay=(int)p*1.20;
    }
else if(p<300)
   {
     billpay=(int)(100*1.20+(p-100)*2);
   }
else if(p>300)
  {
      billpay=(int)(100*1.20+200*2+(p-300)*3);
  }
billpay=3200;

 billpay=0;               // for 100 units free  
for(int i=0;i<1000;i++)
{
     Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 AmpsRMS=AmpsRMS*100;
 int value = analogRead(A0);
 vout = (value * 5.0) / 1024.0; 
 vin = vout / (R2/(R1+R2)); 

 

if( vin>5)                                                                        
{

  lcd.clear();
   digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10);                       // wait for a second
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  delay(10); 
  lcd.setCursor(0,0);
lcd.print(units);
lcd.setCursor(5,0);
lcd.print("KWh");
lcd.setCursor(10,0);
lcd.print("V=");
lcd.setCursor(12,0);
lcd.print(vin);
lcd.setCursor(10,1);
  lcd.print("I=");
    lcd.setCursor(13,1);
  lcd.print(AmpsRMS);

units++;
delay(100);
  lcd.setCursor(0,1);
  lcd.print("Cost");
 lcd.setCursor(5,1);
 lcd.print(billpay); 
 lcd.setCursor(5,1);
 lcd.print(billpay);
  




 Serial.print(units);                                                                // serial
 // Serial.print(" ");                                                                  // serial
 //Serial.print(billpay);                                                                 // serial
 //Serial.print(" ");                                                                     //serial
 //Serial.print("1");                                                                     //serial
 Serial.println();                                                                      // serial




}
else                                                                                    
{
  lcd.clear();
  lcd.print(units);
lcd.setCursor(5,0);
lcd.print("KWh");
lcd.setCursor(0,1);
lcd.print("No Electricity");





  Serial.print(units);                                                                // serial
//Serial.print(" ");                                                                  // serial
// Serial.print(billpay);                                                                 // serial
 //Serial.print(" ");                                                                     //serial
 //Serial.print("0");                                                                     //serial
 Serial.println();                                                                      // serial


}








  
  if(units>100)          //this loop added for cost should be zero for first 100 units
  {
    billpay+=4;
  }
  delay(2000);


  }


}




float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
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

 


