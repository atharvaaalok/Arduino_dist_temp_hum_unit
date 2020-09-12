#include <LiquidCrystal.h>
#include "DHT.h"
#define Type DHT11
int sensePin = 4;
int rs = 7;
int en = 6;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

DHT HT(sensePin, Type);
float humidity;
float tempC;
int setTime = 100;
int dt = 1000;

int trigPin = 2;
int echoPin = 3;
float pingTravelTime;
float distance_to_target;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
  HT.begin();
  delay(setTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance_measure();
  humidity = HT.readHumidity();
  tempC = HT.readTemperature();

  lcd_display();
  
  delay(dt);
  lcd.clear();
}













int distance_measure()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH);
  distance_to_target = (((343.0) / 2.0) * (pingTravelTime / 1000000.0)) * 100.0; 
  
}

void lcd_display()
{
  lcd.setCursor(0,0);
  lcd.print("H ");
  lcd.print(humidity);
  lcd.print(" ");
  lcd.print("T ");
  lcd.print(tempC);
  lcd.setCursor(0,1);
  lcd.print("distance ");
  lcd.print(distance_to_target);
}
