#include <FastLED.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

#define DATA_PIN 6
#define DATA_PIN1 5
#define NUM_LEDS 110   
#define NUM_LEDS1 11

CRGBArray<NUM_LEDS> leds;
CRGBArray<NUM_LEDS1> leds1;

/********************************INPUTS********************************************/
#define lBeam A3      //low beam lights input (+yellow / white gnd)
#define hBeam A4      //high beam lights input (+red / white gnd)
#define horn A5       //horn input (+violet / blue gnd)
#define leftInd A0    //left indicator input (+black / brown gnd)
#define rightInd A1   //right indicator input (+green / brown gnd)
#define breakLight A2 //break light input
#define can5vOutput 3 //CAN BUS 5V output rasberry

const int numOfInputs = 6;
int inputPins[] = {A0, A1, A2, A3, A4 ,A5};

/*********************************OUTPUTS******************************************/

const int lBeamOut = 7; //low beam lights output
const int hBeamOut = 8; //high beam lights output
const int hornOut = 4;  //horn output

/**********************************VARIABLES**************************************/

unsigned char interval = 100; //Desired wait time in seconds (as millis)
unsigned char fade = 80;     //bigger number means faster fade
unsigned char indPixL = 61;  // defines left indicators first led on string
unsigned char indPixR = 49;  // defines right indicators first led on string
unsigned char indPixL1 = 6;  // defines left indicators first led on string
unsigned char indPixR1 = 1;  // defines right indicators first led on string
int delayTurnLedOff = 130;    //delay from animation to black (is used twice)

unsigned long currentMillis = 0; 
unsigned long previousMillis = 0;

boolean turnsignalL = false;
boolean turnsignalR = false;
boolean blinkers = false;
boolean poliisi = false;
boolean epilepsia = false;

int iA = 0;
int iB = 6;
int iC = 61;

int headlightCanState = 0;
int blinkerCanState = 0;
//int interlockCanState = 0; //interlockille voidaan lisätä rele, jolloin näytölle voidaan tuoda tästä tieto
int ledCanState = 0;
//-----------------------------------------Left Indicator-----------------------------------------------//

void indicatorLeft()
{
  if (digitalRead(leftInd) == LOW && digitalRead(rightInd) == HIGH && blinkers == false) 
  {  
    turnsignalL = true;
  
    EVERY_N_MILLISECONDS(interval)
    {
      // fade everything out
      fadeToBlackBy((&leds[61]), 5, fade);
      fadeToBlackBy((&leds1[6]), 5, fade);
       // let's set an led value
      leds[indPixL] = CHSV(30, 255, 255);
      leds1[indPixL1] = CHSV(23, 255, 255); 
      FastLED.show();
      indPixL++;
      indPixL1++;
      if (indPixL >= 66)
      {                
           //---delay---//
           currentMillis = previousMillis = millis();
           while(previousMillis + delayTurnLedOff >= currentMillis){
           currentMillis = millis();
    }  
        fill_solid((&leds[61]), 5, CHSV(0, 0, 0));
        fill_solid((&leds1[6]), 6, CHSV(0, 0, 0));
        indPixL = 61;
        indPixL1 = 6;
      } } }
  if (digitalRead(leftInd) == HIGH) // || blinkers == true || turnsignalR == true)
  {
    turnsignalL = false;
    fill_solid((&leds1[6]), 6, CHSV(0, 0, 0));
    FastLED.show();
    indPixL = 61;
    indPixL1 = 6;
  } }

