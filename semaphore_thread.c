#include <stdio.h>          // For input/output functions
#include <pthread.h>        // For pthread functions
#include <semaphore.h>      // For semaphore functions
#include <unistd.h>         // For sleep()

// Define a semaphore variable
sem_t sem;

// Function that will be executed by each thread
void* threadFunction(void* arg) {
    int thread_id = *(int*)arg; // Get thread ID from argument

    sem_wait(&sem); // Acquire semaphore (enter critical section)

    printf("Thread %d: Entered critical section\n", thread_id);
    sleep(1); // Simulate some work in critical section
    printf("Thread %d: Leaving critical section\n", thread_id);

    sem_post(&sem); // Release semaphore (exit critical section)
    return NULL;
}

int main() {
    pthread_t threads[3]; // Array to hold 3 thread IDs
    int ids[3] = {1, 2, 3}; // Thread identifiers

    sem_init(&sem, 0, 1); // Initialize semaphore to 1 (binary semaphore)

    // Create 3 threads
    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, threadFunction, &ids[i]);
    }

    // Wait for all threads to finish
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem); // Destroy semaphore
    return 0;
}
