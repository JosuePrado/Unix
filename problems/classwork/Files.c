#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char** args) {

    int fd = open("Files.c", O_RDONLY);
    printf("id: %d\n", fd);

    if (fd == -1) {
        perror("error");
        return 1;
    }

    char buffer[40];
    int read_status = read(fd, buffer, sizeof(char) * 40);

    if (read_status == -1) {
        perror("error in: ");
        return 2;
    }
    printf("read content: %s", buffer);
    close(fd);

    int fd_w = open("example.txt", O_CREAT | O_RDWR, 0666);
    if (fd_w == -1) {
        perror("Error write");
        return 1;
    }   
    

    return 0;
}