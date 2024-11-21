/**
 * File: send_signal.c
 * Modified by: Alion Bujku
 * 
 * Brief summary of program:
 * This program sends a SIGUSR1 signal along with a random integer value to a
 * process specified by its PID using sigqueue
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <time.h>

 int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    // Parse from command line
    pid_t pid = atoi(argv[1]);

    // Seed random number
    srand(time(NULL));

    // Generate random number
    int random_value = rand() % 100;

    // Set up signal value
    union sigval value;
    value.sival_int = random_value;

    // Send signal with value
    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    printf("Sent SIGUSR1 to process %d with value: %d\n", pid, random_value);

    return 0;
 }
