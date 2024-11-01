#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "process.h"
#include "help.h"
#include "log.h"
#include "errors.h"

void print_usage() {
    printf("Usage: my_console_utility [options]\n");
    printf("Options:\n");
    printf("  -u, --users          Show users and their home directories\n");
    printf("  -p, --processes      Show running processes sorted by ID\n");
    printf("  -h, --help           Show this help message\n");
    printf("  -l PATH, --log PATH  Log output to specified file\n");
    printf("  -e PATH, --errors PATH Log errors to specified file\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    int log_enabled = 0;
    int errors_enabled = 0;
    char *log_path = NULL;
    char *error_path = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--users") == 0) {
            handle_users();
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--processes") == 0) {
            handle_processes();
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0) {
            if (++i < argc) {
                log_path = argv[i];
                log_enabled = 1;
            } else {
                fprintf(stderr, "Error: missing log file path\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--errors") == 0) {
            if (++i < argc) {
                error_path = argv[i];
                errors_enabled = 1;
            } else {
                fprintf(stderr, "Error: missing error file path\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (log_enabled) {
        redirect_output(log_path);
    }

    if (errors_enabled) {
        redirect_errors(error_path);
    }

    // Clean up and exit
    if (log_enabled) {
        close_log();
    }

    if (errors_enabled) {
        close_errors();
    }

    return 0;
}
