#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "Logger.h"
#include "Logger_Event.h"
#include "string.h"

#define DEFAULT_MAX_EVENT_SIZE 4
#define MAX_LOG_SIZE 2000

/** 最後に登録したイベントの番号 */
static int lastEventNumber = -1; 

/** 現在メモリ上に確保しているイベント数 */
static int maxEventNumber = DEFAULT_MAX_EVENT_SIZE;

/** ロガーが保持しているイベント */
static Event** events;

/**
   イベント等の情報を一切持たない新たなロガーを生成する。
   このロガーはシングルトンである。
*/
void Logger_Create()
{
    lastEventNumber = -1;
    maxEventNumber = DEFAULT_MAX_EVENT_SIZE;
    events = LoggerEvent_newArray(maxEventNumber);
}

/**
   ロガーに残っているデータを削除する。
   この関数を呼び出した後に、Logger_Createを呼び出すことで、ロガー上の情報をリセットして再度利用可能となる。
   ログの名前や値や、イベントの場所名のメモリは開放しない
*/
void Logger_Destroy()
{
    int i;

    for (i = 0; i < lastEventNumber; i++) {
	free(LoggerEvent_indexOfArray(events, i));
    }
    free(events);
    lastEventNumber = 0;
    maxEventNumber = 0;
}

/**
   新たなイベントを生成する。このイベントにログを登録するには、この関数の戻り値であるイベント番号が必要である。
   @param locationName このイベントが発生したコードの箇所の名前。コードの箇所は常にユニークであることを期待する
   @return イベント番号
*/
int Logger_setNewEvent(char* locationName)
{
    assert(locationName != NULL && "Logger_setNewEvent: locationName is null");
    
    int nextEventNum = lastEventNumber + 1;

    /* 既に容量いっぱいまでイベントが保存されている場合 */
    if (nextEventNum > maxEventNumber) {
	maxEventNumber *= 2; /* 容量を二倍に伸長 */
	events = LoggerEvent_resizeArray(events, maxEventNumber);
    }

    LoggerEvent_setArray(events, nextEventNum, LoggerEvent_Create(nextEventNum, locationName));

    lastEventNumber = nextEventNum;

    return nextEventNum;
}
 
/**
   ログを書き込む
   @param eventNumber イベント番号
   @param name 書き込みたいログの名前
   @param format 書き込みたいログのフォーマット
   @param 可変長 フォーマットに対応した値
*/
void Logger_write(int eventNumber, char* name, char* format, ...)
{
    assert(eventNumber >= 0 && "Logger_write: eventNumber is negative");
    assert(eventNumber <= lastEventNumber && "Logger_write: eventNumber is too large");
    assert(name != NULL && "Logger_write: name is null");
    assert(format != NULL && "Logger_write: format is null");

    va_list ap;

    /* buffは初期値は広く取るが、後で縮める */
    char *buff = (char *)calloc(MAX_LOG_SIZE, sizeof(char));

    assert(buff != NULL && "Logger_write: Cannot allocate memory in calloc");

    /* ログの値を取得する */
    va_start(ap, format);
    vsprintf(buff, format, ap);
    va_end(ap);

    /* buff を縮める */
    buff = (char *)realloc(buff, sizeof(char) * (strlen(buff) + 1));
    assert(buff != NULL && "Logger_write: Cannot allocate memory in realloc");

    /* ログをセットする */
    LoggerEvent_set(LoggerEvent_indexOfArray(events, eventNumber), name, buff);
}

/**
   ログを読み取る
   @param eventNumber イベント番号
   @param name ログの名前
*/
char* Logger_read(int eventNumber, char* name)
{
    assert(eventNumber >= 0 && "Logger_read: eventNumber is negative");
    assert(eventNumber <= lastEventNumber && "Logger_read: eventNumber is too large");
    assert(name != NULL && "Logger_read: name is null");

    return LoggerEvent_get(LoggerEvent_indexOfArray(events, eventNumber), name);
}

/**
   イベントの発生したコードの箇所を取得する
   @param eventNumber イベント番号
*/
char* Logger_getLocation(int eventNumber)
{
    assert(eventNumber >= 0 && "Logger_getLocation: eventNumber is negative");
    assert(eventNumber <= lastEventNumber && "Logger_getLocation: eventNumber is too large");

    return LoggerEvent_getLocation(LoggerEvent_indexOfArray(events, eventNumber));
}

/**
   同じ箇所で発生したイベントの数を数える
   @parma locationName コード上の箇所
*/
int Logger_countLocation(char *locationName)
{
    assert(locationName != NULL && "Logger_countLocation: locationName is null");

    int count = 0;
    int i;
    char* locName;

    for (i = 0; i <= lastEventNumber; i++) {
	locName =  LoggerEvent_getLocation(LoggerEvent_indexOfArray(events, i));
	if (strcmp(locationName, locName) == 0) {
	    count++;
	}
    }
    
    return count;
}


/**
   startEventNumberの次にLocationがsearchLocationNameであるイベント番号を返します
   @param startEventNumber 探し始めるイベント番号
   @param searchLocataionName 探すLocationの名前
   @return そのLocationを持つイベント番号。見つからなかった場合 -1
*/
int Logger_getEventNumberFromLocation(int startEventNumber, char* searchLocationName)
{
    assert(startEventNumber >= 0 && "Logger_getEventNumberFromLocation: startEventNumber is negative");
    assert(searchLocationName != NULL && "Logger_getEventNumberFromLocation: searchLocationName is null");

    int i;

    for (i = startEventNumber; i <= lastEventNumber; i++) {
	if (strcmp(searchLocationName, LoggerEvent_getLocation(LoggerEvent_indexOfArray(events, i))) == 0) {
	    return i;
	}
    }
	
    return -1;
}
