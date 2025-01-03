#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Press Ctrl+C again to exit.\n", sig);
    exit(-1);
}

int main() {
    // Register the signal handler
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Error registering signal handler");
        return 1;
    }

    printf("Program is running in an infinite loop. Press Ctrl+C to test the signal handler.\n");

    // Infinite loop
    while (1) {
        printf("Running...\n");
        sleep(1); // Sleep for a second to avoid high CPU usage
    }

    return 0;
}

