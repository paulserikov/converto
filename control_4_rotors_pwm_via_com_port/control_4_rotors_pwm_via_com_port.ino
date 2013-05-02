// прорамма управления скважностью ШИМ (одновременно 4 движками) через com-порт
// внимание! в настройках терминала необходимо установить NEW LINE

int pwmpin2 = 2;
int pwmpin3 = 3; // передние два пропеллера
int pwmpin4 = 4;
int pwmpin5 = 5; // задние два
int x = 0;

void setup()  { 
  pinMode(pwmpin2, OUTPUT);
  pinMode(pwmpin3, OUTPUT);
  pinMode(pwmpin4, OUTPUT);
  pinMode(pwmpin5, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter PWM value (recommended from 180 to 255");
}

void loop()  {
  while (Serial.available() > 0) 
    {
      int symbol = Serial.read();
      if (symbol == '\n') {
      Serial.print("You have received: ");
      Serial.println(x);
      analogWrite(pwmpin2, x);
      analogWrite(pwmpin3, x);
      analogWrite(pwmpin4, x);
      analogWrite(pwmpin5, x);
      x = 0;
      } else {
      x = x * 10 + (symbol - '0');
      }
    }
  }
