#include <pthread.h>
#include <semaphore.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS 5
#define WANTINGNOMS 0     // HUNGRY
#define NOMMING 1		  // EATING
#define PHILOSOPHIZING 2  // THINKING

int philosopherNumber[NUMBER_OF_PHILOSOPHERS];
int philosopherStatus[NUMBER_OF_PHILOSOPHERS];

pthread_mutex_t chopstickNumber[NUMBER_OF_PHILOSOPHERS];
int chopstickStatus[NUMBER_OF_PHILOSOPHERS];


void printPhilosophers () {
	int i;

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		// Thinking
		if (philosopherStatus[i] == PHILOSOPHIZING) {
			printf("  T  ");
		// Hungry
		} else if (philosopherStatus[i] == WANTINGNOMS) {
			printf("  H  ");
		// Eating
		} else if (philosopherStatus[i] == NOMMING) {
			printf("  E  ");
		}
	}
	printf("\n");
}

// Ah, sample code for random wait. NOM NOM NOM.
int randomWait(int bound) {
    int wait = rand() % bound;
    sleep(wait);
    return wait;
}

void philosophizeAboutNoms (int philosopher) {
	randomWait(NUMBER_OF_PHILOSOPHERS);
	philosopherStatus[philosopher] = WANTINGNOMS;
}

void nom (int philosopher) {
	pickupChopstick(philosopher);
	pickupChopstick((philosopher + 1) % NUMBER_OF_PHILOSOPHERS);
	philosopherStatus[philosopher] = NOMMING;
	randomWait(NUMBER_OF_PHILOSOPHERS);
}

void pickupChopstick (int chopstick) {
	pthread_mutex_lock(&chopstickNumber[chopstick]);
	chopstickStatus[chopstick] += 1;
}

void putdownChopstick (int chopstick) {
	pthread_mutex_unlock(&chopstickNumber[chopstick]);
	chopstickStatus[chopstick] -= 1;
}

void finishNomming (int philosopher) {
	putdownChopstick(philosopher);
	putdownChopstick((philosopher + 1) % NUMBER_OF_PHILOSOPHERS);
	philosopherStatus[philosopher] = PHILOSOPHIZING;
}

void* dineThePhilosophers (void* philosopher) {
	int currentPhilosopher = *(int*) philosopher;
	printPhilosophers();

	while (1) {

		printPhilosophers();

		if (philosopherStatus[currentPhilosopher] == PHILOSOPHIZING) {
			philosophizeAboutNoms(currentPhilosopher);
		} else if (philosopherStatus[currentPhilosopher] == WANTINGNOMS) {
			nom(currentPhilosopher);
		} else if (philosopherStatus[currentPhilosopher] == NOMMING) {
			finishNomming(currentPhilosopher);
		}
	}
}


int main () {
	int i;
	// Initialize thread with NUMBER_OF_PHILOSOPHERS philosophers
	pthread_t philosphers[NUMBER_OF_PHILOSOPHERS];

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		philosopherStatus[i] = PHILOSOPHIZING;
		philosopherNumber[i] = i;
		chopstickStatus[i] = 0;
		pthread_mutex_init(&chopstickNumber[i], NULL);
		pthread_create(&philosphers[i], NULL, dineThePhilosophers, &philosopherNumber[i]);
	}

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		pthread_join(philosphers[i], NULL);
	}

	return 0;
}