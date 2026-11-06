// CODE FOR RECEIVER

#include <LiquidCrystal.h>  // include LCD library
#include <Wire.h>           // include I2C library

// LCD WITH BUTTONS
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// LCD WITHOUT BUTTONS
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

String inputString = "";

void setup() {
  // Start I2C receiver at address 9
  Serial.begin(9600);  // implicit serial frame format
  Wire.begin(9);

  // attach a function to be called when we receive
  // something on the I2C bus
  Wire.onReceive(receiveEvent);

  lcd.begin(16, 2);
  
}

void receiveEvent(int bytes) {
  while(Wire.available()){
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void loop() {
}

// CODE FOR TRANSMITTER

#include <LiquidCrystal.h>  // include LCD library
#include <Wire.h>           // include I2C library

// LCD WITH BUTTONS
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// LCD WITHOUT BUTTONS
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
String InputString = "";
boolean StringComplete = false;
int x = 0;

void setup() {
  // Open I2C bus as transmitter
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  InputString.reserve(200);
}
void serialEvent() {
  while (Serial.available()) {
    // read the new received byte
    char inChar = (char)Serial.read();

    // check if new line character has been received; if
    // not, add it to the string
    // we do not add new line in input string since it
    // will show an extra character in the LCD
    if (inChar != '\n')
      InputString += inChar;

    // diff the receive character is new line, set the flag
    // so that the loop will know to display
    // the received data
    if (inChar == '\n') {
      StringComplete = true;
    }
  }
}
void loop() {
  if(StringComplete)
  {
  Wire.beginTransmission(9);  // transmit to device #9
  Wire.write(InputString.c_str());        // transmit x
  Wire.endTransmission();     // stop transmission       
  InputString = "";
  StringComplete = false;
  }
}
