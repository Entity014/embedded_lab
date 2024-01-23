#include <Arduino.h>

int value = 0;
uint32_t pre_btn = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(8, INPUT_PULLUP);
}
void loop()
{
    if (pre_btn != digitalRead(8))
    {
        pre_btn = digitalRead(8);
        if (digitalRead(8) == LOW)
        {
            value++;
        }
    }
    Serial.println(value);
}