#ifndef SYNC_H
#define SYNC_H

#include <semaphore.h>
#include <pthread.h>

// Semaphores
extern sem_t empty;
extern sem_t full;
extern sem_t mutex; // Using binary semaphore for mutex
// extern pthread_spinlock_t lock; // Commented out for mutex version

// Struct to pass parameters to threads
typedef struct {
    int upper_limit;
} thread_params_t;

// Initializes synchronization primitives
void init_sync(int buffer_size);

// Destroys synchronization primitives
void destroy_sync();

#endif // SYNC_H
