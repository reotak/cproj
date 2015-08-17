#ifndef __LOGGER_IMAGE__
#define __LOGGER_IMAGE__

typedef struct LImage LImage;

// TODO:なに定義すればいいの？
typedef enum ColorModel
{
    LOGGER_IMAGE_RGB_8BIT,
    LOGGER_IMAGE_MONO_1BIT,
    LOGGER_IMAGE_MONO_8BIT,
} ColorModel;

LImage* LoggerImage_Create(int x, int y, ColorModel colorModel);
void LoggerImage_Destroy(LImage* recv);
#endif

