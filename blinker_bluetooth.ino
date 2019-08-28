/*
   blinker bluetooth light
   With this circuit we are able to control a 8x8 matrix led using
   the max7219 chip to send the data.
   w = up arrow
   s = down arrow
   a = left arrow
   d = right arrow
   h = heart
   x = blinker stop
  circuit:
   Arduino board
   8x8 matrix
   max7219 led display driver
   hc-05 or hc-06 serial bluetooth module
   5v power source

  connections:
   pin 12 is connected to the din
   pin 11 is connected to the CLK
   pin 10 is connected to cs
   pin 0 is connected to TX from bluetooth
   pin 1 is connected to RX from bluetooth

   Yeffri J. Salazar
   Xibalba Hackerspace, August 2019.
*/
#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1);

int delaytime = 500; // delay between change the blinker stop signs

const byte IMAGES[][8] = {
  {
    B00000000,
    B00001000,
    B00011100,
    B00111110,
    B01111111,
    B00011100,
    B00011100,
    B00011100
  }, {
    B00000000,
    B00011100,
    B00011100,
    B00011100,
    B01111111,
    B00111110,
    B00011100,
    B00001000
  }, {
    B00000000,
    B00001000,
    B00001100,
    B01111110,
    B01111111,
    B01111110,
    B00001100,
    B00001000
  }, {
    B00000000,
    B00001000,
    B00011000,
    B00111111,
    B01111111,
    B00111111,
    B00011000,
    B00001000
  }, {
    B00000000,
    B00100010,
    B01110111,
    B01111111,
    B01111111,
    B00111110,
    B00011100,
    B00001000
  }, {
    B00000000,
    B00000000,
    B00011100,
    B00100010,
    B00100010,
    B00100010,
    B00011100,
    B00000000
  }, {
    B11111111,
    B11111111,
    B11100011,
    B11011101,
    B11011101,
    B11011101,
    B11100011,
    B11111111
  }
};

void displayImage(const byte* image) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(image[i], 7 - j));
    }
  }
}


void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
  Serial.begin(9600);

}

void loop() {
  while (Serial.available() > 0 ) {
    char a = char(Serial.read());
    lc.shutdown(0, false);
    if (a == 'a') {
      displayImage(IMAGES[0]);
    } else if (a == 'w') {
      displayImage(IMAGES[0]);
    } else if (a == 's') {
      displayImage(IMAGES[1]);
    } else if (a == 'd') {
      displayImage(IMAGES[2]);
    } else if (a == 'a') {
      displayImage(IMAGES[3]);
    } else if (a == 'h') {
      displayImage(IMAGES[4]);
    } else if (a == 'x') {
      for (int i = 0; i < 10; i++) {
        displayImage(IMAGES[5]);
        delay(delaytime);
        displayImage(IMAGES[6]);
        delay(delaytime);
      }
    }
    delay(1000);
    lc.shutdown(0, true);
  }
}
