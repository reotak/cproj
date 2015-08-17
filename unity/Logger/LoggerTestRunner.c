#include "unity_fixture.h"

TEST_GROUP_RUNNER(Logger)
{
    RUN_TEST_CASE(Logger, SetNewEvent);
    RUN_TEST_CASE(Logger, WriteAndRead);
    RUN_TEST_CASE(Logger, CountLocation);
    RUN_TEST_CASE(Logger, GetLocation);
    RUN_TEST_CASE(Logger, GetEventNumberFromLocation);
}
