#include <LiquidCrystal.h> // библиотека для экрана
#define pin_x A2
#define pin_y A1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // создание экземпляра экрана и связь с портами S, E, DB4, DB5, DB6, DB7

byte s[8] = {16, 0, 0, 0, 0, 0, 0, 0};
int now_x = 0, now_y = 0;
int joy_x, joy_y;

void setup() // установочная функция
{
  lcd.begin(16, 2); // инициализация экрана и задание размеров
  Serial.begin(9600); // связь с Serial портом и установка скорости обмена данными
  pinMode(pin_x, INPUT);
  pinMode(pin_y, INPUT);
}

void loop() // функция бесконечного цикла
{
  joy_x = analogRead(pin_x);
  joy_y = analogRead(pin_y);
  
  if (joy_x < 100 && now_x > 0)
  {
    if (s[now_y % 8] == 16)
        {
          s[now_y % 8] = 1;
        }
        else
        {
          s[now_y % 8] <<= 1;
        }
        now_x -= 1;
  }
  else if (joy_x >= 923 && now_x != 79)
  {
    if (s[now_y % 8] == 1)
        {
          s[now_y % 8] = 16;
        }
        else
        {
          s[now_y % 8] >>= 1;
        }
        now_x += 1;
  }

  if (joy_y < 100 && now_y > 0)
  {
    if (now_y % 8 != 0)
        {
          s[now_y % 8 - 1] = s[now_y % 8];
          s[now_y % 8] = 0;
        }
        else
        {
          s[7] = s[now_y % 8];
          s[now_y % 8] = 0;
        }
        now_y -= 1;
  }
  else if (joy_y >= 923 and now_y != 15)
  {
    if ((now_y + 1) % 8 != 0)
        {
          s[now_y % 8 + 1] = s[now_y % 8];
          s[now_y % 8] = 0;
        }
        else
        {
          s[0] = s[now_y % 8];
          s[now_y % 8] = 0;
        }
        now_y += 1;
  }
  
  lcd.clear();
  lcd.createChar(1, s);
  lcd.setCursor(now_x / 5, now_y / 8);
  lcd.write(1);
  delay(100);
}
