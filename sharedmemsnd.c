#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = ftok("shmfile", 65);  // Create unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory

    // Attach to the shared memory
    char *data = (char*) shmat(shmid, NULL, 0);

    printf("Write message: ");
    fgets(data, SHM_SIZE, stdin);  // Get user input

    printf("Message sent: %s\n", data);

    // Detach from the shared memory
    shmdt(data);

    return 0;
}
