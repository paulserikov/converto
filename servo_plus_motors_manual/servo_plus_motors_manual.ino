//работающее управление сервой и моторами черз буфер

#include <Servo.h> 

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

// enter pins where servo connected
uint8_t servo1 = 9;
uint8_t servo2 = 10;
uint8_t servo3 = 11;
uint8_t servo4 = 12;

// enter pins motors connected are
int pwmpin2 = 2;
int pwmpin3 = 3;
int pwmpin4 = 6;
int pwmpin5 = 5;

// function setup
void setup()  { 
  pinMode(pwmpin2, OUTPUT);
  pinMode(pwmpin3, OUTPUT);
  pinMode(pwmpin4, OUTPUT);
  pinMode(pwmpin5, OUTPUT);
  Serial.begin(9600);
}

int x, a, b;  //current level of gas
int z; //угол наклона сервомашинок

void loop() {
  receive_command();
  
}

void receive_command() {
  static char rx_buffer[20];
  static int rx_index;
  while (Serial.available() > 0) {
    int symbol = Serial.read();
    if (symbol == '\n') {
      if (rx_index > 0) { 
        rx_buffer[rx_index] = '\0';
        Serial.print("In buffer: ");
        Serial.println(rx_buffer);
        if (rx_buffer[0] == 'i') {
          Serial.print("You've sent symbol: ");
          Serial.println(rx_buffer[0]);
          //change_angle(60); //init servo
          motor1.write(120);
          motor2.write(60);
          motor3.write(60);
          motor4.write(120);
          Serial.println("You are initialized servo!");
        }
        if (rx_buffer[0] == 't') {
          tormoz();
        }
        if (rx_buffer[0] == 'w') {
          plus_gaz();
        }
        
        else if (rx_buffer[0] >= '0' && rx_buffer[0] <= '9') {
          x = 0;
          for (int i = 0; i < strlen(rx_buffer); ++i)
          x = strtol(rx_buffer, NULL, 10);
        Serial.print("You've sent PWM level: ");
        Serial.println(x);
        write_pwm (x);
        }
        rx_index = 0;
      }
    } else {
      rx_buffer[rx_index++] = symbol;
      if (rx_index >= 20)
        rx_index = 0;
    }
  }
}

void tormoz() {
analogWrite(pwmpin2, 180);
analogWrite(pwmpin3, 180);
analogWrite(pwmpin4, 180);
analogWrite(pwmpin5, 180);
}

void plus_gaz() {
Serial.print("a =");
Serial.println(a);
a=x+5; 
analogWrite(pwmpin2, a);
analogWrite(pwmpin3, a);
analogWrite(pwmpin4, a);
analogWrite(pwmpin5, a);
x=a;
}

void write_pwm(int a) {
  analogWrite(pwmpin2, a);
  analogWrite(pwmpin3, a);
  analogWrite(pwmpin4, a);
  analogWrite(pwmpin5, a);
}

//void change_angle (int a) {
 // motor1.write(180-a);
 // motor2.write(a);
 // motor3.write(a);
  //motor4.write(180-a);
//}

