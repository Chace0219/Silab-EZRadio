
#include "PIRSensor.h"

PIRSensor::PIRSensor(int pin)
{
  _pin = pin;
  pinMode(pin, INPUT);
}

bool PIRSensor::status() const
{
  return (digitalRead(_pin));
}
