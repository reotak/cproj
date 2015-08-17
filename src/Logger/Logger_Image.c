#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "Logger_Image.h"

/* BPM形式をサポート */

/* BPM形式(?)のファイルヘッダ */
typedef struct FileHeader {
    uint16_t fileType; // 2byte : ファイル・タイプ 0x42,0x4d ("BM") 
    uint32_t fileSize; // 4byte : ファイル・サイズ バイト	   
    uint16_t reserved1; // 2byte : 予約領域1 常に0		   
    uint16_t reserved2; // 2byte : 予約領域2 常に0		   
    uint32_t offset; // 4byte : 画像データまでのオフセット	   
} FileHeader;

/* BPM形式)の情報ヘッダ */
typedef struct InfoHeader {
    uint32_t headSize;	  // 4byte : 情報ヘッダのサイズ バイト	   
    uint32_t width;	  // 4byte : 画像の幅 ピクセル		   
    uint32_t height;	  // 4byte : 画像の高さ ピクセル	    
    uint16_t plane;	  // 2byte : プレーン数 常に1		   
    uint16_t colorSize;	  // 2byte : 1画素あたりの色数 ビット	   
    uint32_t complessionFormat;	  // 4byte : 圧縮形式		   
    uint32_t dataSize;	  // 4byte : 画像データのサイズ バイト	   
    uint32_t xResolution;  // 4byte : 水平解像度 ppm		   
    uint32_t yResolution;  // 4byte : 垂直解像度 ppm		   
    uint32_t parret;	  // 4byte : パレットの色数		   
    uint32_t parretIndex; // 4byte : 重要のパレットのインデックス  
} InfoHeader;

/** ロガーの画像としてBPM画像をサポート */
struct LImage {
    FileHeader fileHeader;
    InfoHeader infoHeader;
    int realWidth; // 実際の画像の幅のバイト数（BMPは4バイト単位）
    void* image;
};

static void setDefault(LImage* image)
{
    image->fileHeader.fileType = 0x424d; // 2byte : ファイル・タイプ 0x42,0x4d ("BM")
//    image->fileHeader.fileSize; // 4byte : ファイル・サイズ バイト	      
    image->fileHeader.reserved1 = 0; // 2byte : 予約領域1 常に0		      
    image->fileHeader.reserved2 = 0; // 2byte : 予約領域2 常に0		      
    image->fileHeader.offset = 0; // 4byte : 画像データまでのオフセット	      

    image->infoHeader.headSize = 40;    // 4byte : 情報ヘッダのサイズ バイト     
//    image->infoHeader.width;	  // 4byte : 画像の幅 ピクセル		   
//    image->infoHeader.height;	  // 4byte : 画像の高さ ピクセル	   
    image->infoHeader.plane;	  // 2byte : プレーン数 常に1		   
//    image->infoHeader.colorSize;	  // 2byte : 1画素あたりの色数 ビット	   
    image->infoHeader.complessionFormat = 0;	  // 4byte : 圧縮形式		   
//    image->infoHeader.dataSize;	  // 4byte : 画像データのサイズ バイト	   
    image->infoHeader.xResolution = 100;  // 4byte : 水平解像度 ppm		      
    image->infoHeader.yResolution = 100;  // 4byte : 垂直解像度 ppm		      
//?    image->infoHeader.parret;	  // 4byte : パレットの色数		   
//?    image->infoHeader.parretIndex; // 4byte : 重要のパレットのインデックス  
}


LImage* LoggerImage_Create(int xdot, int ydot, ColorModel colorModel)
{
    assert(xdot > 0 && "LoggerImage_Create: xdot is zero or negative");
    assert(ydot > 0 && "LoggerImage_Create: ydot is zero or negative");

    int wantSizeByte;
    LImage* image = (LImage *)malloc(sizeof(LImage));

    setDefault(image);

    assert(image != NULL && "LoggerImage_Create: Cannot allocate memory.");
    
    // colorModelを調べて、画像サイズ、
    switch (colorModel) {
    case LOGGER_IMAGE_RGB_8BIT :
	
	break;
    case LOGGER_IMAGE_MONO_1BIT :
	
	break;
    case LOGGER_IMAGE_MONO_8BIT :

	break;
    default :
	assert("LoggerImage_Create: undefined colorModel");
    }

    return NULL;
}

void LoggerImage_Destroy(LImage* recv)
{
    assert(recv != NULL && "LoggerImage_Destroy: recv is null");

    free(recv);
}
