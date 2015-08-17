#ifndef __LOGGER_EVENT__
#define __LOGGER_EVENT__

typedef struct Event Event;

Event* LoggerEvent_Create(int number, char* locationName);

void LoggerEvent_set(Event* recv, char* name, char* value);
char* LoggerEvent_get(Event* recv, char* name);
char* LoggerEvent_getLocation(Event* recv);

Event** LoggerEvent_newArray(int size);
Event** LoggerEvent_resizeArray(Event** events, int size);
Event* LoggerEvent_indexOfArray(Event** events, int index);
void LoggerEvent_setArray(Event** events, int index, Event* event);

void LoggerEvent_Destroy(Event* recv);
#endif
