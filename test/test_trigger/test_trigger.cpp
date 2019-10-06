#include <Arduino.h>
#include <unity.h>

#include "Quest_Trigger.h"

#define TEST_PIN A0

void test_trigger_on_low()
{


    Quest_Trigger trigger = Quest_Trigger(TEST_PIN);

    uint8_t pinValue = HIGH;
    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(TEST_PIN, pinValue);
        TEST_ASSERT_EQUAL(pinValue == LOW, trigger.isTriggered());
        if (pinValue == LOW)
        {
            pinValue = HIGH;
        }
        else
        {
            pinValue = LOW;
        }
    }
}

void setup()
{
    delay(4000);

    UNITY_BEGIN();

    pinMode(TEST_PIN, OUTPUT);

    RUN_TEST(test_trigger_on_low);

    // TODO: test trigger for high or low
    // TODO: test no trigger within debounce time for high or low
    // TODO: test minimum time before next trigger

    UNITY_END();
}

void loop()
{
}
