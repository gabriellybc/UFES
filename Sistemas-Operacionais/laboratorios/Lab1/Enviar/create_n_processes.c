#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int N = 5; // Number of child processes to create
    pid_t pid = 100;
    
    for (int i = 0; i < N; i++) {
        if (pid > 0){ 
            pid = fork();
        } else if (pid < 0) {
            printf("Error using fork!\n");
            break;
        } else {
            break;
        }
    }
    sleep(10);
    printf("I'm process %d, child of %d.\n", getpid(), getppid());
    return 0;
}
