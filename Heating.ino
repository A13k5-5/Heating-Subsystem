// Reading const
int analogPin = A3;
double val = 0.0; // store the read value
double constRes = 6660.0;
double totalVolt = 5.0;
double b = 4220;
double r1, temp;
double tempUncertainty = 0.6;

// Writing const
int transistorBase = 2;
double targetTemp = 28;

double celsToKelvin(double cels) {
  return cels + 273.15;
}

double kelvinToCels(double kelv){
  return kelv - 273.15;
}

void controlTemp(double curTemp, double targetTemp){
  if (curTemp < targetTemp){
    digitalWrite(transistorBase, LOW);
    Serial.println("Heating up");
  } else {
    digitalWrite(transistorBase, LOW);
    Serial.println("Not heating up");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(transistorBase, OUTPUT);
}

void loop() {
  // Reading
  val = totalVolt / 1023.0 * analogRead(analogPin);
  r1 = (constRes * val) / (totalVolt - val);
  temp = kelvinToCels((celsToKelvin(25.0)) * b / (b - celsToKelvin(25.0) * log(10000 / r1)));
  Serial.println(temp);

  // Writing
  controlTemp(temp, targetTemp);
  delay(1500);
}