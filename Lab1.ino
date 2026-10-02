// Read status of buttons and display it on LEDs connected to 
//PORTA 
// Variables for reading the status of the buttons connected 
//to the  
// digital pins 4, 5, 6, 7 
int b1; 
int b2; 
int b3; 
int b4; 
int count = 0;
// variable for the LED status 
unsigned char stat = 0; 
void setup() { 
// configure digital pins as inputs 
pinMode(4, INPUT_PULLUP); 
pinMode(5, INPUT_PULLUP); 
pinMode(6, INPUT_PULLUP); 
pinMode(7, INPUT_PULLUP); 
// activate PORTA, as output,  
DDRA = 0b11111111; 
} 
void loop() { 
// read BTNs status  
b1 = digitalRead(4);
b2 = digitalRead(5); 
b3 = digitalRead(6); 
b4 = digitalRead(7); 
// combine result: each LED is controlled by a button.  

if( b1 == HIGH)//Some buttons are //duplicated 
{
stat = (1 << count);
PORTA = stat;
delay(250);

PORTA=0x00;
delay(50);

count++;

if (count > 3)
   count = 0;
}
else
{

stat = (1 << count);
PORTA = stat;
delay(250);

PORTA=0x00;
delay(50);

count--;
if(count < 0)
   count = 3;
}
}
