// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include <FastLED.h>
#include "font.h"


///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 80

// Data pin that led data will be written out over
#define DATA_PIN 3

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

CRGB dis[16][5];

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(1000);

      // Uncomment one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      FastLED.setBrightness(10);

      Serial.begin(9600);      // open the serial port at 9600 bps:    
}

void all_off() {
  for(int i =0; i<16; i++)
  {
    for(int z=0; z<5; z++)
    {
      dis[i][z] = CRGB::Black;
    }
  }
}

void refresh() {
  for( int x=0; x<16; x++)
  {
    leds[x] = dis[x][0];
    leds[31-x] = dis[x][1];
    leds[32+x] = dis[x][2];
    leds[63-x] = dis[x][3];
    leds[64+x] = dis[x][4];
  }
}

void write_char(int location, char c)
{
  char z[5];

  int ci = (int) c - 32;
  //Serial.print(ci);

  for(int y=0; y<5; y++)
  {
    char c = __font_bitmap__[ci*6+y];
    //c = c >> 5;
    //c = c & 7;
    z[y] = c;
  }
  //int z;
  for( int y=0; y<5; y++)
  {
    for( int i=0; i<8; i++)
    {  
      if( z[y] & ((char)1) << i )
      {
        if(7-i+location > 0 && 7-i+location < 16 )
          dis[7-i+location][y] = CRGB::White;
        //Serial.print("1");
      }
      else
      {
        //dis[7-i+location][y] = CRGB::Black;
        //Serial.print("0");
      } 
    }
  }
}

char string[] = "I LOVE YOU";

void loop() {

for(int x =16; x>=((int)sizeof(string)-1) * -4; x--)
{
  all_off();

  //Serial.print(x);
  //Serial.print("\n");
  for(int q=0; q<sizeof(string)-1; q++)
  {
    write_char(x+q*4, string[q]);
  }


  //all_off();
      refresh();
          FastLED.show();
            delay(200);
}
   
}
