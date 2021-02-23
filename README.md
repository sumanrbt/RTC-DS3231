# RTC-DS3231

DS3231 interrupt every minute is the arduino code for (uno + lcd(16,2) + RTC DS3231 module
This code has interrupts at the 10th second of everyminute, it wakes the sleeping arduino, sets the alarm and does the required logic and then sleeps back.
With the lcd panel and the arduino being waked up the system draws about 60mA of current and when the arduino is sleeping it draws about 40 mA of current.
![Test Image 4](https://user-images.githubusercontent.com/53753302/108868082-dc785400-761b-11eb-8f22-c5275bbf877e.jpeg)
In arduino nano only the pins A4 and A5 are the SDA and SCL pins respectively for the i2c communication. Since we have a lcd and an rtc module that both use I2C for communnication we can use the same set of pins for both devices as each device has a different id and handled seperately. The nano +lcd(with backlit on) and the rtc in the normal operating mode consume 50mA and in the sleep mode with the lcd (and backlit) on and the rtc it sonsumes only 30mA.
Note that the backlight of the lcd alone consumes 10mA.
The nano and the rtc without the lcd consumes 10mA in the sleep mode and 30 mA in the normal wake stage

![Test Image 4](https://user-images.githubusercontent.com/53753302/108868037-cff3fb80-761b-11eb-8c0e-5325ad5882a3.jpeg)

