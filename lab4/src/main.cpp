#include <Arduino.h>
#include <Esp.h>
#include <esp_log.h>
#define LDR 35
#define LED 2
int LDR_Value = 0;
int static_variable = 500;

void setup()
{
  Serial.begin(115200);
  pinMode(LDR, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);
}

void loop()
{
  LDR_Value = analogRead(LDR);
  ESP_LOGI("Main", "LDR_1: %d Static: %d", LDR_Value, static_variable);

  if (LDR_Value > 600)
  {
    digitalWrite(LED, LOW);
  }
  else if (LDR_Value < 400)
  {
    digitalWrite(LED, HIGH);
  }

  // Serial.print("LDR_1: ");
  Serial.println(LDR_Value);
  // Serial.print(",");
  // Serial.print("Static: ");
  Serial.println(static_variable);
  delay(20);
}