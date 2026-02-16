#include "logger/factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    Logger base;
} ConsoleLogger;

static void PrintTime(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d:%02d:%02d ",
           tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static void ConsoleLog(Logger *self, LogLevel level, const char *fmt, va_list args) {
    (void)self;

    PrintTime();
    printf("[%s] ", LogLevelToString(level));
    vprintf(fmt, args);
    printf("\n");
}

static void ConsoleSetLevel(Logger *self, LogLevel level) {
    self->level = level;
}

static void ConsoleDestroy(Logger *self) {
    free(self);
}

static const LoggerVTable VTABLE = {
    .log = ConsoleLog,
    .set_level = ConsoleSetLevel,
    .destroy = ConsoleDestroy
};

Logger *LoggerCreateConsole(void) {
    ConsoleLogger *l = malloc(sizeof(*l));
    if (!l) {
        return NULL;
    }

    l->base.vtable = &VTABLE;
    l->base.level = LOG_DEBUG;
    return (Logger *)l;
}
