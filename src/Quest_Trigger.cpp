#include "Quest_Trigger.h"

Quest_Trigger::Quest_Trigger(uint8_t pin, bool triggerValue, uint64_t debounceMs)
{
    this->pin = pin;
    this->triggerValue = triggerValue;
    this->debounceMs = debounceMs;
    this->lastState = digitalRead(pin);
    this->lastStateChangeMs = millis();
}

bool Quest_Trigger::isTriggered()
{
    uint64_t currentTime = millis();
    bool currentState = digitalRead(pin);

    if (currentState != lastState)
    {
        lastState = currentState;
        lastStateChangeMs = currentTime;
    }

    if (currentTime - lastStateChangeMs < debounceMs)
    {
        return false;
    }

    return currentState == triggerValue;
}
