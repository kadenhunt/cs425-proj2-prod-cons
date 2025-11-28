#!/bin/bash

# Experiment script for producer-consumer timing analysis
# Usage: ./run_experiments.sh [mutex|spinlock]

SYNC_TYPE=${1:-mutex}
RESULTS_FILE="src/experiments/results/results_${SYNC_TYPE}.txt"

echo "Running experiments with $SYNC_TYPE synchronization..."
echo "Results will be saved to $RESULTS_FILE"
echo ""

# Create results directory if it doesn't exist
mkdir -p src/experiments/results

# Clear previous results
echo "Synchronization,Buffer_Size,Num_Producers,Num_Consumers,Upper_Limit,Critical_Work,Elapsed_Time" > "$RESULTS_FILE"

# Experiment parameters
BUFFER_SIZES=(10 20 30 40 50 100)
THREAD_COMBINATIONS=("1,1" "1,5" "5,1" "2,2" "3,3" "5,5")
CRITICAL_WORK_VALUES=(0 100000 1000000)
UPPER_LIMIT=10000

echo "Starting experiments..."

for buffer_size in "${BUFFER_SIZES[@]}"; do
    for threads in "${THREAD_COMBINATIONS[@]}"; do
        IFS=',' read -r producers consumers <<< "$threads"
        for work in "${CRITICAL_WORK_VALUES[@]}"; do
            echo "Testing: Buffer=$buffer_size, Producers=$producers, Consumers=$consumers, Work=$work"
            
            # Run the experiment 3 times and take average
            total_time=0
            for run in {1..3}; do
                result=$(./prodcons "$buffer_size" "$producers" "$consumers" "$UPPER_LIMIT" 1 "$work" | grep "Elapsed time:" | awk '{print $3}')
                total_time=$(echo "$total_time + $result" | bc -l)
            done
            avg_time=$(echo "scale=6; $total_time / 3" | bc -l)
            
            # Save result
            echo "$SYNC_TYPE,$buffer_size,$producers,$consumers,$UPPER_LIMIT,$work,$avg_time" >> "$RESULTS_FILE"
        done
    done
done

echo "Experiments completed! Results saved to $RESULTS_FILE"
