#include "DHT.h"
#define Type DHT11
#include <LiquidCrystal.h>

int sensor_pin = 2;
int temp_toggle_switch = 4;

int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12; 

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT HT(sensor_pin, Type);

float humidity;
float temp_celcius;
float temp_faren;

int temp_flag = 0;

void printToLCD() {
    lcd.setCursor(0, 0);
    lcd.print("HUMID: ");
    lcd.print(humidity);
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("TEMP: ");
    if (temp_flag == 0) {
      lcd.print(temp_celcius);
      lcd.print(" C");
    }else {
      lcd.print(temp_faren);
      lcd.print(" F");
    }
}


void setup() {
  Serial.begin(9600);
  HT.begin();
  lcd.begin(16, 2);
  pinMode(temp_toggle_switch, INPUT);
}

void loop() {
  humidity = HT.readHumidity();
  temp_celcius = HT.readTemperature();
  temp_faren = HT.readTemperature(true);
  int temp = digitalRead(temp_toggle_switch);

  if (temp == 0) {
    if (temp_flag == 0) {
      temp_flag = 1;
    } else {
        temp_flag = 0;
      }
  }

  printToLCD();
  
  delay(200);
}
