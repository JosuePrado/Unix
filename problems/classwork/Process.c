#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) 
{
  printf("main pid: %d, parent pid: %d\n", 
          getpid(), getppid());
  
  // sleep(10);

  pid_t child_pid_status = fork();

  if (child_pid_status == 0) {
    // child process
    printf("at child process pid(%d), ppid(%d)\n", getpid(), getppid());
    sleep(5);
    printf("Finish child block\n");
  } else {
    // parent process
    printf("main process pid(%d), ppid(%d)\n", getpid(), getppid());

    // wait for the child process
    wait(NULL);

    printf("Finish parent block\n");
  }

  // printf("child_pid_status: %d\n", child_pid);
  printf("Finish main process pid(%d), ppid(%d).\n", getpid(), getppid());

  return 0;
}