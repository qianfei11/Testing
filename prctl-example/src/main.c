#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "prctl_lib.h"

int main(int argc, char *argv[]) {
    const char *new_name = "MyProcess";

    if (argc > 1) {
        new_name = argv[1];
    }

    printf("Original process name: ");
    // Note: Getting the original name programmatically is non-trivial.
    // For demonstration purposes, we'll skip retrieving it.

    printf("Setting process name to '%s'\n", new_name);

    if (set_process_name(new_name) != 0) {
        fprintf(stderr, "Failed to set process name to '%s'\n", new_name);
        return 1;
    }

    printf("Process name set successfully.\n");

    // Keep the process running so you can observe the name change
    printf("Sleeping for 60 seconds. Check the process name using 'ps' or 'top'.\n");
    sleep(60);

    return 0;
}

