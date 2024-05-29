#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

#define MESSAGE_SIZE 64


struct msg_struct
{
    long msg_type;
    char msg_content[MESSAGE_SIZE];
};

int main (int argc, char** argv) {
    key_t key; 
    int msg_queue_id;
    struct msg_struct message;
    int exit = 0;

    key = ftok("msgQueue", 65); 

    msg_queue_id= msgget (key, 0666);

    if (msg_queue_id == -1) {
        perror("msgget failed\n");
        return 1;
    }
    
    while (!exit){
        msgrcv(msg_queue_id, (void *) &message, MESSAGE_SIZE, 0, 0);
        printf("Message received from the Queue %s\n" , message.msg_content);
        if (strncmp(message.msg_content, "exit", 4) == 0){
            exit = 1;
        }
    }
    msgctl(msg_queue_id, IPC_RMID, 0);
    printf("Reader Finish\n");


    return 0;
}