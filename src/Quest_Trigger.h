#ifndef quest_trigger_h
#define quest_trigger_h

#include <Arduino.h>

class Quest_Trigger
{
public:
    Quest_Trigger(uint8_t pin, bool triggerValue, uint64_t debounceMs);

    bool isTriggered();
    void delayNextTrigger(uint64_t delayMs);

private:
    uint8_t pin;
    bool triggerValue;
    uint64_t debounceMs;
    bool lastState;
    uint64_t lastStateChangeMs;
    uint64_t delayUntilMs;
};

#endif
