/* Here is an example sketch to show XBM bitmap
 * and regular Adafruit bitmap
 * it should work with ESP8266 @ 80MHz and SPI=4MHz
 * 
 * ALL THE STANDARD EXAMPLES REQUIRE ESP8266=160MHz, SPI=27MHz 
 * otherwise you must add yield() to all slow functions
 * 
 * Your SSD1283 might need slower SPI e.g. 16MHz, 24MHz
 * It is easy to set SPI in LCDWIKI_SPI.cpp
 * in beginTransaction() statement
 * 
 * My ST7735 display is 128x160
 * your SSD1283 is 130x130 i.e. similar small size
 * 
 * library is so inefficient, ESP8266 will timeout on 176x220 or 240x320
 */

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

// I tested this with ST7735S display using HW SPI on ESP8266
LCDWIKI_SPI mylcd(ST7735S ,D10,D9, D8,-1); //hardware spi,cs,cd,reset,led 

//Sample constructors e.g. using HW SPI pins
//LCDWIKI_SPI mylcd(MODEL,   CS,CD,RST,LED); 
//LCDWIKI_SPI mylcd(ILI9341, 10, 9,  8, -1);  //HWSPI
//LCDWIKI_SPI mylcd(ILI9341,  5,13, 12, -1);  //HWSPI ESP32
//LCDWIKI_SPI mylcd(ILI9341,D10,D9, D8, -1);  //HWSPI ESP8266

//Sample software SPI constructors e.g. using random pins
//LCDWIKI_SPI mylcd(MODEL,   CS, DC,MISO,MOSI,RST,SCK,LED); //Uno, Nucleo
//LCDWIKI_SPI mylcd(ILI9341, 10,  9,  12,  11,  8, 13, -1); //Uno, Nucleo
//LCDWIKI_SPI mylcd(ILI9341, 10,  9,  22,  23,  8, 24, -1); //Zero
//LCDWIKI_SPI mylcd(ILI9341, 10,  9,  18,  21,  8, 20, -1); //M0 Pro
//LCDWIKI_SPI mylcd(ILI9341, 10,  9,  74,  75,  8, 76, -1); //Due
//LCDWIKI_SPI mylcd(ILI9341,  5, 13,  19,  23, 12, 18, -1); //ESP32
//LCDWIKI_SPI mylcd(ILI9341,D10, D9, D12, D11, D8,D13, -1); //ESP8266 Soft SPI is disabled in LCDWIKI_SPI.cpp
//LCDWIKI_SPI mylcd(SSD1283A,A5, A3,  -1,  A2, A4, A1, A3); //software spi,model,cs,cd,miso,mosi,reset,clk,led


#include "xbm_mono.h"       //1024 bytes for 128x64x1 truck
#include "bitmap_mono.h"
#define RED   0xF800
#define GREEN 0x07E0
#define BLUE  0x001F
#define BLACK 0x0000

// Helper function to render bitmaps from PROGMEM
// plots pixels left to right, then goes to next row
// XBM format are lsb first
// regular bitmaps are msb first
// most Font bitmaps are msb first
// FreeFonts store contiguous bits
// XBM align a fresh row on a byte boundary
// Windows BMP aligns on a uint32_t boundary
//
void drawABitmap(int x, int y, const uint8_t *bmp, int w, int h, uint16_t color, uint16_t bg, bool is_xbm = false, uint8_t pad = 7)
{
    int yy, xx;
    uint8_t first = 1, RVS = pad & 0x80, MASK = is_xbm ? 0x01 : 0x80;
    uint16_t pixel;
    pad &= 31;
    uint16_t wid = (w + pad) & ~pad;                    //bits per row
    mylcd.Set_Addr_Window(x, y, x + w - 1, y + h - 1);
    for (yy = 0; yy < h; yy++) {
        uint32_t ofs = (RVS ? (h - yy - 1) : yy) * wid; //bit offset
        const uint8_t *p = bmp + (ofs >> 3);            //flash address
        uint8_t mask = MASK;
        if (is_xbm) mask <<= (ofs & 7);
        else mask >>= (ofs & 7);
        uint8_t c = pgm_read_byte(p++);
        for (xx = 0; xx < w; xx++) {
            if (mask == 0) {
                c = pgm_read_byte(p++);
                mask = MASK;
            }
            pixel = (c & mask) ? color : bg;
            mylcd.Push_Any_Color(&pixel, 1, first, 0);
            first = 0;
            if (is_xbm) mask <<= 1;
            else mask >>= 1;
        }
    }
    mylcd.Set_Addr_Window(0, 0, mylcd.Get_Width() - 1, mylcd.Get_Height() - 1);
}

void setup() 
{
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);  
  mylcd.Set_Rotation(1);  //LANDSCAPE
}

#define drawBitmap(x, y, bmp, w, h, fg, bg) drawABitmap(x, y, bmp, w, h, fg, bg, false) 
#define drawXBitmap(x, y, xbm, w, h, fg, bg) drawABitmap(x, y, xbm, w, h, fg, bg, true) 

void loop() 
{
    mylcd.Fill_Screen(BLACK);
    drawXBitmap(0, 0, truck_128x64_xbm, 128, 64, BLACK, BLUE);     
    drawXBitmap(1, 64, tractor2_128x64_xbm, 128, 64, BLACK, RED);     
    delay(5000);
    drawBitmap(2, 32, tractor_128x64, 128, 64, BLACK, GREEN);     
    delay(5000);
}
