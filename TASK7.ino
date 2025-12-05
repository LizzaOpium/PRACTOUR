int LED[5] = { 3, 5, 9, 10, 11 };
int const PHOTORES = A0;
int const MAX = 800;
int const MIN = 158;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
  }
  pinMode(PHOTORES, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(PHOTORES));
  int A = map(analogRead(PHOTORES), 0, 1023, 1, 5);

  if (analogRead(PHOTORES) >= MIN) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED[i], 0);
    }

    for (int i = 0; i < A; i++) {
      digitalWrite(LED[i], 1);
    }
  }
  
  if (analogRead(PHOTORES) < MIN) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED[i], 0);
    }
  }

  if (analogRead(PHOTORES) > MAX) {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], 1);
    }
  }
}
