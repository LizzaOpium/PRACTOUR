const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;
const int SPEED_R = 10;
const int SPEED_L = 9;
const int HC_TRIG = 3;
const int HC_ECHO = 2;
int speed_r = 120;
int speed_l = 120;

void forward(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, speed_r);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed_l);
  delay(t);
}

void backward(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(SPEED_R, speed_r);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(SPEED_L, speed_l);
  delay(t);
}

void stop(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, speed_r);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed_l);
  delay(t);
}

// ДЛЯ СОНАРА
float getDist() {
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  float us = pulseIn(HC_ECHO, HIGH);
  return us /  58.2;
}

void setup() {
  Serial.begin(9600);
  pinMode(HC_TRIG, OUTPUT); // тригг - выход
  pinMode(HC_ECHO, INPUT); // ехо - вход
}

void loop() {
  int distance = getDist();
  Serial.println(distance);

  if (distance > 9.0) {
    forward(10);
  }
  if (distance == 9.0) {
    stop(10);
  }  
  if (distance < 9.0) {
    backward(10);
  }
}
