#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


LiquidCrystal_I2C  lcd2(0x27,2,1,0,4,5,6,7); // 0x26 is the I2C bus address for an unmodified module
//I"C variables
const int voltage =1;
const int byPassOn= 2; 
const int byPassOff= 3; 

// Define LED Pin
int LED = 13;
 
// Variable for received data
int ReceiveData; 
int Rms; //Receive Mosfet State, vastaanottaa mosfetin tilatiedon ON/OFF
//int slaveAddr = 8;   //slave osoitteet alkavat 8


float maxVolt =4.2;     // maksimi jännitte ladattaessa, jolloin MOSFET kytkeytyy päälle

//slave address logic
const int numOfSlaves = 2; // I2C addresses 8+numOfSlaves--> is reserved for slave addresses 



void setup() {
 Serial.begin(9600); /* begin serial comm. */
 Wire.begin(); /* join i2c bus as master */
 Serial.println("I am I2C Master");
 lcd2.setBacklightPin(3,POSITIVE);
 lcd2.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
 lcd2.begin(20, 4);
 lcd2.clear();
}

void loop() {

 for( int i = 8; i < numOfSlaves+8; i++) {


 Wire.beginTransmission(i); //aloittaa keskustelun slave 8:n kanssa
 Wire.write(voltage);  //kysyy jännitettä
 Wire.endTransmission();    //lopettaa keskustelun
 Wire.requestFrom(i, 1); // pyytää ja lukee datan slavelta, datan koko 1 bitti

   while(Wire.available()){
     ReceiveData = Wire.read();
  }
    Serial.println("***********************************");
    Serial.print("slave ");
    Serial.print(i);
    Serial.print("=");
    Serial.println(ReceiveData*5.0/255);
    lcd2.setCursor(0,0);
    lcd2.print("slave ");
    lcd2.print(i);
    lcd2.print(":");
    lcd2.print(ReceiveData*5.0/255);
    delay(1000);
   /*Serial.print("slave 9:  ");
    Serial.println(Slave9);
    lcd2.setCursor(0,1);
    lcd2.print(Slave9);
    Serial.print("slave 10:  ");
    Serial.println(Slave10);
    lcd2.setCursor(0,2);
    lcd2.print(Slave10);
*/
    /*
    Serial.print("slave 10:  ");
    Serial.println(ac);
    Serial.print("slave 11:  ");
    Serial.println(ad);
    Serial.print("slave 12:  ");
    Serial.println(ae);
    Serial.print("slave 13:  ");
    Serial.println(af);
    Serial.print("slave 14:  ");
    Serial.println(ag);
    Serial.print("slave 15:  ");
    Serial.println(ah);
    */


   
   if((ReceiveData*5.0/255)>maxVolt){   //YLIJÄNNITESUOJAUS 
    /*
    lcd2.setCursor(6,0);
    lcd2.print("      ");
    lcd2.setCursor(6,1);
    lcd2.print("      ");
    */
    Wire.beginTransmission(i); /* begin with device address */
    Wire.write(byPassOn);  /* sends hello string */
    Wire.endTransmission();    /* stop transmitting */
    Wire.requestFrom(i, 1); /* request & read data of size 1 from slave */   
     while(Wire.available()){
     Rms = Wire.read();
    } 
    if(Rms==1){ // Jos Rms = 1 niin slaven mosfet output == HIGH
    Serial.println();
    Serial.print("Mosfet in slave:");
    Serial.print(i);
    Serial.println("ON");
    }
   }
   else {   // Jos Rms ei 1 niin slaven mosfet kytketään Pois päältä
    Wire.beginTransmission(i); 
    Wire.write(byPassOff); 
    Wire.endTransmission();    
    Wire.requestFrom(i, 1);
     while(Wire.available()){   //kysytään Rms tilaa 
     Rms = Wire.read();
    } 
    if(Rms==2){ // Jos Rms = 0 niin slaven mosfet output == LOW
    Serial.println();
    Serial.print("Mosfet in slave:");
    Serial.print(i);
    Serial.println("OFF");
        } 
      }
    ReceiveData = 0;
    Rms = 0;
    //slaveAddr++;

 }


 delay(1000);
 lcd2.clear();
 //slaveAddr=8;   // sets slave addres back to 8
 
 }

 

 
 
