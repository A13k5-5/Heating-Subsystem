// Reading const
#define SLAVE_ADDR 9
#include <Wire.h>
int analogPin = A3;
float val = 0.0; // store the read value
float constRes = 9960.0;
float totalVolt = 5.0;
float b = 4220;
float r1, temp;

// Writing const
int transistorBase = 3;
float targetTemp = 35;

float celsToKelvin(float cels) {
  return cels + 273.15;
}

float kelvinToCels(float kelv){
  return kelv - 273.15;
}

void controlTemp(float curTemp, float targetTemp){
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
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event
}

void receiveEvent(int bytes) {
  String receivedData = ""; // Clear the buffer
  while (Wire.available()) {
    char c = Wire.read();
    receivedData += c;
  }
  Serial.println("Data received from ESP32: " + receivedData);
  targetTemp = receivedData.toFloat();

}

void requestEvent() {
  val = totalVolt / 1023.0 * analogRead(analogPin);
  Serial.println(val);
  // Serial.println(val);
  r1 = (constRes * val) / (totalVolt - val);
  
  // temp = -332.28*r1 + 18026;

  // Old method to calculate temp - not always accurate
  temp = kelvinToCels((celsToKelvin(25.0)) * b / (b - celsToKelvin(25.0) * log(10000 / r1)));
  // Serial.println(temp);

  char tempMsg[10];

  // Convert float to char array
  sprintf(tempMsg, "%f", temp);


  Wire.write(tempMsg); // respond with message of 6 bytes

  // Writing
  controlTemp(temp, targetTemp);
 
 // as expected by master
}

void loop() {
  requestEvent();
  // Reading
  delay(500);
}