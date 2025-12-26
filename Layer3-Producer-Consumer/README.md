This project implements a solution to the classic **producer-consumer problem** (bounded buffer problem) using POSIX threads and semaphores. The program demonstrates thread synchronization in a multi-threaded environment where producers add items to a shared circular buffer and consumers remove items, with proper coordination to prevent race conditions and ensure thread safety.

The solution uses three semaphores to coordinate access to the shared buffer:

1. **Mutex** - It provides **mutual exclusion** to ensure only one thread (producer or consumer) can access the buffer at a time. It also protects critical sections where the buffer indices (in and out) and buffer content are modified.
2. **Empty** - It tracks the number of **empty slots** available in the buffer. Producers wait on this semaphore before producing. If empty = 0, the buffer is full and producers block.
3. **Full** - It tracks the number of **full slots** (items ready for consumption in the buffer). Consumers wait on this semaphore before consuming. If full = 0, the buffer is empty and consumers block.


**INSTRUCTIONS FOR COMPILATION AND EXECUTION:**

To compile and execute the program, first **open the Cygwin terminal and navigate to the project directory**. From there, compile the source code by entering the command make. Once compilation is successful, launch the program using **make start**. After execution, you can remove the compiled files by running the **make clean** command.
