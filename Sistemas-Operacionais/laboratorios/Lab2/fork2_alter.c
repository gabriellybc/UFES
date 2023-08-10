#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.

int main(int argc, char *argv[]) {
    if (argc < 2) {
		fprintf (stderr, "Usage: %s command arg1 arg2 ... \n", argv[0]);
		return 1;
	}

    pid_t pid = fork(); // Fork a child process.
    if (pid < 0) { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) { // Child process.
        printf("[CHILD]: About to load command.\n");
        execvp(argv[1], &argv[1]);
	    
        printf("[CHILD]: I'm finished.\n");
        return 42;
    } else { // Parent process.
        printf("[PARENT]: Waiting on child.\n");
        wait(NULL);
        printf("[PARENT]: Child finished.\n");
    }
    return 0;
}