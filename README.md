
# blinker bluetooth light

With this circuit we are able to control a 8x8 matrix led using

the max7219 chip to send the data.

* w = up arrow
* s = down arrow
* a = left arrow
* d = right arrow
* h = heart
* x = blinker stop

## circuit:
* Arduino board
* 8x8 matrix
* max7219 led display driver
* hc-05 or hc-06 serial bluetooth module
* 5v power source

## connections:
pin 12 is connected to the din
pin 11 is connected to the CLK
pin 10 is connected to cs
pin 0 is connected to TX from bluetooth
pin 1 is connected to RX from bluetooth

Yeffri J. Salazar
Xibalba Hackerspace, August 2019.
