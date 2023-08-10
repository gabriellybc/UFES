#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.

int main(int argc, char *argv[]) {
    if (argc < 2) {
		fprintf (stderr, "Usage: %s command arg1 arg2 ... \n", argv[0]);
		return 1;
	}
    printf("Number of parameters: %d\n", argc);
    for (int i=0; i<argc; i++){
        printf("%d = %s\n", i, argv[i]);
    }
	
    return 0;
}