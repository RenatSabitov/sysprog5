#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void handle_processes() {
    DIR *proc_dir;
    struct dirent *entry;

    if ((proc_dir = opendir("/proc")) == NULL) {
        fprintf(stderr, "Error opening /proc directory\n");
        return;
    }

    while ((entry = readdir(proc_dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            printf("Process ID: %s\n", entry->d_name);
        }
    }

    closedir(proc_dir);
}
