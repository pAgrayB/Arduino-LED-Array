//**************************************************************//
//  Name    : sample_hello-world                             
//  Author  : Patrick Graybeal
//  Date    : 2 Jun 2019   
//  Modified: 2 Jun 2019                                 
//  Version : 1.0                                             
//  Notes   : Code for simulating ball dropped from rest at a height of 8*h,
//            where h is the space between LEDs in meters
//****************************************************************

//Pin connected to RCLK of SN74HC595N
int latchPin = 8;
//Pin connected to SRCLK of SN74HC595N
int clockPin = 12;
////Pin connected to SER of SN74HC595N
int dataPin = 11;

// Value to write to shift register
int value = 1;
// Operation to perform on value
bool op = true;

// Height between LEDs (m)
float h = 1.5;

// Initial velocity is 0 (m/s)
float vel = 0;
// Time between latches (sec)
float time = sqrt((2 * h)/9.81);


void updateMovement() {

    if (op) { // Falling
      value *= 2; // shift one LED left
      vel = vel - (9.81 * time); //update velocity
      time = ( vel + sqrt(pow(vel,2) + 19.62 * h) ) / 9.81; //update LED timing
    } else { // Rising
      value /= 2; // shift one LED right
      vel = vel - (9.81 * time); //update velocity
      time = ( -1 * vel + sqrt(pow(vel,2) - 19.62 * h) ) / (-9.81); //update LED timing
    }
}

void updateDirection() {

      if (value == 128) { // Left-most LED is reached
      op = false; // start rising
      vel = -1 * vel; // switch velocity direction for calculations
    } else if (value == 1){ // Right-most LED is reached
      op = true; // start falling
      vel = 0; // reset velocity to 0 (avoids rounding errors)
      time = sqrt((2 * h)/9.81); // reset timing to initially calculated (avoid rounding errors)
    }
}


void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
    
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    
    // shift out the bits:
    shiftOut(dataPin, clockPin, LSBFIRST, value);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(time * 1000); // delay needs msecs  

    updateMovement();
    updateDirection();    
}
