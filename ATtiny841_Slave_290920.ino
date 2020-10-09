
#define __AVR_ATtiny841__

#include <Arduino.h>

#if defined(__AVR_ATtiny841__)
#define F_CPU 8000000                          // clock speed: 8MHz (external crystal) - modify as needed TÄSTÄ EN OLE VARMA? KÄYTÖSSÄ SISÄINEN KRISTALLI
#include "WireS.h"                              // I2C library for ATtiny841 (and other modern ATtinys)
#else
#define F_CPU 20000000                          // clock speed: 20MHz (external crystal) - modify as needed
#include "TinyWireS.h"                          // I2C library for ATtiny84A (and other older ATtinys)
#endif





// Analog pin for battery
const int analogPin = 1;
const int MosfetPin= 3; 



// I2C address number
const byte addr=9;  //Slaven osoite

int c=0;
double RefVolt= 5.0;  //laskennallinen jännitteen viitearvo



#define NUM_SAMPLES 30          //how many times it takes voltage sample 

int sum = 0;                    // kuinka monta arvoa jännitteestä otetaan ja niistä lasketaan keskiarvo
unsigned char sample_count = 0; // 


int voltage = 0;            // laskettu jännite
const int MosOn=1;          // viesti joka lähetetään kun mosfet on päällä
const int MosOff=2;         // viesti joka lähetetään kun mosfet on pois päältä

boolean SendVoltage = false;  //Masterin kanssa keskustelun muuttujia 
boolean SendMosfetOn = false;
boolean SendMosfetOff = false;



void setup() {
 TinyWireS.begin(addr);    //liittyy I2C väylään osoitteella addr
 TinyWireS.onReceive(receiveEvent); /* register receive event */
 TinyWireS.onRequest(requestEvent); /* register request event */

 analogReference(EXTERNAL);


 pinMode(analogPin, INPUT);           //   tekee a1 inputin
 pinMode(3, OUTPUT);        // 


}

void loop() {

     while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A1);
        sample_count++;
        delay(10);
    } 
    voltage = ((float)sum / (float)NUM_SAMPLES *5.15 ) ;

    sample_count = 0;
    sum = 0;
    voltage = map(voltage,0,5115,0,255); 

     delay(1000);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <TinyWireS.available()) {
    int c = TinyWireS.read();      /* receive byte as a character */
          /* print the character */
    if ( c==1){
      SendVoltage=true;
    }
    if ( c==2)  {
      SendMosfetOn=true;
      digitalWrite(3, HIGH);
    } 
    if ( c==3)  {
      SendMosfetOff=true;
      digitalWrite(3, LOW);
    }     
    
  }
}

// function that executes whenever data is requested from master
void requestEvent() {

 if(SendVoltage==1){
 TinyWireS.write(voltage);  // Lähettää jännitetiedon
 }
 if(SendMosfetOn==true){
 TinyWireS.write(MosOn);  // Lähettää Tiedon mosfetin tilasta
 }
  if(SendMosfetOff==true){
 TinyWireS.write(MosOff);  // Lähettää Tiedon mosfetin tilasta
 }



// Wire.write(",");


    SendVoltage = 0;
    SendMosfetOn = 0;
    SendMosfetOff = 0; 

}
