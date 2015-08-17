#include "unity_fixture.h"
#include "Logger/Logger.h"

TEST_GROUP(Logger);

// よく使う場所の名前
static char *sameLoc = "SAME_LOCATION!";


TEST_SETUP(Logger)
{
    Logger_Create();
}

TEST_TEAR_DOWN(Logger)
{
    Logger_Destroy();
}

TEST(Logger, SetNewEvent) 
{
    // 最初のイベント番号は 0 から始まる
    TEST_ASSERT_EQUAL_INT(0, Logger_setNewEvent("TEST1"));
    TEST_ASSERT_EQUAL_INT(1, Logger_setNewEvent("TEST2"));
    TEST_ASSERT_EQUAL_INT(2, Logger_setNewEvent("TEST3"));
    TEST_ASSERT_EQUAL_INT(3, Logger_setNewEvent("TEST4"));
}

TEST(Logger, WriteAndRead)
{
    int event1 = Logger_setNewEvent("Location1");
    Logger_write(event1, "NAME1", "%d", 10);

    int event2 = Logger_setNewEvent(sameLoc);
    Logger_write(event2, "NAME1", "%s", "TEST_RESULT");
    Logger_write(event2, "NAME2", "%0.3lf", 0.12345f);

    int event3 = Logger_setNewEvent(sameLoc);

    TEST_ASSERT_EQUAL_STRING("10", Logger_read(event1, "NAME1"));
    TEST_ASSERT_EQUAL_STRING("TEST_RESULT", Logger_read(event2, "NAME1"));
    TEST_ASSERT_EQUAL_STRING("0.123", Logger_read(event2, "NAME2"));
}

/**
   コード上の箇所で発生したイベントの数を調べられることを確認する
*/
TEST(Logger, CountLocation)
{
    int event1 = Logger_setNewEvent("Location1");
    Logger_write(event1, "NAME1", "%d", 10);

    int event2 = Logger_setNewEvent(sameLoc);
    Logger_write(event2, "NAME1", "%s", "TEST_RESULT");
    Logger_write(event2, "NAME2", "%s", "TEST_RESULT");

    int event3 = Logger_setNewEvent(sameLoc);

    TEST_ASSERT_EQUAL_INT(1, Logger_countLocation("Location1"));
    TEST_ASSERT_EQUAL_INT(2, Logger_countLocation(sameLoc));
}

TEST(Logger, GetLocation)
{
    int event1 = Logger_setNewEvent("Location1");
    Logger_write(event1, "NAME1", "%d", 10);

    int event2 = Logger_setNewEvent(sameLoc);
    Logger_write(event2, "NAME1", "%s", "TEST_RESULT");
    Logger_write(event2, "NAME2", "%s", "TEST_RESULT");

    int event3 = Logger_setNewEvent(sameLoc);

    TEST_ASSERT_EQUAL_STRING("Location1", Logger_getLocation(event1));
    TEST_ASSERT_EQUAL_STRING(sameLoc, Logger_getLocation(event2));
    TEST_ASSERT_EQUAL_STRING(sameLoc, Logger_getLocation(event3));
}

/**
   イベントのコード上の箇所から、イベント番号が取得できることを確認する
*/
TEST(Logger, GetEventNumberFromLocation)
{
    int event0 = Logger_setNewEvent(sameLoc);
    int event1 = Logger_setNewEvent("Location2");
    int event2 = Logger_setNewEvent(sameLoc);
    int event3 = Logger_setNewEvent(sameLoc);
    int event4 = Logger_setNewEvent("Location5");
    int event5 = Logger_setNewEvent(sameLoc);

    TEST_ASSERT_EQUAL_INT(event0, Logger_getEventNumberFromLocation(0, sameLoc));
    TEST_ASSERT_EQUAL_INT(event2, Logger_getEventNumberFromLocation(event0 + 1, sameLoc));
    TEST_ASSERT_EQUAL_INT(event3, Logger_getEventNumberFromLocation(event2 + 1, sameLoc));
    TEST_ASSERT_EQUAL_INT(event5, Logger_getEventNumberFromLocation(event3 + 1, sameLoc));
    // 見つからない場合は、-1
    TEST_ASSERT_EQUAL_INT(-1, Logger_getEventNumberFromLocation(event5 + 1, sameLoc));
}
