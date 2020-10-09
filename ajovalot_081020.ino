
int blinkRightInput = 4;
int blinkRightOutput = 52;

int blinkLeftInput = 5;
int blinkLeftOutput = 51;

int driveShortInput = 7 ;
int driveShortOutput= 49;

int driveLongInput = 6;
int driveLongOutput = 50;

int hornInput = 3;
int hornOutput = 53; 

int Time; // Delay(ms)*Time= ms
int BlinkOn = 20;
int Delay(1);

int latchPin = 10;
int clockPin=9;
int dataPin=8;
byte leds= 0;
unsigned long BlinkString;
unsigned long BlinkTime;
int BlinkRate= 100;
int i; 
int j;

void setup() {

  pinMode(blinkRightOutput, OUTPUT);
  pinMode(blinkLeftOutput, OUTPUT);
  pinMode(driveShortOutput, OUTPUT);
  pinMode(driveLongOutput, OUTPUT);
  pinMode(hornOutput, OUTPUT);

  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  
  
}

void loop() {
  BlinkString = millis();
  
  updateShiftRegister();
/************************************************************************************************///vilkku oikea
if(digitalRead(blinkRightInput)==HIGH){
  
  digitalWrite(blinkLeftOutput,LOW);
  
  if(Time<=BlinkOn){
    bitSet(leds,j);
    updateShiftRegister();
    bitSet(leds, j-1);
    updateShiftRegister();
    bitSet(leds, j-2);
    updateShiftRegister();
    leds=0;    
    digitalWrite(blinkRightOutput,HIGH);
    } 

  if(Time>BlinkOn){
    digitalWrite(blinkRightOutput,LOW);
    }   
  } 
/************************************************************************************************///vilkku vasen
if(digitalRead(blinkLeftInput)==HIGH){
  
  digitalWrite(blinkRightOutput,LOW);
  
  if(Time<=BlinkOn){
    
    bitSet(leds,i);
    updateShiftRegister();
    bitSet(leds, i-1);
    updateShiftRegister();
    bitSet(leds, i-2);
    updateShiftRegister();

    leds=0;
    digitalWrite(blinkLeftOutput,HIGH);
    }
    if(Time>BlinkOn){
      digitalWrite(blinkLeftOutput,LOW);
    } 
    
  

   
  }

/************************************************************************************************/
if((digitalRead(blinkLeftInput)==LOW)&&(digitalRead(blinkRightInput)==LOW)){
  digitalWrite(blinkRightOutput,LOW);
  digitalWrite(blinkLeftOutput,LOW);

}

/************************************************************************************************///Lyhyet
if(digitalRead(driveShortInput)==HIGH){
  digitalWrite(driveShortOutput,HIGH);


} 
else{
  digitalWrite(driveShortOutput,LOW);
}

/************************************************************************************************///Pitkät
if(digitalRead(driveLongInput)==HIGH){
  digitalWrite(driveLongOutput,HIGH);
} 
else{
  digitalWrite(driveLongOutput,LOW);
}
/************************************************************************************************///töötti
  if(digitalRead(hornInput)==HIGH){
    digitalWrite(hornOutput,HIGH);

  }
 else{
  digitalWrite(hornOutput,LOW);
 }

/************************************************************************************************/

//leds = 0;
delay(Delay);
Time ++;
if(Time>BlinkOn*2){
Time= 0;
j--;
if(j<=0){
  j=10;
  leds=0;
}
i++;
if(i>10){
  i=0;
  leds=0;
}
  }

}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin,HIGH);
}
