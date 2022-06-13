// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const int array_laenge = 300;
float buffer_array[array_laenge];
int array_index = 0;
bool start_init = false;

void setup(void) {

     
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
    for(int i=0; i < array_laenge; i++){
      Serial.print(buffer_array[i]);
      Serial.print(",");
    }
    Serial.println("");
    for(int i=0; i < array_laenge; i++){
      buffer_array[i] = 0;
    }
    start_init = false;
    array_index = 0;
  }
 //Serial.println(differenz);
  
}
