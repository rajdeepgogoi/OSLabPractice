#include <stdio.h>          // For printf
#include <pthread.h>        // For thread and mutex functions
#include <unistd.h>         // For sleep()

// Declare two mutex locks
pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

// Function for first thread
void* threadFunc1(void* arg) {
    // Lock mutex A first
    pthread_mutex_lock(&lockA);
    printf("Thread 1 acquired lockA\n");

    sleep(1); // Simulate delay

    // Then attempt to lock mutex B (will wait if B is locked)
    pthread_mutex_lock(&lockB);
    printf("Thread 1 acquired lockB\n");

    // Release both locks
    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);

    return NULL;
}

// Function for second thread
void* threadFunc2(void* arg) {
    // Lock mutex B first (opposite order)
    pthread_mutex_lock(&lockB);
    printf("Thread 2 acquired lockB\n");

    sleep(1); // Simulate delay

    // Then attempt to lock mutex A
    pthread_mutex_lock(&lockA);
    printf("Thread 2 acquired lockA\n");

    // Release both locks
    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, threadFunc1, NULL);
    pthread_create(&t2, NULL, threadFunc2, NULL);

    // Wait for both threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
