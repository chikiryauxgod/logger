#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H

#include "logger.h"

Logger *LoggerCreateConsole(void);
Logger *LoggerCreateFile(const char *path);

#endif
