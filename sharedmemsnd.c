#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    printf("Write: ");
    fgets(str, 1024, stdin);  // Safer input

    // Remove newline character, if present
    str[strcspn(str, "\n")] = 0;

    printf("Data written: %s\n", str);

    shmdt(str);  // Detach shared memory

    return 0;
}
