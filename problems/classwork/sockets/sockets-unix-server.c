#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char** argv) {
    int server_socket_fd;
    char* socket_path = "/tmp/sock_server";
    server_socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(server_socket_fd == -1) {
        perror("Socket creation failed\n");
        return 1;
    }
    struct sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, socket_path);
    int socket_size = sizeof(server_addr);

    int bind_status = bind (server_socket_fd, (struct sockaddr*)&server_addr, socket_size);

    if(bind_status == -1) {
        perror("Bind failed\n");
        return 1;
    }

    int listen_status = listen(server_socket_fd, 5);
    if(listen_status == -1) {
        perror("Listen failed\n");
        return 1;
    }
    struct sockaddr_un* client_addr;
    int socket_size_client = sizeof(client_addr);
    int client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr,&socket_size_client);
    if (client_socket_fd == -1) {
        perror("Accept failed");
        return 1;
    }

    char buffer[64];
    read ( client_socket_fd, &buffer, 64);
    printf("Message received from the client %s\n", buffer);
    write(client_socket_fd, "OK", 2);

    close (client_socket_fd);
    close (server_socket_fd);
    return 0;
}