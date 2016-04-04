#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      2

#include <SoftwareSerial.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

    // initialize Serial connection for debugging
  Serial.begin(9600);
}

//initialize RGB variables to 0
int r_value = 0;
int g_value = 0;
int b_value = 0;
int count = 0;


// the loop routine runs over and over again forever:
void loop() {

//test to see if global count is in first phase
  if(count >= 0 && count <= 255){
      
    r_value = 255 - (count % 256);
    g_value = (count % 256);
    b_value = 0;
  }
//test to see if global count is in second phase
  if(count > 255 && count <= 511){
    
    r_value = 0;
    g_value = 255 - (count % 256);
    b_value = (count % 256);
  }
//test to see if globabl count is in third phase
  if(count > 511 && count <= 767){
    
    r_value = (count % 256);
    g_value = 0;
    b_value = 255 - (count % 256);
  }
  
  delay(10);               // wait for 10 milliseconds

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r_value,g_value,b_value)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
  }

  //global count
  count = (count + 1) % 767;
}

