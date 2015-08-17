#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(LoggerLogs);
    RUN_TEST_GROUP(LoggerEvent);
    RUN_TEST_GROUP(Logger);
    RUN_TEST_GROUP(LoggerImage);
}

int main(int argc, const char* argv[])
{    
    return UnityMain(argc, argv, RunAllTests);
}
