/*
    Illustrating that you can be interrupted while executing a signal 
handler.

    Also shows that the signal for the currently executing handles is 
blocked until we return from that call, but that pending signals are 
merged and then delivered afterwards.

    Demonstrating:
    - Hit ^\ to jump into sig_quit.
    - Hit ^\ again and note that we're not interrupting the sleep inside
the sig_quit handler. However, the signal gets delivered once sig_quit 
finishes, so we re-enter sig_quit.

    Multiple signals of the same kind are merged, so hitting ^\ multiple
times while in sig_quit oly yields a single signal being delivered 
after finishing the sig_quit.

    However:
    - Hit ^\ than ^C and note that sig_int executes immediately. We 
were transfered out of sig_quit, then returned immediately back into
sig_quit

    Finally, note that if you hit ^\, then ^\ again, then ^C, you should
see us entering sig_quit, then sig_int, then re-enter sig_quit without the
first sig_quit invocation having terminated, since jumping out of the
handler unblocked the signal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // For the syscall functions.
#include <signal.h>     // For the signal functions.

#ifndef SLEEP
#define SLEEP 5
#endif

int s = 0;

static void sig_quit(int signo){
    (void)signo;
    (void)printf("\nIn sig_quit, s=%d. Now sleeping...\n", ++s);

    /*
        This call to sleep(3) can itself be interrupted if we receive a
        signal other than SIGQUIT while executing this signal handler.
        If that happens, then we jump into the other signal handler.
        When that hadler completes, we are returned back here.
    */
    (void)sleep(SLEEP);
    (void)printf("\nsig_quit, s=%d: exiting.\n", s);

}

static void sig_int(int signo){
    (void)signo;
    (void)printf("\nNow in sig_int, s=%d. Returning immediately.\n", ++s);

}

int main(int argc, char* argv[]){
    printf("\n=> Establishing initial signal handler via signal(3).\n");

    if (signal(SIGQUIT, sig_quit) == SIG_ERR){
        (void)fprintf(stderr, "can't set signal handler!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sig_int) == SIG_ERR){
        (void)fprintf(stderr, "can't set signal handler!\n");
        exit(EXIT_FAILURE);
    }

    (void)sleep(SLEEP);

    (void)printf("\n=> Time for a second interruption.\n");
    (void)sleep(SLEEP);
    (void)printf("\n=> Now exiting.\n");
    exit(EXIT_SUCCESS);

}