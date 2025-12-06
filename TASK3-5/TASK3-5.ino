// Скетч 2: Задания 3, 4, 5
// Сохранить как: MCP_Sensors.ino

#include <Servo.h>

// Определяем пины
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;
const int SPEED_R = 10;
const int SPEED_L = 9;
const int HC_TRIG = 3;
const int HC_ECHO = 2;
const int BUTTON = 8;
const int LINE_SENSOR_RIGHT = A0;
const int LINE_SENSOR_LEFT = A1;
const int SERVO_PIN = 11;

// Переменные
int buttonPressCount = 0;
int lineThreshold = 500;
int taskState = 0; // 0-ожидание, 1-линия, 2-УЗ, 3-серво
Servo myServo;

// ==================== ФУНКЦИИ ДВИЖЕНИЯ ====================

void forward(int t, int speed_l, int speed_r) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, speed_r);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed_l);
  delay(t);
}

void stop(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(SPEED_R, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, 0);
  delay(t);
}

void tank_turn(int t, int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(SPEED_R, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_L, speed);
  delay(t);
}

// ==================== ЗАДАНИЕ 3: ДАТЧИКИ ЛИНИИ ====================

void calibrateLineSensors() {
  Serial.println("=== КАЛИБРОВКА ===");
  
  Serial.println("Правый на белую -> кнопка");
  waitForButton();
  int wR = analogRead(LINE_SENSOR_RIGHT);
  
  Serial.println("Правый на черную -> кнопка");
  waitForButton();
  int bR = analogRead(LINE_SENSOR_RIGHT);
  
  Serial.println("Левый на белую -> кнопка");
  waitForButton();
  int wL = analogRead(LINE_SENSOR_LEFT);
  
  Serial.println("Левый на черную -> кнопка");
  waitForButton();
  int bL = analogRead(LINE_SENSOR_LEFT);
  
  lineThreshold = (wR + wL + bR + bL) / 4;
  Serial.print("Порог: ");
  Serial.println(lineThreshold);
}

void waitForButton() {
  while (digitalRead(BUTTON)) {}
  while (!digitalRead(BUTTON)) {}
  delay(200);
}

void lineAlignment() {
  Serial.println("=== ВЫРАВНИВАНИЕ ===");
  int speed = 77;
  
  // Определяем начальный цвет
  bool initColor = analogRead(LINE_SENSOR_LEFT) >= lineThreshold;
  Serial.print("Начальный цвет: ");
  Serial.println(initColor ? "БЕЛЫЙ" : "ЧЕРНЫЙ");
  
  // Движение пока оба датчика на одном цвете
  Serial.println("Движение...");
  while (true) {
    bool left = analogRead(LINE_SENSOR_LEFT) >= lineThreshold;
    bool right = analogRead(LINE_SENSOR_RIGHT) >= lineThreshold;
    
    if (left == initColor && right == initColor) {
      forward(50, speed, speed);
    } else {
      stop(0);
      break;
    }
    delay(50);
  }
  
  // Определяем какой датчик сменил цвет
  bool leftChanged = (analogRead(LINE_SENSOR_LEFT) >= lineThreshold) != initColor;
  bool rightChanged = (analogRead(LINE_SENSOR_RIGHT) >= lineThreshold) != initColor;
  
  // Выравнивание
  if (leftChanged && !rightChanged) {
    // Вращаем правое колесо
    Serial.println("Вращаем правое колесо");
    while ((analogRead(LINE_SENSOR_RIGHT) >= lineThreshold) == initColor) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(SPEED_R, speed);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(SPEED_L, 0);
      delay(50);
    }
  } 
  else if (!leftChanged && rightChanged) {
    // Вращаем левое колесо
    Serial.println("Вращаем левое колесо");
    while ((analogRead(LINE_SENSOR_LEFT) >= lineThreshold) == initColor) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(SPEED_R, 0);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(SPEED_L, speed);
      delay(50);
    }
  }
  
  stop(1000);
  Serial.println("Выравнивание завершено");
}

// ==================== ЗАДАНИЕ 4: УЗ ДАТЧИК ====================

float measureDistance() {
  digitalWrite(HC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  
  long duration = pulseIn(HC_ECHO, HIGH, 30000);
  float distance = duration * 0.034 / 2;
  
  if (distance <= 0 || distance > 400) {
    return -1;
  }
  
  return distance;
}

void objectDetection() {
  Serial.println("=== ОБНАРУЖЕНИЕ ОБЪЕКТА ===");
  int speed = 77;
  
  while (true) {
    float dist = measureDistance();
    
    if (dist > 0) {
      Serial.print("Расстояние: ");
      Serial.print(dist);
      Serial.println(" см");
      
      if (dist <= 10) {
        Serial.println("Объект найден!");
        stop(0);
        break;
      } else {
        forward(100, speed, speed);
      }
    } else {
      forward(100, speed, speed);
    }
    
    delay(100);
  }
}

// ==================== ЗАДАНИЕ 5: СЕРВОПРИВОД ====================

void servoGrab() {
  Serial.println("=== ЗАХВАТ СЕРВО ===");
  
  myServo.attach(SERVO_PIN);
  delay(1000);
  
  // Отпущено (0°)
  Serial.println("Положение: отпущено");
  myServo.write(0);
  delay(2000);
  
  // Захвачено (90°)
  Serial.println("Положение: захвачено");
  myServo.write(90);
  delay(2000);
  
  // Возврат
  Serial.println("Положение: отпущено");
  myServo.write(0);
  delay(2000);
  
  myServo.detach();
}

// ==================== УПРАВЛЕНИЕ ЗАДАНИЯМИ ====================

void setup() {
  // Настройка пинов
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(SPEED_R, OUTPUT);
  pinMode(SPEED_L, OUTPUT);
  pinMode(HC_TRIG, OUTPUT);
  pinMode(HC_ECHO, INPUT);
  
  Serial.begin(9600);
  Serial.println("=== MCP ЗАДАНИЯ 3-4-5 ===");
  Serial.println("Инструкция:");
  Serial.println("1. 5 нажатий - Задание 3 (Линия)");
  Serial.println("2. 1 нажатие - Задание 4 (УЗ датчик)");
  Serial.println("3. 1 нажатие - Задание 5 (Сервопривод)");
  Serial.println("========================");
  
  stop(0);
}

void loop() {
  // Обработка кнопки для выбора задания
  if (!digitalRead(BUTTON)) {
    while (!digitalRead(BUTTON)) {}
    
    buttonPressCount++;
    Serial.print("Нажатий: ");
    Serial.println(buttonPressCount);
    
    // Задание 3: 5 нажатий
    if (buttonPressCount >= 5 && taskState == 0) {
      Serial.println("\n>>> ЗАДАНИЕ 3: Линия");
      calibrateLineSensors();
      lineAlignment();
      taskState = 1;
      buttonPressCount = 0;
    }
    // Задание 4: 1 нажатие после задания 3
    else if (buttonPressCount >= 1 && taskState == 1) {
      Serial.println("\n>>> ЗАДАНИЕ 4: УЗ датчик");
      objectDetection();
      taskState = 2;
      buttonPressCount = 0;
    }
    // Задание 5: 1 нажатие после задания 4
    else if (buttonPressCount >= 1 && taskState == 2) {
      Serial.println("\n>>> ЗАДАНИЕ 5: Сервопривод");
      servoGrab();
      taskState = 3;
      buttonPressCount = 0;
      Serial.println("\nВсе задания выполнены!");
      Serial.println("Перезагрузите плату для повторения");
    }
  }
  
  // Задержка для стабильности
  delay(10);
}