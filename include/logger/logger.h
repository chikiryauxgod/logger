#ifndef LOGGER_H
#define LOGGER_H

#include "config.h"
#include <stdarg.h>

typedef struct Logger Logger;

typedef struct {
    void (*log)(Logger *self, LogLevel level, const char *fmt, va_list args);
    void (*set_level)(Logger *self, LogLevel level);
    void (*destroy)(Logger *self);
} LoggerVTable;

struct Logger {
    const LoggerVTable *vtable;
    LogLevel level;
};

void LoggerLog(Logger *logger, LogLevel level, const char *fmt, ...);
void LoggerSetLevel(Logger *logger, LogLevel level);
void LoggerDestroy(Logger *logger);

#endif
