#include <stdio.h>
#include <stdlib.h>  // Для EXIT_FAILURE
#include <unistd.h>  // Для dup2

FILE *log_file = NULL;

void redirect_output(const char *path) {
    log_file = fopen(path, "w");
    if (log_file == NULL) {
        fprintf(stderr, "Error opening log file %s\n", path);
        exit(EXIT_FAILURE);  // Теперь EXIT_FAILURE определен
    }
    dup2(fileno(log_file), STDOUT_FILENO);  // Используйте STDOUT_FILENO
}

void close_log() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}
