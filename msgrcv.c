// receiver.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);              // Same key as sender
    int msgid = msgget(key, 0666 | IPC_CREAT);     // Access message queue

    struct msg_buffer message;

    // Receive message of type 1
    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

    printf("Message received: %s", message.msg_text);

    // Optional: Delete the message queue after receiving
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
