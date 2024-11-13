int analogPin = A3;
double val = 0.0; // store the read value

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = 5.0 / 1023.0 * analogRead(analogPin);
  double r1 = 800 * val / (5 - val)
  Serial.println(val);
  delay(100);
}
