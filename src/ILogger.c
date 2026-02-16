#include "logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *LogLevelToString(LogLevel level) {
    switch (level) {
        case LOG_DEBUG: return "DEBUG";
        case LOG_INFO:  return "INFO";
        case LOG_WARN:  return "WARN";
        case LOG_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void LoggerLog(Logger *logger, LogLevel level, const char *fmt, ...) {
    if (!logger || level < logger->level) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    logger->vtable->log(logger, level, fmt, args);
    va_end(args);
}

void LoggerSetLevel(Logger *logger, LogLevel level) {
    if (!logger) {
    return;
    }
    logger->vtable->set_level(logger, level);
}

void LoggerDestroy(Logger *logger) {
    if (!logger) {
        return;
    } 
    logger->vtable->destroy(logger);
}
