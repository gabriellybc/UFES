#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.
#include <errno.h>

int main() {
    pid_t pid = fork(); // Fork a child process.
    if (pid < 0) { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) { // Child process.
        printf("[CHILD]: I'm running.\n");
        sleep(1000);
        printf("[CHILD]: I'm finished.\n");
        return 42;
    } else { // Parent process.
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        int test;
        do {
            test = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
            if (test == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            // Checking child exit status
            if (WIFEXITED(wstatus)) {
                // If child finished normally.
                printf("[PARENT]: Child returned with code %d.\n",
                    WEXITSTATUS(wstatus));
            } else if (WIFSIGNALED(wstatus)) {
                // If child was killed by signal.
                printf("[PARENT]: My child was murdered! \nThe assassin is %d.\n",
                        WTERMSIG(wstatus));
            } else if (WIFSTOPPED(wstatus)) {
                // If child was stopped by signal.
                printf("[PARENT]: My child was stopped by %d.\n",
                        WSTOPSIG(wstatus));
            }
        } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
        exit(EXIT_SUCCESS);

    }
    //printf("I, %d, finished running!", getpid());
    return 0;
}
