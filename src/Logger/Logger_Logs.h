#ifndef __LOGGER_LOGS__
#define __LOGGER_LOGS__

typedef struct Logs Logs;

Logs* LoggerLogs_Create();

void LoggerLogs_set(Logs* recv, char* name, char* value);
char* LoggerLogs_get(Logs* recv, char* name);

void LoggerLogs_Destroy(Logs* logs);

#endif
