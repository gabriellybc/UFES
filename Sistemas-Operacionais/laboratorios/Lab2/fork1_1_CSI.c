#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.

int main() {
    pid_t pid = fork(); // Fork a child process.
    if (pid < 0) { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) { // Child process.
        printf("[CHILD]: I'm running.\n");
        for (;;);
        printf("[CHILD]: I'm finished.\n");
        return 42;
    } else { // Parent process.
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            // If child finished normally.
            printf("[PARENT]: Child returned with code %d.\n",
                   WEXITSTATUS(wstatus));
        } else if (WIFSIGNALED(wstatus)) {
            // If child was killed by signal.
            printf("[PARENT]: My child was murdered! \nThe assassin is: %d.\n",
                   WTERMSIG(wstatus));
        }
    }
    return 0;
}
