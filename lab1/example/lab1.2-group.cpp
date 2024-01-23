#include <Arduino.h>
#define LED 23
#define DELAY_TIME 1000

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    digitalWrite(LED, HIGH); // turn the LED on
    delay(DELAY_TIME);       // wait for a second
    digitalWrite(LED, LOW);  // turn the LED off
    delay(DELAY_TIME);       // wait for a second
}
