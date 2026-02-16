#include "logger/factory.h"

int main(void) {
    Logger *console = LoggerCreateConsole();
    Logger *file = LoggerCreateFile("app.log");

    LoggerSetLevel(console, LOG_DEBUG);
    LoggerSetLevel(file, LOG_INFO);

    LoggerLog(console, LOG_DEBUG, "debug value=%d", 42);
    LoggerLog(console, LOG_INFO, "service started");

    LoggerLog(file, LOG_DEBUG, "not visible");
    LoggerLog(file, LOG_ERROR, "fatal error code=%d", -1);

    LoggerDestroy(console);
    LoggerDestroy(file);
}
