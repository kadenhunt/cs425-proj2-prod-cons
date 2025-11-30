# CS425 Project 2: Producer-Consumer Problem with Pthreads

**Team Members:** Kaden Hunt, Nate Barner  
**Due:** November 29, 2025

## Project Overview
Implementation of the multi-producer, multi-consumer problem using pthreads with both spinlock and mutex synchronization approaches.

## Files Structure
```
├── main.tex                                    # Complete project report (LaTeX)
├── performance_comparison_updated.pdf          # Experimental results figure  
├── Makefile                                    # Build configuration
├── src/                                        # Current source code (mutex version)
│   ├── main.c                                  # Main program with timing
│   ├── buffer.c/.h                             # Shared circular buffer
│   ├── prod.c                                  # Producer thread logic
│   ├── cons.c                                  # Consumer thread logic  
│   └── sync.c/.h                               # Synchronization primitives
├── src_mutex/                                  # Backup of mutex implementation
└── prodcons                                    # Compiled executable
```

## Compilation and Usage
```bash
make clean && make                              # Compile the project
./prodcons <buffer_size> <num_producers> <num_consumers> <upper_limit> [disable_output] [critical_work]
```

**Example:**
```bash
./prodcons 20 2 3 100                          # Buffer=20, 2 producers, 3 consumers, count to 100
```

## Output Format
The program outputs consumed values with consumer IDs:
```
0, 1
1, 2  
2, 1
3, 3
...
```

## Synchronization Versions
- **Current (src/):** Uses `sem_t` binary semaphores for mutual exclusion
- **Spinlock version:** Switch by copying appropriate source files and rebuilding

## Experimental Results
Performance comparison data and analysis available in `main.tex` and `performance_comparison_updated.pdf`.