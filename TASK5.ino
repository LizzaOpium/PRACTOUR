const int LED = 3;
const int RES = A0;
float I = 0.5;
int U = 5;

void setup() {
pinMode(LED, OUTPUT);
pinMode(RES, INPUT);
Serial.begin(9600);
}

void loop() {
  // analogWrite(LED, map(analogRead(RES), 0, 1023, 255, 0));
  // Serial.println("Состояние РЕЗИСТОРА = " + String(analogRead(RES)));
  Serial.println(map(analogRead(RES), 0, 1023, 255, 0));
  I = map(analogRead(RES), 0, 1023, 0, 255);
  Serial.println("Мощность = " + String(U * I));
}
