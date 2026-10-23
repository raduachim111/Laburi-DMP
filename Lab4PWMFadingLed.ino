#include "pitches.h"  

int ledPins[] = {9,10,11};
int nrLeds = 3;
int step = 10;
int puls = 0;



void setup() {
  for(int i = 0; i < nrLeds; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

}

void loop() {
  for(int i = 0 ; i < nrLeds ; i++ )
  {
    analogWrite(ledPins[i], puls);
  }
  puls = puls + step;
  if(puls <= 0 || puls >= 255)
  {
    step =- step;
  }
  delay(30);
}