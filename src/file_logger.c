#include "logger/factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    Logger base;
    FILE *fp;
} FileLogger;

static void PrintTime(FILE *f) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(f, "%02d:%02d:%02d ",
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static void FileLog(Logger *self, LogLevel level, const char *fmt, va_list args) {
    FileLogger *l = (FileLogger *)self;

    PrintTime(l->fp);
    fprintf(l->fp, "[%s] ", LogLevelToString(level));
    vfprintf(l->fp, fmt, args);
    fprintf(l->fp, "\n");
    fflush(l->fp);
}

static void FileSetLevel(Logger *self, LogLevel level) {
    self->level = level;
}

static void FileDestroy(Logger *self) {
    FileLogger *l = (FileLogger *)self;
    if (l->fp){
        fclose(l->fp);
    }
    free(l);
}

static const LoggerVTable VTABLE = {
    .log = FileLog,
    .set_level = FileSetLevel,
    .destroy = FileDestroy
};

Logger *LoggerCreateFile(const char *path) {
    FileLogger *l = malloc(sizeof(*l));
    if (!l) {
        return NULL;
    }

    l->fp = fopen(path, "a");
    if (!l->fp) {
        free(l);
        return NULL;
    }

    l->base.vtable = &VTABLE;
    l->base.level = LOG_DEBUG;
    return (Logger *)l;
}
