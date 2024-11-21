/**
 * File: signal_sigaction
 * Modified by: Alion Bujku
 * 
 * Brief summary of program: The program registers a signal handler for SIGUSR1 using
 * sigaction and prints the PID of the process that sent the signal
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int sig, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 from process with PID: %d\n", info->si_pid);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = sigusr1_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while(1) {
        pause();
    }


    return 0;
}

