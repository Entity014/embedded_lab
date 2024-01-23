#include <Arduino.h>
#include <AccelStepper.h>
#include <MQTT.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_I2CDevice.h>
#include <RTClib.h>
#include <LCD_I2C.h>

void task_arduino(void *arg);
const char ssid[] = "@JumboPlusIoT";
const char pass[] = "12345678";

const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_topic[] = "group42/command";
const char mqtt_state[] = "group42/state";
const char mqtt_time[] = "group42/time";
const char mqtt_client_id[] = "arduino_group_x"; // must change this string to a unique value
int MQTT_PORT = 1883;
AccelStepper stepper(AccelStepper::FULL4WIRE, 2, 4, 5, 19);

int save_state = 1;
int pos_arr[4] = {550, 1100, 1650, 2200};

WiFiClient net;
MQTTClient client;
RTC_DS1307 rtc;

LCD_I2C lcd(0x27, 16, 2);

unsigned long lastMillis = 0;

char daysOfWeek[7][12] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"};

String act = "";
bool en = false, isRandom = false;
int state;
void connect()
{
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id))
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);

  if (payload == "On")
  {
    en = true;
  }
  else if (payload == "Off")
  {
    en = false;
  }

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  pinMode(0, INPUT_PULLUP);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  if (!rtc.begin())
  {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1)
      ;
  }
  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  connect();
  lcd.begin();
  lcd.backlight();
  xTaskCreatePinnedToCore(
      task_arduino,
      "Task2",
      8192,
      NULL,
      0,
      NULL,
      0);
}

void loop()
{
  DateTime now = rtc.now();
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected())
  {
    connect();
  }

  if (now.second() % 30 == 0 && en)
  {
    state = random(3);                                     // 0, 1, 2, 3
    save_state += state + 1;                               // 0, 1, 2, 3
    save_state = save_state % 4 != 0 ? save_state % 4 : 4; // 1, 2, 3, 4
    isRandom = true;
    Serial.println(String(state) + " " + String(save_state));
  }
  // else
  // {
  //   isRandom = false;
  // }
  // Serial.println(stepper.distanceToGo());

  if (save_state == 1)
  {
    act = "Nonn";
    client.publish(mqtt_state, "Nonn");
  }
  else if (save_state == 2)
  {
    act = "Kin Keaw";
    client.publish(mqtt_state, "Kin Keaw");
  }
  else if (save_state == 3)
  {
    act = "Ren Game";
    client.publish(mqtt_state, "Ren Game");
  }
  else if (save_state == 4)
  {
    act = "Mai Rean";
    client.publish(mqtt_state, "Mai Rean");
  }

  lcd.print("Act: ");
  lcd.print(act);
  lcd.setCursor(0, 1);
  lcd.print("Clock: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second());
  client.publish(mqtt_time, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
  delay(1000);
  lcd.backlight();
  lcd.clear();
}

void task_arduino(void *arg)
{
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(100);
  while (1)
  {
    if (stepper.distanceToGo() == 0 && isRandom)
    {

      stepper.move(pos_arr[state]);
      isRandom = false;
    }
    stepper.run();
  }
}