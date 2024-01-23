#include <Arduino.h>
#define LED 23
#define BUTTON 32

void setup()
{
    pinMode(BUTTON, INPUT_PULLUP); // set arduino pin to input mode
    pinMode(LED, OUTPUT);          // set arduino pin to output mode
}
void loop()
{
    if (digitalRead(BUTTON) == LOW)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}