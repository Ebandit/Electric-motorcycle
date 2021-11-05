#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 62
#define NUM_LEFT_LEDS 16


int Lbeam = 22;                  //low beam lights input (+yellow / white gnd)
int Hbeam = 24;                  //high beam lights input (+red / white gnd)
int Bflash = 26;                 //high beam flashing input (+orange / white gnd)
int Horn = 28;                   //horn input (+violet / blue gnd)
int Leftind = 30;                //left indicator input (+black / brown gnd)
int Rightind = 32;               //right indicator input (+green / brown gnd)
int Break = 34;                   //break light input
bool indicatorState = false;      //indicator status false=off
bool brakeState = false;


int LbeamOut = 2;               //low beam lights output
int HbeamOut = 3;                 //high beam lights output
int HornOut = 4;                  //horn output



CRGBArray<NUM_LEDS> leds;
CRGBArray<NUM_LEFT_LEDS> leftleds;



unsigned long previousMillis = 0;     //start time milliseconds
unsigned long interval = 25;          //Desired wait time in seconds (as millis)
int indPixL = 46 ; 
int indPixR = 16 ; 
int fade = 60;

void indicatorLeft(){


  unsigned long currentMillis = millis();
  if(digitalRead (Leftind)==LOW){  

    if(currentMillis - previousMillis > interval) 
    {   
      // fade everything out
      for (int i = 46; i < 62; i++)
      {
      leds[i].fadeToBlackBy(fade);
      }
      
   

      // let's set an led value
      leds[indPixL] = CHSV(23,255,255);
      FastLED.show();
      indPixL++;
      if(indPixL>=62)
      {
        indPixL=46;
      }
      previousMillis = currentMillis;  
    }
  }
      if(digitalRead (Leftind)==HIGH){ 

      for(int i=46; i<62; i++) { 
      leds[i] = CHSV(255,255,80); 
      FastLED.show();

      }
    }
}
void indicatorRight(){


  unsigned long currentMillis = millis();
  if(digitalRead (Rightind)==LOW){  

    if(currentMillis - previousMillis > interval) 
    {   
      // fade everything out
      for (int i = 16; i > 0; i--)
      {
      leds[i].fadeToBlackBy(fade);
      }

      // let's set an led value
      leds[indPixR] = CHSV(23,255,255);
      FastLED.show();
      indPixR--;
      if(indPixR<=0)
      {
        indPixR=16;
      }
      previousMillis = currentMillis;  
    }
  }
      if(digitalRead (Rightind)==HIGH){ 

      for(int i=16; i>=0; i--) { 
      leds[i] = CHSV(255,255,80); 
      FastLED.show();

      }
    }
}
//------------------------------------------break lights-----------------------------------------------//
void breaklights(){

if(brakeState==false && digitalRead (Horn)==LOW){ 
  for(int i=45; i>16; i--) {          // For each pixel...

      leds[i] = CHSV(255,255,255); 
      FastLED.show();
      brakeState = true;
  }
}
if(brakeState==true && digitalRead(Horn)==HIGH){
  for(int i=45; i>16; i--) {          // For each pixel...

      leds[i] = CHSV(255,255,80); 
      FastLED.show();
  }
  brakeState=false;
}
} 
void setup() { 
  
  FastLED.addLeds<NEOPIXEL,6>(leds, NUM_LEDS); 
  //Serial.begin(9600);

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

  for(int i=45; i>16; i--) {          // For each pixel...

      leds[i] = CHSV(255,255,80); 
      FastLED.show();
  }

}

void loop(){ 

indicatorLeft();
indicatorRight();
breaklights();
  }

