#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231 clock;
RTCDateTime dt;
void setup()
{
	// initialize the LCD
	
  clock.begin();
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
  //clock.setDateTime(__DATE__, __TIME__);
}

void loop()
{
	print_time();
  delay(1000);
}
 void print_time(){
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
