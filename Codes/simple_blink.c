#include <Arduino.h>

const int blinker = 13;

void setup()
{
    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(blinker, LOW);
    delay(1000);
    digitalWrite(blinker, HIGH);
    delay(1000);
}