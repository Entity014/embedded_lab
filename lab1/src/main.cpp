#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
}
void loop()
{
  Serial.println(!digitalRead(0));
  for (int i = 0; i < rand(200); i++)
  {
    onestep;
  }
  state++;
}