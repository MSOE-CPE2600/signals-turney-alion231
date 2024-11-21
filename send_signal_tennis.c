/**
 * File: send_signal_tennis.c
 * Modified by: Alion Bujku
 *
 * Brief summary of program:
 * Sends a "ball" signal (SIGUSR1) to the receiver and handles responses.
 * Ends the game after 10 volleys.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_VOLLEYS 10

int volley_count = 0;
pid_t receiver_pid;

// Signal handler for the "ball" signal
void ball_handler(int sig, siginfo_t *info, void *context) {
    printf("Received ball from PID: %d. Volley count: %d\n", info->si_pid, volley_count + 1);
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

    // Send the ball back to the receiver
    union sigval value;
    value.sival_int = volley_count;
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        exit(1);
    }
    printf("Sent ball back to PID: %d\n", receiver_pid);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver PID>\n", argv[0]);
        return 1;
    }

    receiver_pid = atoi(argv[1]);

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

    printf("Server process PID: %d\n", getpid());
    printf("Serving the ball to PID: %d\n", receiver_pid);

    // Send SIGUSR1 to the receiver
    union sigval value;
    value.sival_int = 0;
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    // Keep the program running
    while (1) {
        pause();
    }

    return 0;
}