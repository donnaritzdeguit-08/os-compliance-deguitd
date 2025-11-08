#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t chopsticks[NUM_PHILOSOPHERS];

void think(int id);
void pick_up_chopsticks(int id);
void eat(int id);
void put_down_chopsticks(int id);


void* philosopher(void* num) {
	int id = *(int*)num;
	while(1){
	   think(id);
	   pick_up_chopsticks(id);
	   eat(id);
	   put_down_chopsticks(id);
	}
   return NULL;
}


int main() {
	int i;
	int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
	for (i = 0; i < NUM_PHILOSOPHERS; i++)
           sem_init(&chopsticks[i], 0, 1);

    // Create philosopher threads
	for (i = 0; i < NUM_PHILOSOPHERS; i++) {
           ids[i] = i;
           pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    	}

    // Wait for threads to finish (they actually loop forever)
	for (i = 0; i < NUM_PHILOSOPHERS; i++)
           pthread_join(philosophers[i], NULL);

    return 0;
}


void think(int id) {
	printf("Philosopher %d is thinking.\n", id + 1);
	sleep(1);
}

void pick_up_chopsticks(int id) {
	if (id % 2 == 0) {  // Odd philosophers pick left first
	   sem_wait(&chopsticks[id]);  // Pick left chopstick
	   sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick right chopstick
	} else {  // Even philosophers pick right first
	   sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick right chopstick
	   sem_wait(&chopsticks[id]);  // Pick left chopstick
    	}
	printf("Philosopher %d picked up chopsticks.\n", id + 1);
}

void eat(int id) {
	printf("Philosopher %d is eating.\n", id + 1);
	sleep(1);
}

void put_down_chopsticks(int id) {
	   sem_post(&chopsticks[id]);  // Put down left
	   sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right
	printf("Philosopher %d put down chopsticks.\n", id + 1);
}

