const int BUTTON = 5;
const int SERVA = 3;
bool flag_button = false;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SERVA, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Serial.println(digitalRead(BUTTON));
  if (!digitalRead(BUTTON) && flag_button == false) {
    while (!digitalRead(BUTTON)) {
    }
    flag_button = true;
    // крутим серво на 0
    Serial.println("Кнопка нажата 1-й раз!");
  }
  if (!digitalRead(BUTTON) && flag_button == true) {
    while (!digitalRead(BUTTON)) {
    }
    flag_button = false;
    // крутим серво на 0
    Serial.println("Кнопка нажата 2-й раз!");
  }
  if (flag_button) {
    digitalWrite(SERVA, HIGH);
    delayMicroseconds(500);
    digitalWrite(SERVA, LOW);
    delay(20);
  }
  if (!flag_button) {
    digitalWrite(SERVA, HIGH);
    delayMicroseconds(2500);
    digitalWrite(SERVA, LOW);
    delay(20);
  }
}
