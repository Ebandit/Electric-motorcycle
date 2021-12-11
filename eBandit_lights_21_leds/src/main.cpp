#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 22   //tutustu miksi pitää olla 22 vaikka ledejä on 21??!?!?!?!???
CRGBArray<NUM_LEDS> leds;

/********************************INPUTS********************************************/
#define lBeam 22      //low beam lights input (+yellow / white gnd)
#define hBeam 24      //high beam lights input (+red / white gnd)
#define bFlash 26     //high beam flashing input (+orange / white gnd)
#define horn 28       //horn input (+violet / blue gnd)
#define leftInd 30    //left indicator input (+black / brown gnd)
#define rightInd 32   //right indicator input (+green / brown gnd)
#define breakLight 34 //break light input

const int numOfInputs = 7;
int inputPins[] = {22, 24, 26, 28, 30, 32, 34};

/*********************************OUTPUTS******************************************/

const int lBeamOut = 2; //low beam lights output
const int hBeamOut = 3; //high beam lights output
const int hornOut = 4;  //horn output

/**********************************VARIABLES**************************************/

unsigned char interval = 100; //Desired wait time in seconds (as millis)
unsigned char fade = 100;     //bigger number means faster fade
unsigned char indPixL = 46;  // defines left indicators first led on string
unsigned char indPixR = 16;  // defines right indicators first led on string

//-----------------------------------------Left Indicator-----------------------------------------------//

void indicatorLeft()
{
  if (digitalRead(leftInd) == LOW)
  {

    EVERY_N_MILLISECONDS(interval)
    {
      // fade everything out
      for (int i = 15; i < NUM_LEDS; i++)
      {
        leds[i].fadeToBlackBy(fade);
      }
      // let's set an led value
      leds[indPixL] = CHSV(23, 255, 255);
      //leds[indPixL + 1] = CHSV(23, 255, 255);
      //leds[indPixL + 2] = CHSV(23, 255, 255);
      FastLED.show();
      indPixL++;

      if (indPixL >= NUM_LEDS)
      {
        indPixL = 15;
      }
    }
  }
  if (digitalRead(leftInd) == HIGH)
  {

    fill_solid((&leds[14]), 7, CHSV(255, 255, 80));
    FastLED.show();
    indPixL = 15;
  }
}
//------------------------------------------Right Indicator-----------------------------------------------//
void indicatorRight()
{

  if (digitalRead(rightInd) == LOW)
  {

    EVERY_N_MILLISECONDS(interval)
    {
      for (int i = 7; i > 0; i--)
      {
        leds[i].fadeToBlackBy(fade);
      }
      // let's set an led value
      leds[indPixR] = CHSV(23, 255, 255);
      //leds[indPixR - 1] = CHSV(23, 255, 255);
      //leds[indPixR - 2] = CHSV(23, 255, 255);
      FastLED.show();
      indPixR--;
      if (indPixR <= 1)
      {
        indPixR = 7;
      }
    }
  }
  if (digitalRead(rightInd) == HIGH)
  {
    fill_solid((&leds[0]), 7, CHSV(255, 255, 80));
    FastLED.show();
    indPixR = 7;
  }
}
//------------------------------------------break lights-----------------------------------------------//
void Breaklights()
{
  if (digitalRead(horn) == LOW) 
  {
    fill_solid((&leds[1]), 21, CHSV(255, 255, 255));
    FastLED.show();
  }
  if (digitalRead(horn) == HIGH)
  {
    fill_solid((&leds[1]), 21, CHSV(255, 255, 80));
    FastLED.show();
  }
}
//------------------------------------------front lights-----------------------------------------------//
void frontlights()
{
  if (digitalRead(bFlash) != digitalRead(hBeam))
  {
    digitalWrite(lBeamOut, LOW);
    digitalWrite(hBeamOut, HIGH);
    Serial.println("Pitkät");
  }
  else
  {
    digitalWrite(hBeamOut, LOW);
  }

  if (digitalRead(lBeam) == LOW)
  {
    Serial.println("lyhyet");
    digitalWrite(lBeamOut, HIGH);
    digitalWrite(hBeamOut, LOW);
  }
  else
  {
    digitalWrite(lBeamOut, LOW);
  }
}

void police()
{
  if (digitalRead(horn) == LOW)
  {

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

        for (int i = 0; i < NUM_LEDS * random8(30); i++)
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
          }
        }
      }
    }
  }
}
void epilepsy()
{
  if (digitalRead(horn) == LOW)
  {

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
        
      }
    }
  }
}
//------------------------------------------SETUP-----------------------------------------------//
void setup()
{

  FastLED.addLeds<NEOPIXEL, 50>(leds, NUM_LEDS);
  fill_solid((&leds[1]), 21, CHSV(255, 255, 80));
FastLED.show();

  for (int i = 0; i < numOfInputs; i++)
  {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  pinMode(lBeamOut, OUTPUT);
  pinMode(hBeamOut, OUTPUT);
  pinMode(hornOut, OUTPUT);
  Serial.begin(9600);

    //static uint8_t hue;
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      // fade everything out
      leds.fadeToBlackBy(80);

      // let's set an led value
      leds[i] = CHSV(255, 255, 160);

      // now, let's first 20 leds to the top 20 leds,
      leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
      FastLED.delay(33);
    }


    for (int i = NUM_LEDS; i > NUM_LEDS / 2; i--)
    {
      // fade everything out
      leds.fadeToBlackBy(60);
      FastLED.delay(50);
    }


      for (int i = NUM_LEDS/2; i > 0; i--)
    {
      // let's set an led value
      leds[i] = CHSV(255, 255, 80);

      // now, let's first 20 leds to the top 20 leds,
      leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
      FastLED.delay(30);
    }




  Serial.begin(9600);
}

void loop()
{

  //indicatorLeft();
  //indicatorRight();
  Breaklights();
  frontlights();
 //police();
  //epilepsy();
}
