const int LED = 3;
const int PHOTORES = A0;
int max = 0;
int min = 9999;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PHOTORES, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Задаем показания фоторезистора, чем темнее - тем больше значение
  int photoresState = analogRead(PHOTORES);
  Serial.print("Состояние Фоторезистора = ");
  Serial.println(photoresState);
  
  // напишем штуку, которая будет оценивать минимум и максимум показаний
  // if (photoresState > max) {
  //   max = photoresState;
  // }
  // if (photoresState < min) {
  //   min = photoresState; 
  // }
  // Serial.print("Минмум: ");
  // Serial.println(min);
  // Serial.print("Максимум: ");
  // Serial.println(max);

  if(photoresState > 900) {
    // т.е. если слишком темно, вырубим светодиод
    analogWrite(LED, 0);
  }
  else analogWrite(LED, map(photoresState, 0, 1023, 255, 0));
  Serial.print("яркость светодиода = ");
  Serial.println(map(photoresState, 0, 1023, 255, 0));
}
