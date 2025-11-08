**DEADLOCK PREVENTION STRATEGY (ASYMMETRIC):**

I chose the asymmetric strategy for its simple and straightforward approach to eliminating deadlocks. By having odd-numbered philosophers pick up their left chopstick first and even-numbered philosophers pick up their right first, the strategy ensures that at least two philosophers will compete for the same initial resource, preventing a universal, symmetrical deadlock. For instance, if Philosopher 1 (odd) grabs his left, and Philosopher 2 (even) grabs his right, they are now both competing for the same chopstick (the one between them), meaning one will get it and proceed, while the other waits. This creates a situation where at least one philosopher can always get two chopsticks and eat, thereby keeping the system moving and preventing a deadlock.


**INSTRUCTIONS FOR COMPILATION AND EXECUTION:**

To compile and execute the program, first **open the Cygwin terminal and navigate to the project directory**. From there, compile the source code by entering the command **make**. Once compilation is successful, launch the program using **make start**. After execution, you can remove the compiled files by running the **make clean** command.
