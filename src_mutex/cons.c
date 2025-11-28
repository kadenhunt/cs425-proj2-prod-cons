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
        // Lock to check the consumed count
        sem_wait(&mutex);
        if (consumed_count >= params->upper_limit) {
            sem_post(&mutex);
            break; // All numbers consumed
        }
        sem_post(&mutex);

        sem_wait(&full);

        // This small critical section for buffer removal can also be protected by the same mutex
        sem_wait(&mutex);
        item = remove_item();
        consumed_count++;
        
        // Critical section work (for experiments)
        for (long j = 0; j < critical_section_work; j++);
        
        sem_post(&mutex);

        sem_post(&empty);

        if (!disable_output) {
            printf("%d ", item);
            fflush(stdout);
        }
    }

    pthread_exit(0);
}
