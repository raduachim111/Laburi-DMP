#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

volatile bool isRunning = false;
unsigned long lastResetTime = 0;
unsigned long timeBeforePause = 0;
unsigned long time;

void setup()
{

  lcd.begin(16, 2);
  lcd.print("Timer: ");




  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(20), timerStartStop,RISING);
  attachInterrupt(digitalPinToInterrupt(21), timerReset,RISING);
}

void loop(){
   if(isRunning)
   {
     time = (millis() - lastResetTime + timeBeforePause) / 1000;

   }
   else
   {
     time = timeBeforePause / 1000;
   }
   lcd.setCursor(0,1);
   lcd.print(time);
   lcd.print("s   ");
}

void timerStartStop()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if(!isRunning)
  {
    lastResetTime = millis();
    isRunning = true;
  }
  else
  {
    isRunning = false;
    timeBeforePause = timeBeforePause + (millis() - lastResetTime);
  }
  lastInterruptTime = interruptTime;
}

void timerReset()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  isRunning = false;
  timeBeforePause = 0;
  lastResetTime = millis();
  lastInterruptTime = interruptTime;
}