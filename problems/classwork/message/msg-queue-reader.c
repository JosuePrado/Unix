#include <stdio.h>
#include <sys/msg.h>

#define MESSAGE_SIZE 64

struct msg_struct {
    long msg_type;
    char msg_content[MESSAGE_SIZE];
};


int main(int argc, char** argv) {
    

    printf("Enter main");
    int msg_queue_id;
    struct msg_struct message;
    
    msg_queue_id = msgget((key_t)5678, IPC_CREAT | 0666);
    
    if(msg_queue_id == -1) {
        perror("Error at message queue get.");
        return 1;
    }
    
    msgrcv(msg_queue_id, (void*)&message, MESSAGE_SIZE, 0, 0);
    printf("Message read form queue: %s\n", message.msg_content);
    msgctl(msg_queue_id, IPC_RMID, 0);

    //el sigueinte programa que lea la cola debe sacar este paquete, debe saber dq tipo es la estructura y sacar
    return 0;
}