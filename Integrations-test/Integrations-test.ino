
int loopTime = 0;
int loopStartTime = 0;

double integratedValue = 0;
double lastIntegral = 0;

bool flag = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  loopStartTime = int(millis());

  int sensorValue = analogRead(A0);

  flag = sensorValue > 50;
  if(flag){
      integratedValue += double(loopTime)*double(sensorValue);
  }else{
    if(integratedValue > 0){
      lastIntegral = integratedValue;
    }
      integratedValue = 0;
  }


  Serial.print(millis());
  Serial.print(" : ");
  Serial.print(loopTime);
  Serial.print(" : ");
  Serial.print(sensorValue);
  Serial.print(" : ");
  Serial.print(integratedValue);
  Serial.print(" : ");
  Serial.print(lastIntegral);
  Serial.println();

  loopTime = int(millis()) - int(loopStartTime);
  //delay(500);
  
}
