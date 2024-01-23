#include <Arduino.h>

void setup()
{
    pinMode(8, INPUT_PULLUP); // set arduino pin to input mode
    pinMode(3, OUTPUT);       // set arduino pin to output mode
}
void loop()
{
    if (digitalRead(8) == LOW)
    {
        digitalWrite(3, HIGH);
    }
    else
    {
        digitalWrite(3, LOW);
    }
}