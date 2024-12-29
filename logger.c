#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "utils.h"

void log_operation(const char *operation, const char *result) {
    FILE *logfile = fopen("operation_log.txt", "a");
    if (!logfile) {
        perror("Log file open failed");
        return;
    }

    time_t now = time(NULL);
    if (now == -1) {
        fprintf(stderr, "Failed to get current time\n");
        fclose(logfile);
        return;
    }

    struct tm *tm_info = localtime(&now);
    if (!tm_info) {
        fprintf(stderr, "Failed to convert time\n");
        fclose(logfile);
        return;
    }

    char time_buffer[26];
    if (strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info) == 0) {
        fprintf(stderr, "Failed to format time\n");
        fclose(logfile);
        return;
    }

    fprintf(logfile, "%s | Operation: %s | Result: %s\n", time_buffer, operation, result);
    fclose(logfile);
}
