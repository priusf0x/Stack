#include "Logger.h"

#include <stdio.h>
#include <stdlib.h>

const size_t LOG_BUFFER_SIZE = 100;
static enum DetalizationLevels DETALIZATION_LEVEL = DETALIZATION_LEVEL_DEBUG;
char LOG_BUFFER[LOG_BUFFER_SIZE] = {0};

FILE*
GetLogFile()
{
    static FILE * log_file = OpenLogFile();
    return log_file;
}

FILE*
OpenLogFile()
{
    FILE * log_file = fopen(LOG_FILE, "a+");
    if (log_file == NULL)
    {
        fprintf(stderr, "FAILED TO READ FILE\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    fprintf(log_file, "\n-------------------------------------\n");
    return log_file;
}

void
LogMessage(const char * log_message,
           enum DetalizationLevels detalization_level)
{
    FILE * log_file = GetLogFile();
    if (detalization_level <= DETALIZATION_LEVEL)
    {
        time_t t1 = time(NULL);
        tm t = *localtime(&t1);
        fprintf(log_file, "\n <%.2d:%.2d:%.2d> ", t.tm_hour, t.tm_min, t.tm_sec);
        fprintf(log_file, log_message);
    }
}

void SwitchDetailLevelTo(enum DetalizationLevels detalization_level)
{
    DETALIZATION_LEVEL = detalization_level;
}







