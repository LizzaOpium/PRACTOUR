// Скетч 1: Базовый МСР с движением и кнопкой
// Сохранить как: MCP_Basic.ino

// Определяем пиныw
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;
const int SPEED_R = 9;
const int SPEED_L = 10;
const int BUTTON = 8;
bool flag_button = false;
const int SERVA = BUTTON;

// Переменные
int buttonPressCount = 0;

// Движение вперед
void forward(int t, int speed_l, int speed_r) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, speed_r);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed_l);
  delay(t);
}

// Остановка
void stop(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, 0);
  delay(t);
}

// Танковый поворот
void tank_turn(int t, int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(SPEED_R, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed);
  delay(t);
}

// MCP последовательность
void mcp_sequence() {
  int speed = 200;
  forward(2000, speed, speed);
  stop(1000);
  tank_turn(1000, speed);
  stop(1000);
}

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SERVA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(SPEED_R, OUTPUT);
  pinMode(SPEED_L, OUTPUT);

  Serial.begin(9600);
  Serial.println("MCP Basic готов");
  Serial.println("5 нажатий - запуск движения");

  stop(0);
}

void loop() {
  // Serial.println(digitalRead(BUTTON));
  if (!digitalRead(BUTTON) && flag_button == false) {
    while (!digitalRead(BUTTON)) {
    }
    flag_button = true;
    flag_button = false;
    delay(20);
    buttonPressCount++;
  }

  if (buttonPressCount >= 5) {
    Serial.println("Запуск MCP!");
      mcp_sequence();
      buttonPressCount = 0;
  }

  // if (!digitalRead(BUTTON) && flag_button == true) {
  //   while (!digitalRead(BUTTON)) {
  //   }
  //   flag_button = false;
  //   // крутим серво на 0
  //   Serial.println("Кнопка нажата 2-й раз!");

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

  // if (!digitalRead(BUTTON)) {
  //   while (!digitalRead(BUTTON)) {}

  //   buttonPressCount++;
  //   Serial.print("Нажатий: ");
  //   Serial.println(buttonPressCount);

  //   if (buttonPressCount >= 5) {
  //     Serial.println("Запуск MCP!");
  //     mcp_sequence();
  //     buttonPressCount = 0;
  //   }
  // }
}