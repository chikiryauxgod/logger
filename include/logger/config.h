#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

const char *LogLevelToString(LogLevel level);

#endif
