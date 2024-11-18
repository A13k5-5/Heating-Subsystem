int analogPin = A3;
double val = 0.0; // store the read value
double constRes = 6660.0;
double totalVolt = 5.0;
double b = 4220;

double celsToKelvin(double cels) {
  return cels + 273.15;
}

double kelvinToCels(double kelv){
  return kelv - 273.15;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = totalVolt / 1023.0 * analogRead(analogPin);
  double r1 = (constRes * val) / (totalVolt - val);
  double temp = kelvinToCels((celsToKelvin(25.0)) * b / (b - celsToKelvin(25.0) * log(10000 / r1)));

  Serial.println(temp);
  delay(100);
}