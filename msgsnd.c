// sender.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);              // Create unique key
    int msgid = msgget(key, 0666 | IPC_CREAT);     // Create message queue

    struct msg_buffer message;
    message.msg_type = 1;

    printf("Write message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin); // Get user input

    // Send the message (excluding msg_type size)
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Message sent: %s", message.msg_text);
    return 0;
}
