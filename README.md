# Producer-Consumer Problem Implementation

A C implementation of the classic producer-consumer synchronization problem using pthreads. This project explores different synchronization methods and measures their performance under various conditions.

## What This Project Does

This program simulates multiple producer and consumer threads working with a shared buffer. Producers generate numbers in sequence (0, 1, 2, ...) and place them in the buffer, while consumers take numbers from the buffer and print them. The challenge is keeping everything synchronized so no data gets corrupted or lost.

## Project Structure

```
src/
├── main.c          # Main program entry point
├── buffer.c/.h     # Shared buffer implementation  
├── prod.c          # Producer thread logic
├── cons.c          # Consumer thread logic
└── sync.c/.h       # Synchronization primitives

src_mutex/          # Backup of mutex version
experiments/        # Testing scripts and results
main.tex           # Project report in LaTeX
```

## How to Build and Run

Since this uses pthreads, you need a Unix-like environment. On Windows, use WSL:

```bash
# Compile the program
make

# Run with basic parameters
./prodcons <buffer_size> <num_producers> <num_consumers> <upper_limit>

# Example: 10-slot buffer, 2 producers, 3 consumers, count to 100
./prodcons 10 2 3 100

# For experiments (disable output, add critical section work)
./prodcons 10 2 3 1000 1 100000
```

## What We're Testing

The project compares two synchronization approaches:

**Spinlock Version**: Uses pthread_spinlock_t for mutual exclusion. Threads "spin" in a loop waiting for the lock.

**Mutex Version**: Uses binary semaphores (sem_t) for mutual exclusion. Threads block and get woken up by the OS.

We measure performance under different conditions:
- Various buffer sizes
- Different numbers of producer/consumer threads  
- Different amounts of work in critical sections

## Implementation Details

Both versions ensure:
- No race conditions when accessing shared data
- Producers don't overflow the buffer
- Consumers don't try to read from empty buffer
- Numbers are produced in perfect sequence (0, 1, 2, ...)

The synchronization uses:
- `empty` semaphore: Counts available buffer slots
- `full` semaphore: Counts occupied buffer slots  
- `mutex`/`lock`: Protects critical sections

## Current Status

- ✅ Both spinlock and mutex versions implemented
- ✅ Timing measurements integrated
- ✅ Experiment infrastructure ready
- 🔄 Data collection and analysis in progress
- 📊 Report completion underway

## Contributors

- Nate Barner: Problem analysis and design documentation
- Kaden Hunt: Implementation and experimental setup