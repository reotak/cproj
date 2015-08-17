#include "unity_fixture.h"
#include "Logger/Logger_Logs.h"

TEST_GROUP(LoggerLogs);

static Logs* logs;

TEST_SETUP(LoggerLogs)
{
    logs = LoggerLogs_Create();
}

TEST_TEAR_DOWN(LoggerLogs)
{
    LoggerLogs_Destroy(logs);
}


TEST(LoggerLogs, SetAndGet)
{
    LoggerLogs_set(logs, "TEST 1", "test1");
    LoggerLogs_set(logs, "TEST  2", "test2");

    TEST_ASSERT_EQUAL_STRING("test2", LoggerLogs_get(logs, "TEST  2"));
    TEST_ASSERT_EQUAL_STRING("test1", LoggerLogs_get(logs, "TEST 1"));
    TEST_ASSERT_NULL(LoggerLogs_get(logs, "NO DATA"));
}

