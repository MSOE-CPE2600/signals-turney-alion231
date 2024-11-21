/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Alion Bujku
 * 
 * Brief summary of modifications: Added signal handler for SIGSEGV signal and print a
 * message instead of allowing program to terminate
 */


#include <stdio.h>
#include <signal.h>

// Signal handler for SIGSEGV
void segfault_handler(int sig) {
    printf("Segmentation fault received. Continuing execution...\n");
}

int main (int argc, char* argv[]) {
    // Register signal handler for SIGSEGV
    signal(SIGSEGV,segfault_handler);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}