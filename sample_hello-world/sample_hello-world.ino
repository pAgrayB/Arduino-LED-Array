//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : (adpated from) Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 2 Jun 2019   
//  Modified: 2 Jun 2019                                 
//  Version : 1.0                                             
//  Notes   : Code for using a SN74HC595N Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to RCLK of SN74HC595N
int latchPin = 8;
//Pin connected to SRCLK of SN74HC595N
int clockPin = 12;
////Pin connected to SER of SN74HC595N
int dataPin = 11;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(100);
  }
}
