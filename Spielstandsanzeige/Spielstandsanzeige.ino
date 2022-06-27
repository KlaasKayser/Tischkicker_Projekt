// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 20 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

const byte interruptPin = 2;        //2 ist der pin an der Lichtschranke
//const byte interruptPin2 = 3;


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(interruptPin, INPUT_PULLUP);          //_PULLUP setzt Pin auf 5V
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), tor, RISING);
  //attachInterrupt(digitalPinToInterrupt(interruptPin2), tor2, RISING);
}

int y=0;
int z=0;
float zeitseittor = 1000;

void loop() {
  leuchten(y);
  //Serial.println(y);
  //Serial.println(digitalRead(interruptPin));
  //leuchten2(z);
}

void tor()
{
  if(y<10 && (millis()-zeitseittor)>= 2000){
    y++;
    zeitseittor = millis();
    
  }
  
}

void tor2()
{
  if(z<10){
    z++;
  }
}

void leuchten(int a) {
  for(int l=0; l<10; l++) {
    pixels.setPixelColor(l, pixels.Color(0, 0, 0));
  }
  for(int i=a-1; i>=0; i=i-1) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
  }
pixels.show();
}

void leuchten2(int b) {
  for(int x=10; x<20; x++) {
    pixels.setPixelColor(x, pixels.Color(0, 0, 0));
  }
  for(int f=b+9; f>=10; f=f-1) {
    pixels.setPixelColor(f, pixels.Color(0, 0, 255));
  }
pixels.show();
}