//------------------------------------------Right Indicator-----------------------------------------------//
void indicatorRight()
{
  if (digitalRead(rightInd) == LOW && digitalRead(leftInd) == HIGH && blinkers == false)  
  {   
    turnsignalR = true;  
    EVERY_N_MILLISECONDS(interval)
    {
       fadeToBlackBy((&leds[45]), 5, fade);
      fadeToBlackBy((&leds1[1]), 5, fade);
      // let's set an led value      
      leds[indPixR] = CHSV(30, 255, 255);
      leds1[indPixR1] = CHSV(23, 255, 255);     
      FastLED.show();
      indPixR--;
      indPixR1++;
      if (indPixR <= 44)
      {
           //---delay---//
           currentMillis = previousMillis = millis();
           while(previousMillis + delayTurnLedOff >= currentMillis){
           currentMillis = millis();
    }
        fill_solid((&leds[44]), 5, CHSV(0, 0, 0));
        fill_solid((&leds1[0]), 6, CHSV(0, 0, 0));        
        FastLED.show();
        indPixR = 49;
        indPixR1 = 1;
      } } }
  if (digitalRead(rightInd) == HIGH) //|| blinkers == true || turnsignalL == true)
  {
    turnsignalR = false;
    fill_solid((&leds1[0]), 6, CHSV(0, 0, 0));
    FastLED.show();
    indPixR1 = 1;
    indPixR = 49;
  } }
//------------------------------------------Blinkers-----------------------------------------------//
void Blinkers() 
{
 if (digitalRead(rightInd) == LOW && digitalRead(leftInd) == LOW) 
  { 
    turnsignalR=false;
    turnsignalL=false;
    blinkers = true; 
    EVERY_N_MILLISECONDS(interval)
    {
      fadeToBlackBy((&leds[61]), 5, fade);
      fadeToBlackBy((&leds1[1]), 5, fade);
      fadeToBlackBy((&leds[45]), 5, fade);
      fadeToBlackBy((&leds1[1]), 5, fade);
      // let's set an led value      
      leds[indPixR] = CHSV(30, 255, 255);
      leds1[indPixR1] = CHSV(23, 255, 255);        
      leds[indPixL] = CHSV(30, 255, 255);
      leds1[indPixL1] = CHSV(23, 255, 255);    
      FastLED.show();
      indPixR--;
      indPixR1++;
      indPixL++;
      indPixL1++;
      if (indPixR <= 44)
      {       
           //---delay---//       
            currentMillis = previousMillis = millis();
             while(previousMillis + delayTurnLedOff >= currentMillis){
           FastLED.show();
           currentMillis = millis();
    }
        fill_solid((&leds[44]), 5, CHSV(0, 0, 0));
        fill_solid((&leds1[0]), 6, CHSV(0, 0, 0));
        fill_solid((&leds[61]), 5, CHSV(0, 0, 0));
        fill_solid((&leds1[6]), 6, CHSV(0, 0, 0));
        FastLED.show();
        indPixR = 49;
        indPixR1 = 1;    
        indPixL = 61;
        indPixL1 = 6;
      } } }  
  if (digitalRead(rightInd) == HIGH && digitalRead(leftInd) == HIGH)
  {
    blinkers = false;
  } }

//------------------------------------------break lights-----------------------------------------------//
void Breaklights()
{
  if (digitalRead(breakLight) == LOW && turnsignalR == false && turnsignalL == false && blinkers == false) 
  {
    fill_solid((&leds[45]), 21, CHSV(255, 255, 255));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  }
  if (digitalRead(breakLight) == HIGH && turnsignalR == false && turnsignalL == false && blinkers == false)
  {
    fill_solid((&leds[45]), 21, CHSV(255, 255, 80));    //fill_solid((&leds[50]), 11, CHSV(255, 255, 80));
    FastLED.show();  
  }  
   if (digitalRead(breakLight) == LOW && turnsignalR == true && turnsignalL == false && blinkers == false)
  {
    fill_solid((&leds[50]), 16, CHSV(255, 255, 255));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  }
  if (digitalRead(breakLight) == HIGH && turnsignalR == true && turnsignalL == false && blinkers == false)
  {
    fill_solid((&leds[50]), 16, CHSV(255, 255, 80));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  } 
   if (digitalRead(breakLight) == LOW && turnsignalR == false && turnsignalL == true && blinkers == false)
  {
    fill_solid((&leds[45]), 16, CHSV(255, 255, 255));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  }
  if (digitalRead(breakLight) == HIGH && turnsignalR == false && turnsignalL == true && blinkers == false)
  {
    fill_solid((&leds[45]), 16, CHSV(255, 255, 80));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  }  
   if (digitalRead(breakLight) == LOW && turnsignalR == false && turnsignalL == false && blinkers == true)
  {
    fill_solid((&leds[50]), 11, CHSV(255, 255, 255));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  }
  if (digitalRead(breakLight) == HIGH && turnsignalR == false && turnsignalL == false && blinkers == true)
  {
    fill_solid((&leds[50]), 11, CHSV(255, 255, 80));     //fill_solid((&leds[50]), 11, CHSV(255, 255, 255));
    FastLED.show();
  } } 
