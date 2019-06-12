#include <SPI.h>

#define initial 0b1110000011100000
#define final 0b0000011100000111
#define wrap 0b1000000000000000
#define first 0b1000001110000011
#define second 0b1100000111000001

int latchPin = 8;
int dataPin = 11;

int LED = 0;
int i = 0;
int j = 15;
unsigned long enterTime = 0;
uint16_t value = 0b1110000011100000;
uint16_t woopValue = 0b0111100000000000;
char op = 'r';

// Global variables for "bounce" pattern
uint16_t value2 = 1;
bool op2 = true; // Operation to perform on value
float h = 2; // Height between LEDs (m)
float vel = 0; // Initial velocity is 0 (m/s)
float time = sqrt((2 * h)/9.81); // Time between latches (sec)
// End variables for "bounce" pattern

typedef enum Patterns {train, love, woop, bounce, MAX_PATS} pattern_t;

//
// SELECT PATTERN HERE
pattern_t current = bounce;
// SELECT PATTERN HERE
//

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));
}

void loop() {

  switch (current)
  {
    case train:
      trainPattern();
      break;
  
    case love:
      bitterSweetPattern();
      break;

    case woop:
      woopPattern();
      break;

    case bounce:
      bouncePattern();
      break;

    default:
      turnOnMany(0b1001100110011001);
      break;
  }
  

}

// Runs each pattern function in the main
// loop of the arduino ALONE for the effect

void bouncePattern () {

    // take the (SS) latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    
    // shift out the bits:
    SPI.transfer16(value2);

    //take the (SS) latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(time * 1000); // delay needs msecs  

    updateMovement();
    updateDirection();
}

void updateMovement() {

    if (op2) { // Falling
      value2 *= 2; // shift one LED left
      vel = vel - (9.81 * time); //update velocity
      time = ( vel + sqrt(pow(vel,2) + 19.62 * h) ) / 9.81; //update LED timing
    } else { // Rising
      value2 /= 2; // shift one LED right
      vel = vel - (9.81 * time); //update velocity
      time = ( -1 * vel + sqrt(pow(vel,2) - 19.62 * h) ) / (-9.81); //update LED timing
    }
}

void updateDirection() {

      if (value2 == 32768) { // Left-most LED is reached
      op2 = false; // start rising
      vel = -1 * vel; // switch velocity direction for calculations
    } else if (value2 == 1){ // Right-most LED is reached
      op2 = true; // start falling
      vel = 0; // reset velocity to 0 (avoids rounding errors)
      time = sqrt((2 * h)/9.81); // reset timing to initially calculated (avoid rounding errors)
    }
}

void woopPattern () {

  turnOnMany(woopValue);
  op = dir(woopValue, op);
  if (op == 'r') {
    woopValue >>= 1;
  } else if (op == 'l') {
    woopValue <<= 1;
  }

  delay(50);
}

char dir(uint16_t check, char op) {
  char returnOp = 'l';
  if (check == 0b1111000000000000) {
    return returnOp = 'r';
  } else if (check == 0b0000000000001111) {
    return returnOp = 'l';
  } else {
    return op;
  }
}


void trainPattern () { 
  
  turnOnMany(value);

  // Shift the train to the right
  value = value >> 1;

  // When the train reaches the end,
  // perform the wrap around light sequence.
  if (value == final >> 1) {
    value = first;
    delay(500);
    turnOnMany(value);
    delay(500);

    value = second;
    turnOnMany(value);
    delay(500);

    value = initial;
    turnOnMany(value);
    delay(500);

    value = value >> 1;
    
  } else {
    delay(500);
  }
}

void bitterSweetPattern () {
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

// Helper function of bitterSweetPattern
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

// Helper function of bitterSweetPattern
void counterCheck () {
  if (i == 16) {
    i = 0;
  }
  if (j == -1) {
    j = 15;
  }
}

// General helper function
void turnOnMany (uint16_t packed) {

  digitalWrite(latchPin, LOW);
  SPI.transfer16(packed);
  digitalWrite(latchPin, HIGH);
}
