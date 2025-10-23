# Operating_systems_Assignment

## ***Producer-Consumer Problem***

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is completed, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize the producer and the consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

### Compilation and Execution
Compile the producer and consumer programs:
```bash
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
g++ cleanup.cpp -lrt -o cleanup
```

### Run the programs:
```bash
./producer & ./consumer &
```

### To stop execution
```bash
pkill producer; pkill consumer
```
### Cleanup instructions
```bash
./cleanup
```

### Output code 
Produced: 1 | Count: 1  
Consumed: 1 | Count: 0  
Produced: 2 | Count: 1  
Consumed: 2 | Count: 0  
Produced: 3 | Count: 1  
Produced: 4 | Count: 2  
Consumed: 4 | Count: 1  
Produced: 5 | Count: 2  
Consumed: 5 | Count: 1  
Produced: 6 | Count: 2  
pkill producer; pkill consumer


### Explanation
1. Shared Memory
    - Stores a small buffer of size 2 and a counter count.
    - Both producer and consumer processes access this memory to share items.

2. Producer Process
    - Generates items (integers starting from 1) and adds them to the buffer.
    - Waits if the buffer is full (count == 2).
    - Uses empty and mutex semaphores to ensure proper synchronization and mutual exclusion.

3. Consumer Process
    - Removes items from the buffer.
    - Waits if the buffer is empty (count == 0).
    - Uses full and mutex semaphores to ensure proper synchronization and mutual exclusion.

4. Semaphores

    - mutex: Ensures mutual exclusion when accessing the buffer.
    - empty: Tracks the number of empty slots in the buffer.
    - full: Tracks the number of items available for consumption.

5. Cleanup
    - A separate program removes shared memory and semaphores to avoid resource leaks.
