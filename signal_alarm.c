/**
 * File: signal_alarm.c
 * Modified by: Alion Bujku
 * 
 * Brief summary of program: This program sets an alarm for 5 seconds and uses
 * a signal handler to catch the SIGALRM signal and print a message when recieved
 */

 #include <stdio.h>
 #include <signal.h>
 #include <unistd.h>

 void alarm_handler(int sig) {
    printf("Received signal\n");
 }

 int main() {
    // Register signal handler with SIGALRM
    signal(SIGALRM, alarm_handler);

    // Schedule alarm for 5 seconds
    alarm(5);

    printf("Alarm set for 5 seconds...\n");

    // Wait for signal
    pause();

    return 0;
    
 }
