// Reading const
#define SLAVE_ADDR 9
#include <Wire.h>
int analogPin = A3;
double val = 0.0; // store the read value
double constRes = 6660.0;
double totalVolt = 5.0;
double b = 4220;
double r1, temp;
double tempUncertainty = 0.6;

// Writing const
int transistorBase = 3;
double targetTemp = 29;

double celsToKelvin(double cels) {
  return cels + 273.15;
}

double kelvinToCels(double kelv){
  return kelv - 273.15;
}

void controlTemp(double curTemp, double targetTemp){
  if (curTemp < targetTemp - 0.5){
    digitalWrite(transistorBase, HIGH);
    Serial.println("Heating up");
    Wire.write("Heating up");
  } else {
    digitalWrite(transistorBase, LOW);
    Serial.println("Not heating up");
    Wire.write("Not heating up");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(transistorBase, OUTPUT);
  Wire.begin(SLAVE_ADDR); // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void requestEvent() {
  val = totalVolt / 1023.0 * analogRead(analogPin);
  // Serial.println(val);
  r1 = (constRes * val) / (totalVolt - val);
  Serial.println(r1);
  temp = kelvinToCels((celsToKelvin(25.0)) * b / (b - celsToKelvin(25.0) * log(10000 / r1)));
  Serial.println(temp);

  char charVal[10];
  dtostrf(temp, 3, 2, charVal);
  charVal[5] = ';';

  Wire.write(charVal); // respond with message of 6 bytes

  // Writing
  controlTemp(temp, targetTemp);
 
 // as expected by master
}

void loop() {
  // requestEvent();
  // Reading
  delay(500);
}