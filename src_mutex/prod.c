#include <stdio.h>
#include "buffer.h"
#include "sync.h"

extern int next_value;
extern long critical_section_work;

void *producer(void *param) {
    thread_params_t *params = (thread_params_t *)param;
    int item;

    while (1) {
        // Lock to get the next value
        sem_wait(&mutex);
        if (next_value >= params->upper_limit) {
            sem_post(&mutex);
            break; // All numbers produced
        }
        item = next_value++;
        
        // Critical section work (for experiments)
        for (long j = 0; j < critical_section_work; j++);
        
        sem_post(&mutex);

        sem_wait(&empty);
        
        // This small critical section for buffer insertion can also be protected by the same mutex
        sem_wait(&mutex);
        insert_item(item);
        
        // Additional critical section work (for experiments)
        for (long j = 0; j < critical_section_work; j++);
        
        sem_post(&mutex);
        
        sem_post(&full);
    }

    pthread_exit(0);
}
