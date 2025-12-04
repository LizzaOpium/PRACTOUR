#include <Servo.h>
const int HC_TRIG = 3;
const int HC_ECHO = 2;

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
}

void loop() {
  float dist = getDist();
  Serial.println(dist);
  delay(50);
}
