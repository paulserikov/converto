// код удержания сервы в заданной позиции
// motor.write от 60 до 140

#include <Servo.h> // Подключаем стандартную библиотеку

Servo motor1;  // Создаём экземпляры класса сервомашинок
Servo motor2;
Servo motor3;
Servo motor4;

uint8_t servo1 = 9; // Пин к которому подключена серва
uint8_t servo2 = 10;
uint8_t servo3 = 11;
uint8_t servo4 = 12;
int x=0;

void setup(){
  Serial.begin(9600);
  motor1.attach(servo1); // Указываем на каком пине сидит серва
  motor2.attach(servo2);
  motor3.attach(servo3);
  motor4.attach(servo4);
  Serial.println("Hello servo!");
  Serial.println("Enter angle value from 60 to 140...");
}


void loop()  {
  while (Serial.available() > 0) 
    {
      int symbol = Serial.read();
      if (symbol == '\n') {
      Serial.print("You sent: ");
      Serial.println(x);
      motor1.write(180-x);
      motor2.write(x);
      motor3.write(x);
      motor4.write(180-x);
      x = 0;
      } else {
      x = x * 10 + (symbol - '0');
      }
    }
  }

