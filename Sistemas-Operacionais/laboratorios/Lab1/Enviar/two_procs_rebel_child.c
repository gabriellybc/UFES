#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int glob = 6;

int main(void) {
	int var; 			/* external variable in initialized data */
	pid_t pid;			/* automatic variable on the stack */
	var = 88;
	printf("before fork\n");
	
	if ( (pid = fork()) < 0)
		fprintf(stderr, "fork error\n");
	else if (pid == 0) { 		/* ***child*** */
		// Modify child process group id:
        if (setpgid(getpid(), 346) != 0){
            printf("Error on changing PGID!\n");
        } else {
            printf("Rebel child!\n");
        }
	}
	else
		sleep(1);		/* ***parent***; try to guarantee that child ends first*/
	
	printf("pid = %d, ppid = %d, uid = %d, pgid = %d\n",
         getpid(), getppid(), getuid(), getpgid(getpid()));
	return 0;
}
