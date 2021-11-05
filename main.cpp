
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN 6 // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 62  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//----------------------------------------------Pins--------------------------------------------//

int Lbeam = 22;                  //low beam lights input (+yellow / white gnd)
int Hbeam = 24;                  //high beam lights input (+red / white gnd)
int Bflash = 26;                 //high beam flashing input (+orange / white gnd)
int Horn = 28;                   //horn input (+violet / blue gnd)
int Leftind = 30;                //left indicator input (+black / brown gnd)
int Rightind = 32;               //right indicator input (+green / brown gnd)
int Break = 34;                   //break light input
bool indicatorState = false;      //indicator status false=off


int LbeamOut = 2;               //low beam lights output
int HbeamOut = 3;                 //high beam lights output
int HornOut = 4;                  //horn output
/*
int LeftindOut = 5;               //left indicator output
int RightindOut = 6;              //right indicator output
int BreakOut = 7;                 //break light output
*/


//------------------------------------------------------Variables for auto off-----------------------------------------------------//
          
unsigned long previousMillis = 0;     //start time milliseconds
unsigned long interval = 40;          //Desired wait time in seconds (as millis)
unsigned long counterR=20;            //counter for right turn light
unsigned long counterL=0;             //counter for left turn light
int left=46;                          //turn lights starting point in led strip
int right=16;                         //turn lights starting point in led strip


//------------------------------------------left indicator-----------------------------------------------//
void leftindicator()
{
  if(digitalRead (Leftind)==LOW)
  {
    if (indicatorState==false)    //this turns off the tail light in the indicator area and only works once when the indicator light is on
    {
      for(int i=46; i<62; i++) 
      { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(00, 0, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.  
      }
      counterL=0;
      left=46;
      indicatorState=true;
    }
    
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis > interval) 
    {  //If interval is reached :
              
      counterL++;
      if(left<62) 
      { 
        pixels.setPixelColor(left, pixels.Color(255, 69, 0)); //255, 69, 0 orange
        pixels.show();   // Send the updated pixel colors to the hardware.
        left++;
        previousMillis = currentMillis;  
      }
        if(counterL>=16) 
        { 
          left=46;
          counterL=0;
          for(int i=46; i<62; i++) 
          { // For each pixel...
            pixels.setPixelColor(i, pixels.Color(00,00,0));
            pixels.show();
          }
        }   
    }
  }   
  
    if(digitalRead (Leftind)==HIGH){ ////Serial.println("poisVASEN");

      for(int i=46; i<62; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(30, 0, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.  

      }
     counterL=0;
      left=46;
    }
}
//------------------------------------------right indicator-----------------------------------------------//
void rightindicator(){

if(digitalRead (Rightind)==LOW){

                           
  if (indicatorState==false)    //this turns off the tail light in the indicator area and only works once when the indicator light is on
  {
    for(int j=16; j>=0; j--) 
    { 
      pixels.setPixelColor(j, pixels.Color(00, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.  
    }
      counterR=16;
      right=16;
      indicatorState=true;

  }
  
  unsigned long currentMillis = millis();           //call current millis
  if(currentMillis - previousMillis > interval) {  //If interval is reached :
    counterR--;

    if(right>0) { 
      pixels.setPixelColor(right, pixels.Color(255,69,0)); //255, 69, 0 orange
      pixels.show();   // Send the updated pixel colors to the hardware.
      right--;
      previousMillis = currentMillis;  
    }
    if(counterR<=0) { 
      right=16;
      counterR=16;
      for(int j=16; j>=0; j--) { // For each pixel...
        pixels.setPixelColor(j, pixels.Color(00,00,0));
        pixels.show();
      }
    }
  }

}

  if(digitalRead (Rightind)==HIGH){ 

    for(int j=16; j>=0; j--) { // For each pixel...
      pixels.setPixelColor(j, pixels.Color(30, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.  
    }
    counterR=16;
    right=16;

    }
 
}
//------------------------------------------Indicator Check------------------------------------------------//
void indicatorCheck(){

  if (digitalRead(Rightind)==HIGH || digitalRead(Leftind)==HIGH)
  {
    indicatorState = false;    //indicator is off
  }
  
 /* 
  if(digitalRead (Rightind)==HIGH){ 
    if (digitalRead(Leftind)==HIGH)
    {
     indicatorState = false;    //indicator is off 
    }
  }
  */
}
//------------------------------------------break lights-----------------------------------------------//
void breaklights(){

if(digitalRead (Horn)==LOW){ 
  for(int i=45; i>17; i--) {          // For each pixel...

    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}
else{
  for(int i=45; i>17; i--) {          // For each pixel...

    pixels.setPixelColor(i, pixels.Color(30, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}
} 

//------------------------------------------High beam lights-----------------------------------------------//
void highbeam(){

if(digitalRead (Hbeam)==LOW)
  { 
    digitalWrite(HbeamOut,HIGH);
  }
else
  {
   digitalWrite(HbeamOut,LOW);
  }
}
 
//------------------------------------------Low beam lights-----------------------------------------------//
void lowbeam(){

if(digitalRead (Lbeam)==LOW)
  { 
    digitalWrite(LbeamOut,HIGH);
  }
else
  {
   digitalWrite(LbeamOut,LOW);
  }
} 
//------------------------------------------void setup-----------------------------------------------//
void setup() {

  
  pixels.begin(); // Initialize NeoPixel strip object (REQUIRED)
  pixels.show();  // Initialize all pixels to 'off'

  
    for(int i=62; i>0; i--) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(30,0,0));

    pixels.show();  } // Send the updated pixel colors to the hardware.
  
//-----------------------------------------------------PINMODES-----------------------------------------------------//

  pinMode(22, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);        
  pinMode(28, INPUT_PULLUP);        
  pinMode(30, INPUT_PULLUP);        
  pinMode(32, INPUT_PULLUP);   
  pinMode(34, INPUT_PULLUP);       

  pinMode(LbeamOut, OUTPUT);       
  pinMode(HbeamOut, OUTPUT);
  pinMode(HornOut, OUTPUT);
  /*
  pinMode(LeftindOut, OUTPUT);
  pinMode(RightindOut, OUTPUT);
  pinMode(BreakOut, OUTPUT);*/
  


}
//------------------------------------------void loop-----------------------------------------------//
void loop() {

leftindicator();
rightindicator();
indicatorCheck();
breaklights();
highbeam();
lowbeam();


}
