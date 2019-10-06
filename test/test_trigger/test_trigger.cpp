#include <Arduino.h>
#include <unity.h>

#include "Quest_Trigger.h"

#define TEST_PIN A0

void test_trigger_on_low()
{
    Quest_Trigger trigger = Quest_Trigger(TEST_PIN, LOW);

    bool pinHigh = true;
    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(TEST_PIN, pinHigh);
        TEST_ASSERT_EQUAL(!pinHigh, trigger.isTriggered());
        pinHigh = !pinHigh;
    }
}

void test_trigger_on_high()
{
    Quest_Trigger trigger = Quest_Trigger(TEST_PIN, HIGH);

    bool pinHigh = true;
    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(TEST_PIN, pinHigh);
        TEST_ASSERT_EQUAL(pinHigh, trigger.isTriggered());
        pinHigh = !pinHigh;
    }
}

void setup()
{
    delay(4000);

    UNITY_BEGIN();

    pinMode(TEST_PIN, OUTPUT);

    RUN_TEST(test_trigger_on_low);
    RUN_TEST(test_trigger_on_high);

    // TODO: test no trigger within debounce time for high or low
    // TODO: test minimum time before next trigger

    UNITY_END();
}

void loop()
{
}
