#include "sync.h"

sem_t empty;
sem_t full;
sem_t mutex;
// pthread_spinlock_t lock; // Commented out for mutex version

void init_sync(int buffer_size) {
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1); // Binary semaphore initialized to 1
    // pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
}

void destroy_sync() {
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    // pthread_spin_destroy(&lock);
}
