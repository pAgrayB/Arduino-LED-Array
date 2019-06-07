#include <SPI.h>
int latchPin = 8;
int dataPin = 11;
int LED = 0;
int i = 0;
int j = 15;
unsigned long enterTime = 0;


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));
}

void loop() {

  enterTime = millis();
  while (millis() - enterTime < 200) { // exit after 200ms
    turnOn(i);
    delay(1);
    turnOn(j);
    delay(1);
  }
  
  i++;
  j--;

  counterCheck();
}

void turnOnMany (byte packed) {
  


  
}


void turnOn (int LED_index) {

  if (LED_index < 0 || LED_index >= 16) {
    return;
  }

  // value = 2^LED_index afterwards
  int i = 0;
  int value = 1;
  while (i < LED_index) {
    value *= 2;
    i++;
  }
  
  digitalWrite(latchPin, LOW);
  SPI.transfer16(value);
  digitalWrite(latchPin, HIGH);
}

void counterCheck () {
  if (i == 16) {
    i = 0;
  }
  if (j == -1) {
    j = 15;
  }
}
