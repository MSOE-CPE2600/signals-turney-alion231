/**
 * File: recv_signal.c
 * Modified by: Alion Bujku
 * 
 * Brief summary of program:
 * This program registers a signal handler for SIGUSR1 using sigaction. It retrieves
 * and prints the integer value sent with the signal using sigqueue
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int sig, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 with value %d\n", info->si_value.sival_int);
}

int main() {
    struct sigaction sa;

    // Set up struct
    sa.sa_sigaction = sigusr1_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    // Register handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Receiver process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    // Infinite loop
    while(1) {
        pause();
    }

    return 0;
    
}