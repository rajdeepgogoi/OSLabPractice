#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = ftok("shmfile", 65);  // Same key as sender
    int shmid = shmget(key, SHM_SIZE, 0666);  // Access the shared memory

    // Attach to the shared memory
    char *data = (char*) shmat(shmid, NULL, 0);

    printf("Message received: %s\n", data);

    // Detach from the shared memory
    shmdt(data);

    return 0;
}
