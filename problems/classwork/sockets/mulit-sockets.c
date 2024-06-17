#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <dirent.h>
#include <signal.h>

#define PORT 9393
#define MAX_USERS 100
#define BUFFER_SIZE 8000
#define FILES_PATH "/home/fundacion/Documents/desarrollo-unix/files"

int server_socket;
int num_clients = 0;
int num_get_requests = 0;
int num_post_requests = 0;

void sigint_handler(int signum) {
    printf("\nSe recibió la señal SIGINT. Cerrando el servidor...\n");
    printf("Número de clientes conectados: %d\n", num_clients);
    printf("Número de solicitudes GET: %d\n", num_get_requests);
    printf("Número de solicitudes POST: %d\n", num_post_requests);
    close(server_socket); 
    exit(signum);
}

void send_response(int client_socket, const char* response_status, const char* content_type, const char* body) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.0 %s\r\nContent-Type: %s\r\n\r\n%s", response_status, content_type, body);
    write(client_socket, response, strlen(response));
}

void handle_get_request(int client_socket, const char* path) {
    num_get_requests++;
    if (strcmp(path, "/") == 0) {
        DIR *dir;
        struct dirent *ent;
        char files_list[4096] = "Archivos de python:\n";
        if ((dir = opendir(FILES_PATH)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strstr(ent->d_name, ".py") != NULL) {
                    strcat(files_list, ent->d_name);
                    strcat(files_list, "\n");
                }
            }
            closedir(dir);
            send_response(client_socket, "200 OK", "text/plain", files_list);
        } else {
            send_response(client_socket, "500 Error interno en el servidor(ya fuí)", "text/plain", "Error al abrir el directorio de archivos deseado\n");
        }
    } else {
        send_response(client_socket, "404 error nemo", "text/plain", "tu archivo no se ha encontrado, seguro que lo pusiste bien? \n");
    }
}

void handle_post_request(int client_socket, const char* path) {
    num_post_requests++;

    char file_name[100];
    int result = sscanf(path, "/submit_form?file_name=%s", file_name);

    if (result != 1) {
        send_response(client_socket, "400 mala solicitud", "text/plain", "seguro que escribiste bien el Post?\n");
        printf("Tu solicitud post no me gusta\n");
        return;
    }

    int len = strlen(file_name);
    if (len <= 3 || strcmp(&file_name[len - 3], ".py") != 0) {
        send_response(client_socket, "404 error nemo", "text/plain", "ubicas que solo corro archivos .py?\n");
        printf("ponle la extension .py a tu archivo, capaz es eso\n");
        return;
    }

    char file_path[BUFFER_SIZE];
    snprintf(file_path, sizeof(file_path), "/home/fundacion/Documents/desarrollo-unix/files/%s", file_name);

    FILE *fp;

    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "python3 %s", file_path);
    fp = popen(command, "r");
    
    if (fp == NULL) {
        send_response(client_socket, "500 error interno en el servidor", "text/plain", "no puedo ejecutar el archivo .py que me diste\n");
        printf("seguro que tienes un _main_? le pasó a un amigo\n");
        return;
    }

    char output[BUFFER_SIZE];
    memset(output, 0, sizeof(output));

    while (fgets(output, sizeof(output), fp) != NULL) {
        send_response(client_socket, "200 OK", "text/plain", output);
    }

    pclose(fp);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("necesito que marques el puerto a usar\n");
        printf("asi: ./servidor -p <puerto>\n");
        return 1;
    }

    if (strcmp(argv[1], "-p") != 0) {
        printf("aqui usamos -p para ingresar el puerto, como lo hacen en tu casa?\n");
        printf("tu argumento: '%s' no me suena\n", argv[1]);
        return 1;
    }

    int port = atoi(argv[2]);
    if (port != PORT) {
        printf("hoy trabajamos en el puerto: %d\n", PORT);
        return 1;
    }

    signal(SIGINT, sigint_handler);

    int client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error al crear el socket \n");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error al vincular el socket \n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error al escuchar conexiones entrantes \n");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1) {
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Error al aceptar la conexión \n");
            exit(EXIT_FAILURE);
        }

        num_clients++;
        printf("Número de clientes conectados: %d\n", num_clients);

        char request[BUFFER_SIZE];
        read(client_socket, request, sizeof(request));

        char method[10], path[100];
        sscanf(request, "%s %s", method, path);

        printf("Método: %s, Ruta: %s\n", method, path);

        if (strcmp(method, "GET") == 0) {
            handle_get_request(client_socket, path);
        } else if (strcmp(method, "POST") == 0) {
            handle_post_request(client_socket, path);
        } else {
            send_response(client_socket, "400 Bad Request", "text/plain", "aca solo gets y posts \n");
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}