#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char ** argv) {
    pid_t child;
    int fd[2];

    int pipe_status = pipe(fd);
    if (pipe_status == -1) {
        printf("Error at open pipe.");
        return 1;
    }

    child = fork();
    if (child == -1) {
        perror("Error at fork");
        return 0;
    }

    if(child == 0) {
        //child process
        printf("Child process\n");
        close(fd[0]);
        char message [50] = "Hi from child.";
        printf("Sending message '%s' from pid(%d) with ppid(%d)", message, getpid(), getppid());
        write(fd[1], message, strlen(message));
        printf("Finish child process\n");
    } else {
        //main process
        printf("Main process\n");
        close(fd[1]);

        char message_read[50];
        read(fd[0], message_read, sizeof(message_read));
        printf("Message got '%s' from pid(%d) with ppid(%d)", message_read, getpid(), getppid());

        printf("Finish main process\n");
    }

    return 0;
}
