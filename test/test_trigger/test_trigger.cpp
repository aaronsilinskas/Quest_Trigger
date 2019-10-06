#include <Arduino.h>
#include <unity.h>

#include "Quest_Trigger.h"

void failAlways()
{
    TEST_ASSERT_EQUAL(true, false);
}

void setup()
{
    delay(4000);

    UNITY_BEGIN();

    RUN_TEST(failAlways);

    UNITY_END();
}

void loop()
{
}