//------------------------------------------front lights-----------------------------------------------//
void frontlights()
{
  if (digitalRead(hBeam) == LOW && digitalRead(lBeam) == HIGH) //digitalRead(bFlash) != && poliisi == false
  {
    headlightCanState = 2;
    digitalWrite(lBeamOut, LOW);
    digitalWrite(hBeamOut, HIGH);
  }
  if (digitalRead(hBeam) == HIGH && digitalRead(lBeam) == LOW)
  {
    headlightCanState = 1;
    digitalWrite(hBeamOut, LOW);
    digitalWrite(lBeamOut, HIGH);
  }
//----pitkien väläytys---//
  if (digitalRead(lBeam) == LOW && digitalRead(hBeam) == LOW)
  {
    headlightCanState = 2;
    digitalWrite(lBeamOut, LOW);
    digitalWrite(hBeamOut, HIGH);
  } }
//----------------------------------horny--------------------------------//
void horny()
{
  if (digitalRead(horn) == LOW)
  {
    digitalWrite(hornOut, HIGH);
  }
  if (digitalRead(horn) == HIGH)
  {
     digitalWrite(hornOut, LOW);  
  } }
//------------------------POLLIISI ASIA-------------------------///

void police()
{
  if (ledCanState == 1)
  {
    poliisi = true;
    EVERY_N_MILLISECONDS(interval)
    {
      for (int i = 0; i < 8; i++)
      {
        fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 255));
        FastLED.show();
        FastLED.delay(40);
        fill_solid(leds, NUM_LEDS, CHSV(255, 255, 0));
        FastLED.show();
        FastLED.delay(40);
      }
      for (int i = 0; i < 3; i++)
      {
        for (int i = 0; i < NUM_LEDS * random8(30); i++) //
        {
          leds[random8(NUM_LEDS)] = CHSV(HUE_BLUE, 255, 255);
          FastLED.show();
          leds[random8(NUM_LEDS - 1)] = CHSV(HUE_RED, 255, 0);
          FastLED.show();
        }
        for (int i = 0; i < 1; i++)
        {
          for (int i = 0; i < NUM_LEDS / 2; i++)
          {
            // fade everything out
            leds.fadeToBlackBy(20);
            // let's set an led value
            leds[i] = CHSV(HUE_BLUE, 255, 255);
            // now, let's first 20 leds to the top 20 leds,
            leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
            FastLED.delay(5);
          }
          for (int i = NUM_LEDS; i > NUM_LEDS / 2; i--)
          {
            // fade everything out
            leds.fadeToBlackBy(20);
          } } } } }
  if (ledCanState != 1)
  {
  poliisi=false;
  } }
