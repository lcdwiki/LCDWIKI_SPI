This fork should work on AVR, Due, Zero, M0, Teensy3.x, STM32, ESP32
ESP8266 will timeout without lots of yield() calls.

Select ESP8266=160MHz and set SPI=27MHz to reduce timeout risk
I suspect SSD1283A might not run with fast SPI clock speeds
Bit-bang has no chance on ESP8266.

Life is less frustrating with Uno, Zero, Due, ESP32, Nucleo

Please report whether SSD1283A display is worth supporting e.g. wide angle, daylight, ...

I have not altered the original examples.
I have added LCDWIKI_XBM.ino example.   Please study the comments

This is a library for the SPI lcd display.
This library support these lcd controller:
ILI9325 
ILI9328 
ILI9341 
HX8357D 
HX8347G 
HX8347I 
ILI9486 
ST7735S 
SSD1283A

Check out the file of LCDWIKI SPI lib Requirements for our tutorials and wiring diagrams.

These displays use spi bus to communicate, 5 pins are required to interface (MISO is no need).

Basic functionally of this library was origianlly based on the demo-code of Adafruit GFX lib and Adafruit SPITFT lib.  

MIT license, all text above must be included in any redistribution

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder LCDWIKI_SPI. Check that the LCDWIKI_SPI folder contains LCDWIKI_SPI.cpp and LCDWIKI_SPI.h

Place the LCDWIKI_SPI library folder your <arduinosketchfolder>/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE

Also requires the LCDWIKI_GUI library for Arduino. 
https://github.com/lcdwiki/LCDWIKI_gui