#include <Arduino.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_PCF8574.h>
#include <RTClib.h>
#include <LCD_I2C.h>

// RTC_DS1307 rtc;
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(0x68);

LCD_I2C lcd(0x27, 16, 2);
void setup()
{
  // Serial.begin(115200);
  // Serial.println("I2C address detection test");
  if (!i2c_dev.begin())
  {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1)
      ;
  }
  // Serial.print("Device found on address 0x");
  // Serial.println(i2c_dev.address(), HEX);

  lcd.begin();
  lcd.backlight();
  lcd.cursor();
  lcd.blink();
}

void loop()
{
  uint8_t buffer[8] = {0x00}; // we'll reuse the same buffer
  i2c_dev.write_then_read(buffer, 1, buffer, 8);
  lcd.print((0x14 * 0x64) + ((buffer[6] >> 0x04) * 0xA) + (buffer[6] & 0xf), DEC);
  lcd.print("/");
  lcd.print((((buffer[5] >> 0x04) & 0x01) * 0xA) + (buffer[5] & 0xf), DEC);
  lcd.print("/");
  lcd.print((((buffer[4] >> 0x04) & 0x03) * 0xA) + (buffer[4] & 0xf), DEC);
  lcd.setCursor(0, 1);
  lcd.print((((buffer[2] >> 0x04) & 0x03) * 0xA) + (buffer[2] & 0xf), DEC);
  lcd.print(":");
  lcd.print(((buffer[1] >> 0x04) * 0xA) + (buffer[1] & 0xf), DEC);
  lcd.print(":");
  lcd.print(((buffer[0] >> 0x04) * 0xA) + (buffer[0] & 0xf), DEC);
  // Serial.print("Write then Read: ");
  // Serial.print((0x14 * 0x64) + ((buffer[6] >> 0x04) * 0xA) + (buffer[6] & 0xf), DEC);
  // Serial.print("/");
  // Serial.print((((buffer[5] >> 0x04) & 0x01) * 0xA) + (buffer[5] & 0xf), DEC);
  // Serial.print("/");
  // Serial.print((((buffer[4] >> 0x04) & 0x03) * 0xA) + (buffer[4] & 0xf), DEC);
  // Serial.print(" ");
  // Serial.print((((buffer[2] >> 0x04) & 0x03) * 0xA) + (buffer[2] & 0xf), DEC);
  // Serial.print(":");
  // Serial.print(((buffer[1] >> 0x04) * 0xA) + (buffer[1] & 0xf), DEC);
  // Serial.print(":");
  // Serial.println(((buffer[0] >> 0x04) * 0xA) + (buffer[0] & 0xf), DEC);
  // buffer[0] = 0b00;
  // i2c_dev.write(buffer, 8);
  // delay(500);
  // lcd.backlight();
  // lcd.clear();
  // delay(500);
  delay(1000);
}
