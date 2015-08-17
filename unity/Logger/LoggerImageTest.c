#include "unity_fixture.h"
#include "Logger/Logger_Image.h"

TEST_GROUP(LoggerImage);

#define X 1024
#define Y 300

LImage* image;

TEST_SETUP(LoggerImage)
{
    image = LoggerImage_Create(X, Y, LOGGER_IMAGE_MONO_1BIT);
}

TEST_TEAR_DOWN(LoggerImage)
{
    LoggerImage_Destroy(image);
}

IGNORE_TEST(LoggerImage, TestImage) 
{
    TEST_FAIL_MESSAGE("start here");
}

