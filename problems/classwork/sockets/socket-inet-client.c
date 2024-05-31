#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE_SIZE 256

int main() {
    int client_socket_fd;
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd == -1) {
        perror("Error at socket init.");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9595);

    int connect_status = connect(client_socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if (connect_status == -1) {
        perror("Error at connect");
        return 2;
    }

    char message[MESSAGE_SIZE] = "Hello from client";
    int write_status = write(client_socket_fd, message, strlen(message) + 1);
    if (write_status == -1) {
        perror("Error at write");
        return 3;
    }

    char buffer[MESSAGE_SIZE];
    int read_status = read(client_socket_fd, buffer, MESSAGE_SIZE);
    if (read_status == -1) {
        perror("Error at read");
        return 4;
    }

    printf("Message from server: %s\n", buffer);

    close(client_socket_fd);

    return 0;
}
