## Repo for Lab Week 10
## Part 1:
### Research Questions
#### What is a signal disposition?
A signal disposition determines how the process behaves when the signal is delivered.
#### What is a signal handler? What is it used for?
A signal handler is a programmer-defined function that is automatically invoked when the
signal is delivered. It is used for determining one of the following behaviors to occur
on delivery of the signal. It can either perform the default action, ignore the signal, 
or catch the signal.
#### Name and describe each of the five (5) default dispositions?
```
Term - Default action is to terminate the process
Ign - Default action is to ignore the process
Core - Default action is to terminate the process and dump core
Stop - Default action is to stop the process
Cont - Default action is to continue the process if it is currently stopped
```
#### Name and describe one way to programmatically send a signal to a process. Be able to give an example (the code) to send a signal.
One way to send a signal to a process is by using the kill() system call. This function sends a specified signal to a process or group of processes.

##### Example:
```
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        while(1) {
            printf("Child process running...\n");
            sleep(1);
        }
    } else if (pid > 0) {
        sleep(5);
        printf("Sending SIGTERM to child process...\n");
        kill(pid, SIGTERM);
    } else {
        perror("fork failed");
    }
    return 0;
}
```
#### Name and describe one way to send a signal to a process from the command line. Be able to give an example (the command, key combination, etc.) to send a signal.
One way to send a signal is using the kill command to send a signal to a process by its PID

##### Example:
```
1. Find the PID:
    'ps aux | grep <process_name>
2. Send a signal:
    'kill -SIGTERM 12345'

This sends the SIGTERM signal to the process with PID 12345
```

#### Signal Types:
* SIGINT 
    - Description: Is sent when user interrupts a process from keyboard
    - Default Disposition: Terminates the process
    - Overridable: Yes it can be overridden by a signal handler to perform custom actions instead of termination
* SIGTERM 
    - Description: Sent to request termination signal
    - Default Disposition: Terminates the process
    - Overridable: Yes a signal handler can override it to allow cleanup before termination
* SIGUSR1 
    - Description: User-defined signal for custom use
    - Default Disposition: Terminates the process
    - Overridable: Yes since it is designed for user-defined purposes
* SIGKILL 
    - Description: Forces immediate termination of process
    - Default Disposition: Terminates the process unconditionally
    - Overridable: No it cannot be caught or ignored for safety and system control purposes 
* SIGSTOP
    - Description: Stops(pauses) a process
    - Default Disposition: Stops the process execution
    - Overridable: No it cannot be caught or ignored to ensure processes can always be stopped

## Part 2:
#### Be able to describe how you sent SIGINT to the process and the behavior of the process when SIGINT is handled.
I first determined the PID of the process by using the function 'ps aux | grep <process_name>'. Once I determined the PID, I used 
'kill -SIGINT <PID>', which killed the process. The other way to kill the process was using CTRL + C.
#### Describe the behavior of the code after modifying the code. Determine how to make the process exit.
The code ran the nearly the same as before. The only differences to point out is the fact that when trying to terminate the process using the same methods as before, the signal is recieved but the process will not end.
I had to again first determine the PID using the function: 'ps aux | grep <process_name>'. Once the PID was found then I used 
'kill -SIGKILL <PID>', which killed the process and printed out killed.

## Part 3:
#### Run the program and observe the results. What do you observe? Why is this happeneing?
After adding in the signal handler the output seems to be an infinite loop until the system is terminated. This happens because once the signal was handled the program goes back to dereferencing i which causes it to continuously print out that a segmentation error was received, leading into an infinite loop. 

Note, no make file is provided.  It is suggested you create one to be more efficient building your programs.