////////---------------------------------epilsiasa----------------------------///
void epilepsy()
{
  if (ledCanState == 2)
  {
    epilepsia=true;
    EVERY_N_MILLISECONDS(interval)
    {
      for (int i = 0; i < 3; i++)
      {
        for (int i = 0; i < NUM_LEDS * random8(30); i++)
        {
          leds[random8(NUM_LEDS)] = CHSV(random8(255), 255, 255);
          FastLED.show();
          leds[random8(NUM_LEDS - 1)] = CHSV(HUE_RED, 255, 0);
          FastLED.show();
        }
          for (int i = 0; i < NUM_LEDS / 2; i++)
          {
            // fade everything out
            leds.fadeToBlackBy(20);
            // let's set an led value
            leds[i] = CHSV(random8(255), 255, 255);
            // now, let's first 20 leds to the top 20 leds,
            leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
            FastLED.delay(5);
          }
          for (int i = NUM_LEDS; i > NUM_LEDS / 2; i--)
          {
            // fade everything out
            leds.fadeToBlackBy(20);
          }
          fill_solid((&leds[0]), 110, CHSV(0, 0, 0));
          FastLED.show();
      } } }
  if (ledCanState != 2)
  {
    epilepsia=false;
  } }
//------------------------------------------SETUP-----------------------------------------------//
void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS1);
  FastLED.clear();
  FastLED.show();
  for (int i = 0; i < numOfInputs; i++)
  {
    pinMode(inputPins[i], INPUT_PULLUP);
  }    
  pinMode(lBeamOut, OUTPUT);
  pinMode(hBeamOut, OUTPUT);
  pinMode(hornOut, OUTPUT);
  pinMode(can5vOutput, OUTPUT);
  digitalWrite(lBeamOut, LOW);
  digitalWrite(hBeamOut, LOW);
//---------------------------rasberry CAN-väylän avaus------------------------------------//
delay(1000);
digitalWrite(can5vOutput, HIGH); 
if(Canbus.init(CANSPEED_250))  
  delay(200);
//-----------------------takavalot startup-----------------------------//
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      leds.fadeToBlackBy(40);
      // let's set an led value
      leds[i] = CHSV(255, 255, 160);
      // now, let's first 20 leds to the top 20 leds,
      leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
      FastLED.delay(20);
    }
    for (int i = NUM_LEDS; i > NUM_LEDS / 2; i--)
    {
      // fade everything out
      leds.fadeToBlackBy(40);
      FastLED.delay(10);
    }
    for (int i = 65; i > 44; i--)  //tässä for loopissa pikku bugi (int i = 65; i > 44; i--)  (int i = NUM_LEDS/2; i > 0; i--)
    {
      // let's set an led value
      leds[i] = CHSV(255, 255, 80);
      // now, let's first 20 leds to the top 20 leds,
       leds(55, NUM_LEDS - 1) = leds(55 - 1, 0);     // leds(55, NUM_LEDS - 1) = leds(55 - 1, 0);   leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
      FastLED.delay(20);
    }
    fill_solid((&leds[65]), 1, CHSV(255, 255, 80));    
    FastLED.show();
}
void sendCan() {
      tCAN message;
      message.id = 0x608; //formatted in HEX
      message.header.rtr = 0;
      message.header.length = 8; //formatted in DEC
      message.data[0] = headlightCanState;
      message.data[1] = blinkerCanState;
      //message.data[2] = interlockCanState;
      message.data[3] = 0x0; //formatted in HEX
      message.data[4] = 0x0;
      message.data[5] = 0x0;
      message.data[6] = 0x0;
      message.data[7] = 0x0;
      mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
      mcp2515_send_message(&message);
      delay(40);
}
void readCan() {
   tCAN message;
 if (mcp2515_check_message()) 
 {
    if (mcp2515_get_message(&message)) 
  {
        if(message.id == 0x651)  //uncomment when you want to filter
             {              
               ledCanState = message.data[0];
             }
           } } }
void loop()
{

  sendCan();
  readCan();
  police();
  epilepsy();
  
  if (poliisi and epilepsia == false)
  {
  indicatorLeft();
  indicatorRight();
  Blinkers();
  Breaklights();
  horny();
  frontlights();
  }
  if (poliisi || epilepsia == true)
{
  }    
//-----vilkkujen CAN tiedot----//
  if (turnsignalL == true)
  {
    blinkerCanState = 2;   
    }
  if (turnsignalR == true)
  {
    blinkerCanState = 1;   
    }
    if (turnsignalR == false && turnsignalL == false){
    blinkerCanState = 0;
    } }
