#include <Servo.h>

Servo servo1; // создаем серво

const int HC_TRIG = 8;
const int HC_ECHO = 2;
int n = 0;

float getDist() {
  // импульс 10 мкс
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);

  // измеряем время ответного импульса
  float us = pulseIn(HC_ECHO, HIGH);

  // считаем расстояние и возвращаем
  return us /  58.2;
}

void setup() {
  Serial.begin(9600);
  pinMode(HC_TRIG, OUTPUT); // тригг - выход
  pinMode(HC_ECHO, INPUT); // ехо - вход
  servo1.attach(3); // подключение сервы к пину
  servo1.write(0);
  delay(1000);
}

void loop() {
  float dist = getDist();
  Serial.println("Зафиксирована дистанция: " + String(dist) + "СМ");
  servo1.write(n % 180);
  Serial.println("Градус: " + String(n % 180) + "°");
  n += 1;
}
