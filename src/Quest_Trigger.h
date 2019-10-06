#ifndef quest_trigger_h
#define quest_trigger_h

#include <Arduino.h>

class Quest_Trigger
{
public:
    Quest_Trigger(uint8_t pin);

    bool isTriggered();

private:
    uint8_t pin;
};

#endif
