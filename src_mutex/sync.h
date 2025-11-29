#ifndef SYNC_H
#define SYNC_H

#include <semaphore.h>
#include <pthread.h>

// Semaphores
extern sem_t empty;
extern sem_t full;
extern sem_t mutex; // Using binary semaphore for mutex
// extern pthread_spinlock_t lock; // Commented out for mutex version
extern int production_done; // Flag to signal that all production is complete

// Struct to pass parameters to threads
typedef struct {
    int upper_limit;
    int num_consumers;
} thread_params_t;

// Initializes synchronization primitives
void init_sync(int buffer_size);

// Destroys synchronization primitives
void destroy_sync();

#endif // SYNC_H
