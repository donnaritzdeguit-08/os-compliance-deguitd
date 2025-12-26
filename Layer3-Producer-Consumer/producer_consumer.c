#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 2

typedef struct {
	int buffer[BUFFER_SIZE];
	int in;     // index for producer
	int out;    // index for consumer
	sem_t empty; // counts empty slots
	sem_t full;  // counts full slots
	sem_t mutex; // mutual exclusion
} buffer_t;

buffer_t shared;

// Helper function to print buffer contents
void print_buffer() {
	printf("Buffer: [ ");
	for(int i = 0; i < BUFFER_SIZE; i++) {
		printf("%d ", shared.buffer[i]);
	}
	printf("]\n");
}


// Producer thread
void* producer(void *arg) {
	int id = *(int*)arg;

	while (1) {
		int item = rand() % 100;  // random item

        	sem_wait(&shared.empty);   // wait for empty slot
        	sem_wait(&shared.mutex);   // lock mutex

        	// Add item
        	shared.buffer[shared.in] = item;
        	printf("Producer %d: produced %d at index %d\n", id, item, shared.in);
        	shared.in = (shared.in + 1) % BUFFER_SIZE;

        	print_buffer();

        	sem_post(&shared.mutex);   // unlock mutex
		sem_post(&shared.full);    // increase full count

		sleep(5);
	}
}


// Consumer thread
void* consumer(void *arg) {
	int id = *(int*)arg;

	while (1) {
		sem_wait(&shared.full);    // wait for full slot
		sem_wait(&shared.mutex);   // lock mutex

		// Remove item
		int item = shared.buffer[shared.out];
		shared.buffer[shared.out] = 0; // mark empty
		printf("Consumer %d: consumed %d from index %d\n", id, item, shared.out);
		shared.out = (shared.out + 1) % BUFFER_SIZE;

        	print_buffer();

		sem_post(&shared.mutex);   // unlock mutex
        	sem_post(&shared.empty);   // increase empty count

		sleep(5);
	}
}


// Main
int main() {
	pthread_t prod[NUM_PRODUCERS];
	pthread_t cons[NUM_CONSUMERS];

	// Initialize buffer
	shared.in = 0;
	shared.out = 0;

	for(int i = 0; i < BUFFER_SIZE; i++)
        	shared.buffer[i] = 0;

    	// Initialize semaphores
    	sem_init(&shared.empty, 0, BUFFER_SIZE);
	sem_init(&shared.full, 0, 0);
	sem_init(&shared.mutex, 0, 1);

    	// Create producer threads
	int p_id[NUM_PRODUCERS];
    	for(int i = 0; i < NUM_PRODUCERS; i++) {
        	p_id[i] = i + 1;
        	pthread_create(&prod[i], NULL, producer, &p_id[i]);
    	}

    	// Create consumer threads
    	int c_id[NUM_CONSUMERS];
	for(int i = 0; i < NUM_CONSUMERS; i++) {
        	c_id[i] = i + 1;
        	pthread_create(&cons[i], NULL, consumer, &c_id[i]);
 	}

    	// Join (never ends)
	for(int i = 0; i < NUM_PRODUCERS; i++)
        	pthread_join(prod[i], NULL);

	for(int i = 0; i < NUM_CONSUMERS; i++)
        	pthread_join(cons[i], NULL);

	return 0;
}
