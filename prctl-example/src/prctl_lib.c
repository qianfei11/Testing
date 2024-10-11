#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/prctl.h>
#include "prctl_lib.h"

int set_process_name(const char *name) {
    if (name == NULL) {
        errno = EINVAL;
        return -1;
    }

    // prctl(PR_SET_NAME, ...) expects a string with a maximum of 16 bytes,
    // including the terminating null byte.
    char comm[16];
    strncpy(comm, name, sizeof(comm) - 1);
    comm[sizeof(comm) - 1] = '\0'; // Ensure null-termination

    if (prctl(PR_SET_NAME, (unsigned long)comm, 0, 0, 0) == -1) {
        perror("prctl(PR_SET_NAME) failed");
        return -1;
    }

    return 0;
}

