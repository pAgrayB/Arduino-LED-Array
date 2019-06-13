# LED-Array
This repository serves to document the design of a 16-LED long array controlled by an Arduino Uno. A single GPIO port is expanded using two SN74HC595N shift-registers and the SPI Arduino Library. 

![LED-ARRAY](https://github.com/pAgrayB/LED-ARRAY/blob/master/LED-ARRAY.JPG)

## How to Use Patterns.ino
1. Open Patterns.ino in Arduino IDE
2. Find the following on line 28:
  <br> `typedef enum Patterns {train, love, woop, bounce, MAX_PATS} pattern_t;`
3. Change pattern to desired choice on line 32:
  <br> `pattern_t current = bounce;`
4. Compile and upload to Uno.

## Future Improvements
1. Clean and better document code.
2. Use different LED power design, such as driving array with constant current sources to avoid waste in power in resistors.
