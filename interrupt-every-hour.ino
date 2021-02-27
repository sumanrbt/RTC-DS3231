/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS3231.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<avr/sleep.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

DS3231 clock;
RTCDateTime dt;
boolean isAlarm = false;
boolean alarmState = false;
int alarmLED = 4;
boolean boo=false;
int hr=9;
int mn=0;
void alarmFunction()
{
  isAlarm = true;
  
}

void setup()
{
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  lcd.begin();
  clock.begin();
  
   
   clock.enable32kHz(false);
  // Enable output
  //clock.enableOutput(true);
  // Disable output
  clock.enableOutput(false);
  clock.armAlarm1(false);
  clock.clearAlarm1();
  //clock.setAlarm1(0, 0, 0, 10, DS3231_MATCH_S);
  clock.setAlarm1(0, hr, mn, 0, DS3231_MATCH_H_M_S);
  //lcd.setCursor(1,1);
  //lcd.print(clock.isAlarm1());
  //lcd.setCursor(0,1);//lcd.setCursor(column,row)
   pinMode(alarmLED, OUTPUT);
   pinMode(2, INPUT_PULLUP);
   // Attach Interrput 0. In Arduino UNO connect DS3231 INT to Arduino Pin 2
  
   //attachInterrupt(digitalPinToInterrupt(2), alarmFunction, FALLING); 
  //checkAlarms();
}

void checkAlarms()
{
  RTCAlarmTime a1;  
  
  if (clock.isArmed1())
  {
    
    lcd.setCursor(0,1);
    switch (clock.getAlarmType1())
    {
      case DS3231_EVERY_SECOND:
        Serial.println("every second");
        break;
      case DS3231_MATCH_S:
      //lcd.print("MATCH_S");
        break;
      case DS3231_MATCH_M_S:
        Serial.print("when minutes and sencods match: ");
        Serial.println(clock.dateFormat("__ __:i:s", a1));
        break;
      case DS3231_MATCH_H_M_S:
        Serial.print("when hours, minutes and seconds match: ");
        Serial.println(clock.dateFormat("__ H:i:s", a1));
        break;
      case DS3231_MATCH_DT_H_M_S:
        Serial.print("when date, hours, minutes and seconds match: ");
        Serial.println(clock.dateFormat("d H:i:s", a1));
        break;
      case DS3231_MATCH_DY_H_M_S:
        Serial.print("when day of week, hours, minutes and seconds match: ");
        Serial.println(clock.dateFormat("l H:i:s", a1));
        break;
      default: 
        Serial.println("UNKNOWN RULE");
        break;
    }
  } 
  else
  {
    lcd.setCursor(0,1);
    lcd.print("No Alarm1");
  }
}

void loop()
{ //lcd.begin(); 
 
  print_time();
  delay(1000);
  lcd.clear();
  if (boo){
    boo=false;
    clock.clearAlarm1();
    clock.armAlarm1(false);
    clock.clearAlarm1();
    clock.setAlarm1(0, hr, mn, 00, DS3231_MATCH_H_M_S);
    digitalWrite(alarmLED, HIGH);
    delay(5000);
    digitalWrite(alarmLED, LOW);
    /////lcd.setCursor(5,1);
    ////lcd.print("Fired");
    ////delay(5000);
  }
  delay(500);
  //lcd.clear();
  going_to_sleep();
  //if (clock.isAlarm1())
  //{ 
  //  lcd.setCursor(0,1);
   // lcd.print("Alarm"); 
  //}
 
// if (isAlarm)
//  {  lcd.setCursor(11,1);
//     lcd.print(isAlarm);
//       digitalWrite(alarmLED, alarmState);
//       alarmState = !alarmState;
//      delay(1000);
//       clock.clearAlarm1();
//       clock.armAlarm1(false);
//       clock.clearAlarm1();
//       clock.setAlarm1(0, 0, 0, 10, DS3231_MATCH_S);
//     isAlarm=false;
//  } 
 
 
 }
 void print_time(){
  //clock.setDateTime(__DATE__, __TIME__);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  dt = clock.getDateTime();
  
  // For leading zero look to DS3231_dateformat example

  lcd.print("Time ");   
  lcd.print(dt.hour);
  lcd.print(":");  
  lcd.print(dt.minute);
  lcd.print(":"); 
  lcd.print(dt.second);
 }

 void going_to_sleep(){
  
  lcd.setCursor(0,0);
  lcd.print("SLEEPY!");
  delay(1000);
  //lcd.clear();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts (); 
  sleep_enable();
  EIFR = bit (INTF0);
  attachInterrupt(digitalPinToInterrupt(2), wake_up, FALLING); 
  digitalWrite(LED_BUILTIN,LOW);
  
  interrupts ();  
  sleep_cpu();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WOKE");
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  detachInterrupt(digitalPinToInterrupt(2));
  
 }

 void wake_up(){
  sleep_disable();
  boo=true;
  
 }
