#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 62
CRGBArray<NUM_LEDS> leds;

/********************************INPUTS********************************************/
#define lBeam  22                  //low beam lights input (+yellow / white gnd) 
#define hBeam  24                  //high beam lights input (+red / white gnd)
#define bFlash  26                 //high beam flashing input (+orange / white gnd)
#define horn  28                   //horn input (+violet / blue gnd)
#define leftInd  30                //left indicator input (+black / brown gnd)
#define rightInd  32               //right indicator input (+green / brown gnd)
#define breakLight  34                  //break light input

/*********************************OUTPUTS******************************************/

const int lBeamOut = 2;               //low beam lights output
const int hBeamOut = 3;                 //high beam lights output
const int hornOut = 4;                  //horn output

/**********************************VARIABLES**************************************/

unsigned char interval = 60;          //Desired wait time in seconds (as millis)
unsigned char fade = 100;              //bigger number means faster fade
unsigned char indPixL = 46 ;          // defines left indicators first led on string
unsigned char indPixR = 16 ;           // defines right indicators first led on string

//-----------------------------------------Left Indicator-----------------------------------------------//

void indicatorLeft()
{
  if(digitalRead (leftInd)==LOW)
  {
    

    EVERY_N_MILLISECONDS(interval) 
    {   
        // fade everything out
      for (int i = 46; i < NUM_LEDS; i++)
      {
        leds[i].fadeToBlackBy(fade);
        
      }
        // let's set an led value
        leds[indPixL] = CHSV(23,255,255);
        leds[indPixL+1]= CHSV(23,255,255);
        leds[indPixL+2]= CHSV(23,255,255);
        FastLED.show();
        indPixL++;

        if(indPixL>=NUM_LEDS-2)
        {
          indPixL=46;
        }
       
    }
  }
  if(digitalRead (leftInd)==HIGH ){ 

    fill_solid((&leds[46]), 16, CHSV(255,255,80));  
    FastLED.show();
    indPixL=46;
  }
}
//------------------------------------------Right Indicator-----------------------------------------------//
void indicatorRight()
{



  if(digitalRead (rightInd)==LOW)
  {  
      

    EVERY_N_MILLISECONDS(interval) 
    {                  
      for (int i = 16; i > 0; i--)
      {
        leds[i].fadeToBlackBy(fade);
      }
      // let's set an led value
      leds[indPixR] = CHSV(23,255,255);
      leds[indPixR-1]= CHSV(23,255,255);
      leds[indPixR-2]= CHSV(23,255,255);      
      FastLED.show();
      indPixR--;
      if(indPixR<=2)
      {
        indPixR=16;
      }      
    }
  }
  if(digitalRead (rightInd)==HIGH)
  { 
    fill_solid((&leds[1]), 16, CHSV(255,255,80)); 
    FastLED.show(); 
    indPixR=16;
  }
}
//------------------------------------------break lights-----------------------------------------------//
void Breaklights()
{
  if(digitalRead (breakLight)==LOW)
  { 
    fill_solid((&leds[17]), 30, CHSV(255,255,255));  
    FastLED.show();
        
  }
  if(digitalRead(breakLight)==HIGH)
  {
    fill_solid((&leds[17]), 30, CHSV(255,255,80));  
    FastLED.show();      
  }
}
//------------------------------------------front lights-----------------------------------------------//
void frontlights()
{
  if(digitalRead (bFlash)==LOW || digitalRead(hBeam)==LOW)
  { 
    digitalWrite(lBeamOut, LOW);
    digitalWrite(hBeamOut, HIGH);
     
  }
  else
  {
    digitalWrite(hBeamOut,LOW);

  }

  if(digitalRead(lBeam)==LOW)
  {
  digitalWrite(lBeamOut, HIGH);
  digitalWrite(hBeamOut, LOW);

  }
  else
  {
    digitalWrite(lBeamOut,LOW);

  }
}  

void police(){
  if(digitalRead(horn)==LOW){

  

  EVERY_N_MILLISECONDS(interval){
    for (int i = 0; i < 8 ; i++)
    {
      fill_solid( leds, NUM_LEDS, CHSV(HUE_BLUE,255,255));
      FastLED.show();
      FastLED.delay(40);
      fill_solid( leds, NUM_LEDS, CHSV(255,255,0));
      FastLED.show();
      FastLED.delay(40);
      
    }
    

    for (int i = 0; i < 3; i++)
    {
      
    
    for (int i = 0; i < NUM_LEDS*random8(30); i++)
    {
      leds[random8(NUM_LEDS)] = CHSV(HUE_BLUE,255,255);
      FastLED.show();  
      leds[random8(NUM_LEDS-1)] = CHSV(HUE_RED,255,0);
      FastLED.show();  
    }
  
  for (int i = 0; i < 1; i++)
{ 
  
  for(int i = 0; i < NUM_LEDS/2; i++) {   
    // fade everything out
    leds.fadeToBlackBy(20);

    // let's set an led value
    leds[i] = CHSV(HUE_BLUE,255,255);

    // now, let's first 20 leds to the top 20 leds, 
    leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(5);
  }
    for(int i = NUM_LEDS; i > NUM_LEDS/2; i--) {   
    // fade everything out
    leds.fadeToBlackBy(20);
    
  }
}
    }
  }
}
}
//------------------------------------------SETUP-----------------------------------------------//
void setup() 
{ 

  FastLED.addLeds<NEOPIXEL,52>(leds, NUM_LEDS); 


  pinMode(22, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);        
  pinMode(28, INPUT_PULLUP);        
  pinMode(30, INPUT_PULLUP);        
  pinMode(32, INPUT_PULLUP);   
  pinMode(34, INPUT_PULLUP);       

  pinMode(lBeamOut, OUTPUT);       
  pinMode(hBeamOut, OUTPUT);
  pinMode(hornOut, OUTPUT);


  for (int i = 0; i < 1; i++)
{ 
  static uint8_t hue;
  for(int i = 0; i < NUM_LEDS/2; i++) {   
    // fade everything out
    leds.fadeToBlackBy(30);

    // let's set an led value
    leds[i] = CHSV(hue++,255,255);

    // now, let's first 20 leds to the top 20 leds, 
    leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(33);
  }
    for(int i = NUM_LEDS; i > NUM_LEDS/2; i--) {   
    // fade everything out
    leds.fadeToBlackBy(30);
    FastLED.delay(33);
  }
}
  
  fill_solid( leds, NUM_LEDS, CHSV(255,255,80));
  FastLED.show();
  Serial.begin(9600);
}

void loop()
{ 

  indicatorLeft();
  indicatorRight();
  Breaklights();
  frontlights();
  police();
  
}

