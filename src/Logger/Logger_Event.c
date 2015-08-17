#include <stdlib.h>
#include <assert.h>

#include "Logger_Event.h"
#include "Logger_Logs.h"

struct Event
{
    int number;
    char* locationName;
    Logs* logs;
};

/**
   イベントを生成する。
   @param number このイベントを表す番号（ユニーク）
   @param locationName このイベントが発生するコードの位置を特定できる名前
*/
Event* LoggerEvent_Create(int number, char* locationName)
{
    assert(number >= 0 && "number is negative");
    assert(locationName != NULL && "LoggerEvent_Create(): locationName is null");

    Event* event = (Event *)malloc(sizeof(Event));
    
    assert(event != NULL && "LoggerEvent_Create(): Cannnot allocate memory");

    event->number = number;
    event->locationName = locationName;
    event->logs = LoggerLogs_Create();

    return event;
}

/**
   イベントのログを登録する。登録済みの名前のログであっても登録できるが、
   その場合、LoggerEvent_get()で取得できるログの値は、先に登録されたログのものとなる。
   @param name ログの名前
   @param value ログの値
*/
void LoggerEvent_set(Event* recv, char* name, char* value)
{
    assert(recv != NULL && "LoggerEvent_set: recv is null");
    assert(name != NULL && "LoggerEvent_set: name is null");
    assert(name != NULL && "LoggerEvent_set: value is null");

    LoggerLogs_set(recv->logs, name, value);
}

/**
   イベント内に登録されているnameの名前のログの値を取得する。
   登録されていない名前が指定された場合、NULLを返す
   @param name ログの名前
   @return ログの値。見つからない場合NULL
*/
char* LoggerEvent_get(Event* recv, char* name)
{
    assert(recv != NULL && "LoggerEvent_get: recv is null");
    assert(name != NULL && "LoggerEvent_get: name is null");

    return LoggerLogs_get(recv->logs, name);
}

char* LoggerEvent_getLocation(Event* recv)
{
    assert(recv != NULL && "LoggerEvent_getLocation: recv is null");

    return recv->locationName;
}

/**
   イベントのメモリを開放する。
   ただし、locationNameや、ログの名前、ログの値は開放しない
*/
void LoggerEvent_Destroy(Event* recv)
{
    assert(recv != NULL && "recv is null");

    LoggerLogs_Destroy(recv->logs);
    free(recv);
}

Event** LoggerEvent_newArray(int size)
{
    assert(size > 0 && "LoggerEvent_newArray: size is negative or zero");
    
    Event** events = (Event **)malloc(sizeof(Event *) * size);
    assert(events != NULL && "LoggerEvent_newArray: Cannot allocate memory");
    
    return events;
}

Event** LoggerEvent_resizeArray(Event** events, int size)
{
    events = (Event **)realloc(events, sizeof(Event *) * size);
    assert(events != NULL && "LoggerEvent_resizeArray: Cannot allocate memory");

    return events;
}

Event* LoggerEvent_indexOfArray(Event** events, int index)
{
    assert(events != NULL && "LoggerEvent_indexOfArray: events is NULL");
    assert(index >= 0 && "LoggerEvent_indexOfArray: index is negative");

    return events[index];
}

void LoggerEvent_setArray(Event** events, int index, Event* event)
{
    assert(events != NULL && "LoggerEvent_setArray: events is NULL");
    assert(index >= 0 && "LoggerEvent_setArray: index is negative");
    assert(event != NULL && "LoggerEvent_setArray: event is NULL");

    events[index] = event;
}

