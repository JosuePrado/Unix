#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

#define MESSAGE_SIZE 64
struct msg_struct{
        long msg_type;
        char msg_content[MESSAGE_SIZE];
    };


int main (int   argc, char** argv) {
    key_t key; 
    int msg_queue_id ;
    struct msg_struct message;
    char buffer[MESSAGE_SIZE];
    int exit = 0;
    key = ftok("msgQueue", 65); 

    msg_queue_id =msgget(key, IPC_CREAT | 0666);

    if (msg_queue_id == -1) {
        perror("msgget failed\n");
        return 1;
    }

    message.msg_type = 1;

    while (!exit){
        printf ("Enter a message to send to the Queue: ");
        fgets (buffer, MESSAGE_SIZE, stdin); 
        strcpy (message.msg_content, buffer);
        msgsnd(msg_queue_id, (void *)&message, MESSAGE_SIZE, 0);
        printf("Message sent the Queue %s\n" , message.msg_content);
        if (strncmp(buffer, "exit", 4) == 0){
            exit = 1;
        }
    }
    printf("Out of the program\n");
    return 0;
}