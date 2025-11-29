#include <stdio.h>
#include "buffer.h"
#include "sync.h"

// Keep track of how many numbers have been consumed
int consumed_count = 0;
extern int disable_output;
extern long critical_section_work;

void *consumer(void *param) {
    thread_params_t *params = (thread_params_t *)param;
    int item;

    while (1) {
        // Quick check before waiting (to avoid unnecessary waits)
        pthread_spin_lock(&lock);
        int should_exit = (consumed_count >= params->upper_limit);
        pthread_spin_unlock(&lock);
        
        if (should_exit) {
            break; // All numbers consumed
        }

        sem_wait(&full);

        // Re-check after acquiring semaphore (in case we waited and condition changed)
        pthread_spin_lock(&lock);
        if (consumed_count >= params->upper_limit) {
            // Still need to remove the item and post empty to maintain buffer consistency
            item = remove_item();
            pthread_spin_unlock(&lock);
            sem_post(&empty);  // Post empty since we removed an item
            break; // All numbers consumed
        }

        // This small critical section for buffer removal can also be protected by the same spinlock
        item = remove_item();
        consumed_count++;
        
        // Critical section work (for experiments)
        volatile long dummy = 0;
        for (long j = 0; j < critical_section_work; j++) {
            dummy += j;
        }
        
        pthread_spin_unlock(&lock);

        sem_post(&empty);

        if (!disable_output) {
            printf("%d ", item);
            fflush(stdout);
        }
    }

    pthread_exit(0);
}
