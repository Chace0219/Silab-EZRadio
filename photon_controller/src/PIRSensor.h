#ifndef _PIRSENSOR_H
#define _PIRSENSOR_H

#include "application.h"

class PIRSensor
{
  public:
    PIRSensor(int pin);
    bool status() const;
  private:
    int _pin;
};

#endif //PinSensor_h
