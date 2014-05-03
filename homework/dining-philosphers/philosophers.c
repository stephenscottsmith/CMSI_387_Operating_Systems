#include <pthread.h>
#include <semaphore.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WANTNOMS 0
#define NOMMING 1
#define PHILOSOPHIZING 2 

int philosopherNumber[5];
int philosopherStatus[5];

pthread_mutex_t chopstickNumber[5];
int chopstickStatus[5];


void printPhilosophers () {
	int i;

	for (i = 0; i < 5; i++) {
		if (philosopherStatus[i] == PHILOSOPHIZING) {
			printf("  T  ");
		} else if (philosopherStatus[i] == NOMMING) {
			printf("  H  ");
		} else if (philosopherStatus[i] == WANTNOMS) {
			printf("  E  ");
		}
	}
	printf("\n");
}


void* dineThePhilosophers (void* philosopher) {
	int philosopherNumber = *(int*) philosopher;
	printPhilosophers();
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