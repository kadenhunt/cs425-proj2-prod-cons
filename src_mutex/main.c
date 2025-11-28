#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include "buffer.h"
#include "sync.h"

// Function prototypes for producer and consumer
void *producer(void *param);
void *consumer(void *param);

// Global variables
int next_value = 0;
int disable_output = 0;  // Flag to disable printf for experiments
long critical_section_work = 0;  // Amount of work in critical section

int main(int argc, char *argv[]) {
    // 1. Check and parse command-line arguments
    if (argc < 5 || argc > 7) {
        fprintf(stderr, "Usage: %s <buffer_size> <num_producers> <num_consumers> <upper_limit> [disable_output] [critical_work]\n", argv[0]);
        return -1;
    }

    int buffer_size = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);
    int upper_limit = atoi(argv[4]);
    
    // Optional parameters for experiments
    if (argc >= 6) disable_output = atoi(argv[5]);
    if (argc >= 7) critical_section_work = atol(argv[6]);

    // 2. Initialize buffer and synchronization primitives
    init_buffer(buffer_size);
    init_sync(buffer_size);

    // 3. Create producer and consumer threads
    pthread_t producer_threads[num_producers];
    pthread_t consumer_threads[num_consumers];
    
    thread_params_t thread_params;
    thread_params.upper_limit = upper_limit;

    // Start timing
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producer_threads[i], NULL, producer, &thread_params);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, &thread_params);
    }

    // 4. Wait for all threads to complete
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // End timing
    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                         (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    // 5. Clean up and exit
    destroy_buffer();
    destroy_sync();

    if (!disable_output) {
        printf("\nAll threads finished.\n");
    }
    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    return 0;
}
