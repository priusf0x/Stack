#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>
#include <time.h>

extern const size_t LOG_BUFFER_SIZE;
extern char LOG_BUFFER[];
const char LOG_FILE[] = "log/Logs.txt";

enum DetalizationLevels
{
    DETALIZATION_LEVEL_ERROR = 0,
    DETALIZATION_LEVEL_DEBUG = 1
};


FILE * GetLogFile();
FILE * OpenLogFile();
void LogMessage(const char * log_message, enum DetalizationLevels detalization_level);
void SwitchDetailLevelTo(enum DetalizationLevels detalization_level);

#define LOGSHIT(det_level, ...) snprintf(LOG_BUFFER, LOG_BUFFER_SIZE, __VA_ARGS__); LogMessage(LOG_BUFFER, det_level);

#endif
