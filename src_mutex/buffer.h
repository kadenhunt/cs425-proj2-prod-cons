#ifndef BUFFER_H
#define BUFFER_H

// The buffer will be a circular array of integers
extern int *buffer;
extern int buffer_size;
extern int in;  // Index for the next item to be produced
extern int out; // Index for the next item to be consumed

// Initializes the buffer
void init_buffer(int size);

// Destroys the buffer
void destroy_buffer();

// Inserts an item into the buffer
void insert_item(int item);

// Removes an item from the buffer
int remove_item();

#endif // BUFFER_H
