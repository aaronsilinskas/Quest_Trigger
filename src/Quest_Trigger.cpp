#include "Quest_Trigger.h"

Quest_Trigger::Quest_Trigger(uint8_t pin)
{
    this->pin = pin;
}

bool Quest_Trigger::isTriggered()
{
    return digitalRead(pin) == LOW;
}
