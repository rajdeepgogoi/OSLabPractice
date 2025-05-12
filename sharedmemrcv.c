#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    printf("Data read from shared memory: %s\n", str);

    shmdt(str);               // Detach
    shmctl(shmid, IPC_RMID, NULL);  // Optional: Delete shared memory

    return 0;
}
