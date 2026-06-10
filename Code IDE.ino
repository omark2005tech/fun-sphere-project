#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// تعريف السيرفو
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// تعريف IR
const int irSensorPin = 2;
const int servoPin = 3;

// تعريف البنات للستبرب
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
const int enableA = 10;
const int enableB = 11;

// تعريف المتغيرات
int sensorValue = 0;
int stepDelay = 5; // تأخير بين الخطوات

void stepMotor(int step) {
  switch(step) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
  }
}

void setup() {
  myServo.attach(servoPin);
  pinMode(irSensorPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);

  lcd.init();
  lcd.backlight();
}

void loop() {
  // حركة الستبرب موتور المستقلة
  for (int i = 0; i < 4; i++) {
    stepMotor(i);
    delay(stepDelay);
  }

  // الجزء الخاص بالـ IR والسيرفو والشاشة
  sensorValue = digitalRead(irSensorPin);
  
  if (sensorValue == HIGH) {
    myServo.write(45);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WHITE BALL");
  } else {
    myServo.write(135);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BLACK BALL");
  }
}