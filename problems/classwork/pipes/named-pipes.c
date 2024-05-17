#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv[])
{
    int fd;
    char* shared_fifo = "/tmp/shared_fifo";
    int fifo_status = mkfifo(shared_fifo, 0666);
    if(fifo_status == -1){
        perror("Error creating fifo");
        return 1;
    }
    
    fd = open(shared_fifo, O_RDWR);
    pid_t child = fork();
    if(child == 1){
        perror("Error at fork");
        return 1;
    }
    if(child == 0){
        // child process
        int w_elems[10] = {1,2,3,4,5,6,7,8,9,10};
        write(fd, w_elems, sizeof(int) * 10);
    }else{
        // main process
        int r_elems[10];
        read(fd, r_elems, sizeof(int) * 10);
        for (int i = 0; i < 10; i++)
        {
            printf("%d", r_elems[i]);
        }
        printf("\n");
        
    }
    close(fd);
    return 0;
}