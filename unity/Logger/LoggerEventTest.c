#include "unity_fixture.h"
#include "Logger/Logger_Event.h"

TEST_GROUP(LoggerEvent);

static Event* event;

TEST_SETUP(LoggerEvent)
{
    event = LoggerEvent_Create(0, "TEST1");
}

TEST_TEAR_DOWN(LoggerEvent)
{
    LoggerEvent_Destroy(event);
}

TEST(LoggerEvent, SetAndGet)
{
    LoggerEvent_set(event, "TEST 1", "test1");
    LoggerEvent_set(event, "TEST  2", "test2");

    TEST_ASSERT_EQUAL_STRING("test2", LoggerEvent_get(event, "TEST  2"));
    TEST_ASSERT_EQUAL_STRING("test1", LoggerEvent_get(event, "TEST 1"));
    TEST_ASSERT_NULL(LoggerEvent_get(event, "NOT SET VALUE"));
}
