/* 
 *  This program demonstrates the writing of data to 16 LEDs from 
 *  two SN74HC595 daisy-chained using SPI. The LEDs count to 2^16 - 1
 *  in binary.
 */

#include <SPI.h>
int latchPin = 8;
int dataPin = 11;
uint16_t data = 0x5224; // two bytes to send to LEDs

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));

}

void loop() {
  for (data = 1; data < 0xFFFF; data++) {
    digitalWrite(latchPin, LOW);
    SPI.transfer16(data);
    digitalWrite(latchPin, HIGH);
    delay(1000);  
  }
}
