#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>

int *buffer;
int buffer_size;
int in = 0;
int out = 0;

void init_buffer(int size) {
    buffer = (int *)malloc(size * sizeof(int));
    buffer_size = size;
}

void destroy_buffer() {
    free(buffer);
}

void insert_item(int item) {
    buffer[in] = item;
    in = (in + 1) % buffer_size;
}

int remove_item() {
    int item = buffer[out];
    out = (out + 1) % buffer_size;
    return item;
}
