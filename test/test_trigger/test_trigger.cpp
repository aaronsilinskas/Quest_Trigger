#include <Arduino.h>
#include <unity.h>

#include "Quest_Trigger.h"

#define PIN_TRIGGER_LOW A0
#define PIN_TRIGGER_HIGH A1

void test_trigger_on_low()
{
    Quest_Trigger trigger = Quest_Trigger(PIN_TRIGGER_LOW, LOW, 0);

    bool pinToggle = true;
    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(PIN_TRIGGER_LOW, pinToggle);
        TEST_ASSERT_EQUAL(!pinToggle, trigger.isTriggered());
        pinToggle = !pinToggle;
    }
}

void test_trigger_on_high()
{
    Quest_Trigger trigger = Quest_Trigger(PIN_TRIGGER_HIGH, HIGH, 0);

    bool pinToggle = true;
    for (uint8_t i = 0; i < 10; i++)
    {
        digitalWrite(PIN_TRIGGER_HIGH, pinToggle);
        TEST_ASSERT_EQUAL(pinToggle, trigger.isTriggered());
        pinToggle = !pinToggle;
    }
}

void test_trigger_only_after_debounce()
{
    uint8_t debounceMs = 100;
    digitalWrite(PIN_TRIGGER_LOW, HIGH);
    Quest_Trigger triggerLow = Quest_Trigger(PIN_TRIGGER_LOW, LOW, debounceMs);
    digitalWrite(PIN_TRIGGER_HIGH, LOW);
    Quest_Trigger triggerHigh = Quest_Trigger(PIN_TRIGGER_HIGH, HIGH, debounceMs);

    uint64_t endTime = millis() + debounceMs;
    digitalWrite(PIN_TRIGGER_LOW, LOW);
    digitalWrite(PIN_TRIGGER_HIGH, HIGH);
    while (millis() < endTime)
    {
        TEST_ASSERT_EQUAL(false, triggerLow.isTriggered());
        TEST_ASSERT_EQUAL(false, triggerHigh.isTriggered());
        delay(1);
    }

    TEST_ASSERT_EQUAL(true, triggerLow.isTriggered());
    TEST_ASSERT_EQUAL(true, triggerHigh.isTriggered());
}

void test_no_trigger_if_toggled_before_debounce()
{
    uint8_t debounceMs = 100;
    digitalWrite(PIN_TRIGGER_LOW, HIGH);
    Quest_Trigger triggerLow = Quest_Trigger(PIN_TRIGGER_LOW, LOW, debounceMs);
    digitalWrite(PIN_TRIGGER_HIGH, LOW);
    Quest_Trigger triggerHigh = Quest_Trigger(PIN_TRIGGER_HIGH, HIGH, debounceMs);

    digitalWrite(PIN_TRIGGER_LOW, LOW);
    digitalWrite(PIN_TRIGGER_HIGH, HIGH);

    delay(debounceMs / 2);

    digitalWrite(PIN_TRIGGER_LOW, HIGH);
    digitalWrite(PIN_TRIGGER_HIGH, LOW);

    delay(debounceMs / 2);
    delay(1);

    TEST_ASSERT_EQUAL(false, triggerLow.isTriggered());
    TEST_ASSERT_EQUAL(false, triggerHigh.isTriggered());
}

void test_delay_retrigger()
{
    uint8_t debounceMs = 50;
    uint8_t delayMs = 200;
    digitalWrite(PIN_TRIGGER_LOW, LOW);
    Quest_Trigger triggerLow = Quest_Trigger(PIN_TRIGGER_LOW, LOW, debounceMs);

    delay(debounceMs + 1);

    TEST_ASSERT_EQUAL(true, triggerLow.isTriggered());

    uint64_t endTime = millis() + delayMs;
    triggerLow.delayNextTrigger(delayMs);
    while (millis() < endTime)
    {
        TEST_ASSERT_EQUAL(false, triggerLow.isTriggered());
        delay(1);
    }

    TEST_ASSERT_EQUAL(true, triggerLow.isTriggered());
}

void setup()
{
    delay(4000);

    UNITY_BEGIN();

    pinMode(PIN_TRIGGER_LOW, OUTPUT);
    pinMode(PIN_TRIGGER_HIGH, OUTPUT);

    RUN_TEST(test_trigger_on_low);
    RUN_TEST(test_trigger_on_high);
    RUN_TEST(test_no_trigger_if_toggled_before_debounce);
    RUN_TEST(test_delay_retrigger);

    UNITY_END();
}

void loop()
{
}
