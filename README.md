# RTC-DS3231

DS3231 interrupt every minute is the arduino code for (uno + lcd(16,2) + RTC DS3231 module
This code has interrupts at the 10th second of everyminute, it wakes the sleeping arduino, sets the alarm and does the required logic and then sleeps back.
With the lcd panel and the arduino being waked up the system draws about 60mA of current and when the arduino is sleeping it draws about 40 mA of current.
