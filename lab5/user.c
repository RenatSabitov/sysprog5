#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

void handle_users() {
    struct passwd *pw;
    FILE *fp;

    // Open the output file for logging if needed
    // (Implementation for logging will be based on redirect_output)

    // Print users and home directories sorted by username
    while ((pw = getpwent()) != NULL) {
        printf("%s: %s\n", pw->pw_name, pw->pw_dir);
    }

    endpwent();
}
