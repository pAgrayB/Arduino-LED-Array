# LED-Array
This repository serves to docuement how to use and the power design of a 16-LED long array controlled by an Arduino Uno. A single GPIO port is expanded using two SN74HC595N shift-registers and the SPI Arduino Library. 

## How to Use Patterns.ino
1. Open Patterns.ino in Arduino IDE
2. Find the following on line 28:
  <br> `typedef enum Patterns {train, love, woop, bounce, MAX_PATS} pattern_t;`
3. Change pattern to desired choice on line 32:
  <br> `pattern_t current = bounce;`
4. Compile and upload to Uno.

## Power Design
