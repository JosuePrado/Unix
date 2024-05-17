#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024

int main (int argc, char** argv) {
    int shm_id;
    void* shm_ptr;
    char buffer[256];
    //valor del id del espacio de meoria = key que comparten todos los procesos, tamanio, permisos
    shm_id = shmget((key_t) 3475, SHM_SIZE,
        0666 | IPC_CREAT );

    if (shm_id == -1) {
        perror("Error at shmget");
        return 1; 
    } 

    //puntero a la memoria =  id de la referencia del sistema, referencia del puntero, banderas
    shm_ptr = shmat(shm_id, NULL, 0);
    printf("Enter message for shared memory \n");
    read(0, buffer, 256);

    strcpy(shm_ptr, buffer);

    printf("The message sent: %s \n", buffer);
    return 0;
}