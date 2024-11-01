#include <stdio.h>
#include <stdlib.h>  // Для EXIT_FAILURE
#include <unistd.h>  // Для dup2 и STDERR_FILENO

FILE *error_file = NULL;

void redirect_errors(const char *path) {
    error_file = fopen(path, "w");
    if (error_file == NULL) {
        fprintf(stderr, "Error opening error file %s\n", path);
        exit(EXIT_FAILURE);  // Теперь EXIT_FAILURE определен
    }
    dup2(fileno(error_file), STDERR_FILENO);  // Используйте STDERR_FILENO
}

void close_errors() {
    if (error_file) {
        fclose(error_file);
        error_file = NULL;
    }
}
