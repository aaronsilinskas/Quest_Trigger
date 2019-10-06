#include "Quest_Trigger.h"

Quest_Trigger::Quest_Trigger(uint8_t pin, bool triggerValue)
{
    this->pin = pin;
    this->triggerValue = triggerValue;
}

bool Quest_Trigger::isTriggered()
{
    return digitalRead(pin) == triggerValue;
}
