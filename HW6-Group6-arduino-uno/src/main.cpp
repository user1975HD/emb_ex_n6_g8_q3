#include <Arduino.h>

// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

// Include queue support
#include <queue.h>

TaskHandle_t taskBlinkHandle;
TaskHandle_t taskReadAnalog1;
TaskHandle_t taskReadDist;

int analogPinPotens1 = A1;
int analogPinPotens2 = A2;

const int trigPin = 10;
const int echoPin = 11;

int getDistance()
{
  int duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  Serial.println("duration:");
  Serial.println(duration);

  distance = duration * 0.034 / 2;
}

void TaskBlink(void *pvParameters)
{
  (void)pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

void TaskReadAnalog1(void *pvParameters)
{
  (void)pvParameters;

  int poten_1val;
  // pinMode(LED_BUILTIN, OUTPUT);

  for (;;)
  {
    poten_1val = analogRead(analogPinPotens1); // read the input pin
    Serial.println(poten_1val);
  }
}

void TaskReadDist(void *pvParameters)
{
  (void)pvParameters;

  int distanceRead;

  int simu_distanceRead;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  int poten_2val;

  for (;;)
  {
    // motorVal = 10;
    // analogWrite(motorPin, motorVal);

    distanceRead = getDistance();
    Serial.println("distanceRead:");
    Serial.println(distanceRead);

    poten_2val = analogRead(analogPinPotens2); // read the input pin
    Serial.println(poten_2val);
  }
}

void setup()
{
  // put your setup code here, to run once:

  xTaskCreate(TaskBlink, // Task function
              "Blink",   // Task name
              128,       // Stack size
              NULL,
              0,                 // Priority
              &taskBlinkHandle); // Task handler

  xTaskCreate(TaskReadAnalog1, // Task function
              "ReadAnalog1",   // Task name
              128,             // Stack size
              NULL,
              1,                 // Priority
              &taskBlinkHandle); // Task handler

  xTaskCreate(TaskReadDist, // Task function
              "ReadDist",   // Task name
              128,          // Stack size
              NULL,
              3,                 // Priority
              &taskBlinkHandle); // Task handler

  Serial.begin(9600);
  digitalWrite(10, HIGH);
}

void loop()
{
  // Serial.println("alo1 :");
  // // put your main code here, to run repeatedly:
  // digitalWrite(blikerpinFaridy, LOW);
  // delay(1000);
  // digitalWrite(blikerpinFaridy, HIGH);
  // delay(1000);
  // Serial.println("alo :");
}
