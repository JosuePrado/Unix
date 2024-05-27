#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void signkill_handler()
{
    printf("SigKill Handler\n");
}   
void signstop_handler()
{
    printf("SigStop Handler\n");
}
void signcont_handler()
{
    printf("SigCont Handler\n");
}

void siginit_handler()
{
    printf("Ctrl + C detected, exiting the program\n");
    exit(0);
}

int main (int argc, char** argv) {
    int child_pid = fork ();
    if(child_pid == -1 )
    {
        perror("fork failed\n");
        return 1;
    }

    signal(SIGINT, &siginit_handler);
    if (child_pid == 0) {
        signal(SIGSTOP, &signstop_handler);
        signal (SIGCONT, &signcont_handler);
        int counter = 0;
        while (1) {
            printf("I am the child process %d\n", counter++);
            sleep(1);
        }
    } else {
        sleep(6);
        kill (child_pid, SIGSTOP);
        sleep(6);
        kill (child_pid, SIGCONT);
        sleep(6);
        kill(child_pid, SIGKILL);
        wait(NULL);
    }
    return 0;   
}       