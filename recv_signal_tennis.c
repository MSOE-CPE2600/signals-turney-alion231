/**
 * File: recv_signal_tennis.c
 * Modified by: Alion Bujku
 *
 * Brief summary of program:
 * Receives a "ball" signal and sends it back to the server after waiting for a random time.
 * Keeps track of volleys and ends the game after 10 volleys.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_VOLLEYS 10

int volley_count = 0;
pid_t sender_pid;

// Signal handler for the "ball" signal
void ball_handler(int sig, siginfo_t *info, void *context) {
    sender_pid = info->si_pid; // Get the PID of the sender
    printf("Received ball from PID: %d. Volley count: %d\n", sender_pid, volley_count + 1);
    printf("\a"); // Play system bell to simulate hitting the ball

    // Increment the volley count
    volley_count++;

    // End the game after 10 volleys
    if (volley_count >= MAX_VOLLEYS) {
        printf("Game over! Total volleys: %d\n", volley_count);
        exit(0);
    }

    // Wait for a random time between 1 and 2 seconds
    int wait_time = rand() % 2 + 1;
    sleep(wait_time);

    // Send the ball back to the server
    union sigval value;
    value.sival_int = volley_count;
    if (sigqueue(sender_pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        exit(1);
    }
    printf("Sent ball back to PID: %d\n", sender_pid);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = ball_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    printf("Receiver process PID: %d\n", getpid());
    printf("Waiting for the ball...\n");

    // Keep the program running
    while (1) {
        pause();
    }

    return 0;
}