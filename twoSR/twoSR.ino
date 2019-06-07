/* 
 *  This program demonstrates the writing of data to 16 LEDs from 
 *  two SN74HC595 daisy-chained using SPI. The LEDs count to 2^16 - 1
 *  in binary.
 */

#include <SPI.h>
int latchPin = 8;
int dataPin = 11;
uint16_t data = 0x0001; // two bytes to send to LEDs

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));

}

void loop() {
    digitalWrite(latchPin, LOW);
    SPI.transfer16(0x0001 * pow(2,5));
    Serial.println(0x0001 * pow(2,5));
    digitalWrite(latchPin, HIGH);
    delay(1000); 
}
