#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE_SIZE 256

int main(int argc, char** argv) {
    
    void* mmap_ptr;

     int fd = open("/tmp/mmap_shared", O_RDWR | O_CREAT, 0666);
     
     lseek(fd, MESSAGE_SIZE, SEEK_SET);
     write(fd, "", 1);
     
     mmap_ptr = mmap(NULL, MESSAGE_SIZE,
     PROT_READ | PROT_WRITE,
     MAP_SHARED, fd, 0);

    char msg[64] = "Message from mmap sender.";
    memcpy(mmap_ptr, msg, MESSAGE_SIZE);



    return 0;
}