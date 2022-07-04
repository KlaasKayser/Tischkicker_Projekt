// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
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
Adafruit_MPU6050 mpu;

const int array_laenge = 300;
float buffer_array[array_laenge];
int array_index = 0;
int tora = 0;
int torb = 0;
const byte interruptPin = 2;        //2 ist der pin an der Lichtschranke
//const byte interruptPin2 = 3;
sensors_event_t a, g, temp;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }
  pinMode(interruptPin, INPUT_PULLUP);          //_PULLUP setzt Pin auf 5V
  //attachInterrupt(digitalPinToInterrupt(interruptPin), tor, RISING);
    // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  for(int i=0; i < array_laenge; i++){
    buffer_array[i] = 0;
    Serial.println(i);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("aaaaaa");
  delay(100);
}

float zeitseittor = 1000;
float beschleunigung = 0;

void loop() {

  if(tora<10 && (millis()-zeitseittor)>= 2000 && !digitalRead(interruptPin)){
    Serial.println("Tor Gefallen");
    tora++;
    zeitseittor = millis();
    Serial.println("Sensor nimmt auf");

    float minVal = 10000;
    float maxVal = -10000;
    while(millis()<zeitseittor+4000){
      /* Get new sensor events with the readings */
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      beschleunigung = a.acceleration.y;
        if (beschleunigung > maxVal) {
           maxVal = beschleunigung;
        }
        if (beschleunigung < minVal) {
           minVal = beschleunigung;
        }
      }
      float differenz = maxVal-minVal;
    
    Serial.println("Differenz wird bestimmt");
    int x = map(differenz, 11, 100, 1, 10);
    Serial.println(differenz);
    //blinken(x);
    leuchten(tora);
  }
  
}

void tor()
{

  
}



void tor2()
{
  if(torb<10){
    torb++;
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
