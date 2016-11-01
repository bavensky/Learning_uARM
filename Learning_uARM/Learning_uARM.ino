#include <Servo.h>

Servo BASE;
Servo SHOULDER;
Servo ARM;


#define base  8
#define shoulder  9
#define arm 10

#define s_base  A5
#define s_shoulder  A4
#define s_arm  A3

#define  Buzzer 3
#define  buttonSet 4
#define  buttonStart 7

int angle_base = 0;
int angle_shoulder = 0;
int angle_arm = 0;

int arrayBase[5];
int arrayShoulder[5];
int mode = 0, count = 0;

void beep(int up, int down) {
  digitalWrite(Buzzer, HIGH);
  delay(up);
  digitalWrite(Buzzer, LOW);
  delay(down);
}

void setup() {
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);
  pinMode(buttonSet, INPUT);
  pinMode(buttonStart, INPUT);

  BASE.attach(base);
  SHOULDER.attach(shoulder);
  ARM.attach(arm);

  BASE.write(90);
  SHOULDER.write(90);
  delay(1000);
  BASE.detach();
  SHOULDER.detach();
}

void loop() {
  if (digitalRead(buttonSet) == 0) {
    delay(200);
    beep(100, 100);
    mode = 1;
  }
  if (digitalRead(buttonStart) == 0) {
    delay(200);
    beep(100, 100);
    beep(100, 100);
    mode = 2;
  }

  while (mode == 1)  {
    Serial.println("Mode 1");
    if (digitalRead(buttonSet) == 0)   {
      delay(200);
      angle_base = map(analogRead(s_base), 222, 465, 0, 180);
      angle_shoulder = map(analogRead(s_shoulder), 225, 470, 0, 180);
      arrayBase[count] = angle_base;
      arrayShoulder[count] = angle_shoulder;
      count += 1;
      Serial.println("Next");
      beep(100, 100);
      beep(100, 100);
      delay(1000);
    }
    if (digitalRead(buttonStart) == 0) {
      delay(200);
//      Serial.println("Exit");
      BASE.attach(base);
      SHOULDER.attach(shoulder);
      beep(1000, 0);
      BASE.write(90);
      SHOULDER.write(90);
      delay(2000);
      BASE.detach();
      SHOULDER.detach();
      mode = 0;
    }
  }

  while (mode == 2) {
    beep(1000, 0);
    BASE.attach(base);
    SHOULDER.attach(shoulder);

//    Serial.print("Array = ");

    for (int i = 0; i < 5; i++) {
//      Serial.print(arrayBase[i]);
//      Serial.print(" ");
//      Serial.println(arrayShoulder[i]);

      BASE.write(arrayBase[i]);
      SHOULDER.write(arrayShoulder[i]);
      delay(1000);
    }

    BASE.write(90);
    SHOULDER.write(90);
    delay(1000);
    BASE.detach();
    SHOULDER.detach();
    mode = 0;
    beep(100, 100);
    beep(100, 100);
    beep(100, 100);
  }

//  angle_base = map(analogRead(s_base), 222, 465, 0, 180);
//  angle_shoulder = map(analogRead(s_shoulder), 138, 373, 0, 180);
//
//  Serial.print("Main = ");
//  Serial.print(angle_base);
//  Serial.print(" ");
//  Serial.println(digitalRead(angle_shoulder));
//  delay(200);
}
