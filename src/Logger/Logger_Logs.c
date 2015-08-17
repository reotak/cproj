#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logger_Logs.h"

/**
   ログの線形連結リスト
*/
struct Logs {
    char* name; // ログの名前
    char* value; // ログの値

    Logs* next; // 次のログ
};


static Logs* newLog()
{
    Logs* log = (Logs *)malloc(sizeof(Logs));
    assert(log != NULL && "LoggerLogs/newLog(): Cannot allocate memory.");

    log->name = NULL;
    log->value = NULL;
    log->next = NULL;

    return log;
}

/** 
    ログのリストを生成する。
*/
Logs* LoggerLogs_Create()
{
    Logs* head = newLog();
    
    return head;
}

static Logs* getLastLog(Logs* recv)
{
    Logs* next = recv;
    while (next->next != NULL) {
	next = next->next;
    }

    return next;
}

/**
   ログのリストに値を付け加える。メモリエラー等で付け加えることができない場合、アサートする。
   もし、recvに事前に登録済みの名前でログを付け加えた場合、登録はされるが、LoggerLogs_get()を呼び出した際の結果は最初に付け加えた方の値となる。
   @param name 値の名前（キー）
   @param value 値（バリュー）
*/
void LoggerLogs_set(Logs* recv, char* name, char* value)
{
    assert(recv != NULL && "LoggerLogs_set: recv is null");
    assert(name != NULL && "LoggerLogs_set: name is null");
    assert(value != NULL && "LoggerLogs_set: value is null");

    Logs* last = getLastLog(recv);
    Logs* next = newLog();

    next->name = name;
    next->value = value;

    last->next = next;
}

/**
   nameが名前として登録されているログのvalueを抽出する。
   見つからなかった場合NULLを返す。
   @param name 名前
   @return ログのvalue。見つからない場合NULL
*/
char* LoggerLogs_get(Logs* recv, char* name)
{
    assert(recv != NULL && "LoggerLogs_get: recv is null");
    assert(name != NULL && "LoggerLogs_get: name is null");

    Logs* log = recv->next;

    while (log != NULL) {
	if (strcmp(log->name, name) == 0) {
	    return log->value;
	}
	log = log->next;
    }

    return NULL;
}
   
/**
   ログのリストを全て開放する。
   ただし、それらの名前や値として利用されている文字列は開放しない。
*/
void LoggerLogs_Destroy(Logs* recv)
{
    assert(recv != NULL && "LoggerLogs_Destroy: recv is null");
    
    Logs* target = recv;
    Logs* next;

    while (target != NULL) {
	next = target->next;
	free(target);
	target = next;
    }
}


