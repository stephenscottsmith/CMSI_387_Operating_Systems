#include <pthread.h>
#include <semaphore.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WANTINGNOMS 0
#define NOMMING 1
#define PHILOSOPHIZING 2 

int philosopherNumber[5];
int philosopherStatus[5];

pthread_mutex_t chopstickNumber[5];
int chopstickStatus[5];


void printPhilosophers () {
	int i;

	for (i = 0; i < 5; i++) {
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
	randomWait(5);
	philosopherStatus[philosopher] = WANTINGNOMS;
}

void nom (int philosopher) {
	pickupChopstick(philosopher);
	pickupChopstick((philosopher + 1) % 5);
	philosopherStatus[philosopher] = NOMMING;
	randomWait(5);
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
	putdownChopstick((philosopher + 1) % 5);
	philosopherStatus[philosopher] = PHILOSOPHIZING;
}

void* dineThePhilosophers (void* philosopher) {
	int currentPhilosopher = *(int*) philosopher;
	printPhilosophers();

	while (1) {

		printPhilosophers();
		
		if (philosopherStatus[currentPhilosopher] == PHILOSOPHIZING) {
			philosophizeAboutNoms(currentPhilosopher);
		} else if (philosopherStatus[currentPhilosopher] == NOMMING) {
			nom(currentPhilosopher);
		} else if (philosopherStatus[currentPhilosopher] == WANTINGNOMS) {
			finishNomming(currentPhilosopher);
		}
	}
}


int main () {
	int i;
	// Initialize thread with 5 philosophers
	pthread_t philosphers[5];

	for (i = 0; i < 5; i++) {
		philosopherStatus[i] = PHILOSOPHIZING;
		philosopherNumber[i] = i;
		chopstickStatus[i] = 0;
		pthread_mutex_init(&chopstickNumber[i], NULL);
		pthread_create(&philosphers[i], NULL, dineThePhilosophers, &philosopherNumber[i]);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(philosphers[i], NULL);
	}

	return 0;
}