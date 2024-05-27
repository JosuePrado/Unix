#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE_SIZE 256

int main(int argc, char** argv) {
    
    void* mmap_ptr;
    int fd = open("/tmp/mmap_shared", O_RDWR | O_CREAT, 0666);
    mmap_ptr = mmap(NULL, MESSAGE_SIZE,
     PROT_READ | PROT_WRITE,
     MAP_SHARED, fd, 0);
    
    if(mmap_ptr == -1) {
        perror("Error getting map");
        return 1;
    }
    
    char msg[64];
    memcpy(msg, mmap_ptr, MESSAGE_SIZE);
    printf("Message read from mmap: %s\n", msg);

    return 0;
}