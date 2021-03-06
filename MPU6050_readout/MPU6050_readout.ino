// Basic demo for accelerometer readings from Adafruit MPU6050

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
bool start_init = false;
int tora = 0;
int torb = 0;
void setup(void) {

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

     Serial.println("A");

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

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  //Serial.println(atan(abs(a.acceleration.x/a.acceleration.z))*180/3.141) ;

  buffer_array[array_index] = a.acceleration.y;

  if(array_index < array_laenge){
    array_index++;
  }else{
    array_index = 0;
    start_init = true;
  }


  float minVal = 10000;
  float maxVal = -10000;

  for (int i = 0; i < array_laenge; i++) {
    if (buffer_array[i] > maxVal) {
       maxVal = buffer_array[i];
    }
    if (buffer_array[i] < minVal) {
       minVal = buffer_array[i];
    }
  }


 float differenz;
 differenz = maxVal-minVal;


  if(differenz > 11 && start_init){
  tora++;
  //Serial.println(tora);
  //Serial.println(differenz);

    for(int i=0; i < array_laenge; i++){
      //Serial.println(buffer_array[i]);
    }

   
    for(int i=0; i < array_laenge; i++){
      buffer_array[i] = a.acceleration.y;
    }
    start_init = false;
    array_index = 0;

    int x = map(differenz, 11, 100, 1, 10);
    //Serial.println(differenz);
    blinken(x);
    
  }
 //Serial.println(differenz);
  
}

void blinken(int a) {
  for(int l=0; l<10; l++) {
    pixels.setPixelColor(l, pixels.Color(0, 0, 0));
  }
  for(int i=0; i<a; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
    pixels.show();
    delay(300);    
  }
}

void blinken2(int b) {
  for(int x=10; x<20; x++) {
    pixels.setPixelColor(x, pixels.Color(0, 0, 0));
  }
  for(int f=10; f<b+10; f++) {
    pixels.setPixelColor(f, pixels.Color(0, 0, 255));
    pixels.show();
    delay(300);
  }
pixels.show();
}
