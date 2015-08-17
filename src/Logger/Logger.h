#ifndef __LOGGER__
#define __LOGGER__

void Logger_Create();
void Logger_Destroy();

int Logger_setNewEvent(char* locationName);

void Logger_write(int event, char* name, char* format, ...);
char* Logger_read(int event, char* name);
char* Logger_getLocation(int eventNumber);

int Logger_countLocation(char *locationName);

int Logger_getEventNumberFromLocation(int startEventNumber, char* searchLocationName);

#endif
