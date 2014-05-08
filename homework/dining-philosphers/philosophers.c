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

// JD: Missing from this display is the chopstick state.  Not absolutely
//     required, but as you might imagine this would be really helpful
//     in following what's going on.
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
    // JD: Why is the number of philosophers the basis for waiting?  This implies
    //     that your philosopher will tend to wait longer if there are more
    //     philosophers at the table...?
	randomWait(NUMBER_OF_PHILOSOPHERS);
	philosopherStatus[philosopher] = WANTINGNOMS;
}

void nom (int philosopher) {
    // JD: You need a forward declaration of pickupChopstick.
	pickupChopstick(philosopher);
	pickupChopstick((philosopher + 1) % NUMBER_OF_PHILOSOPHERS);
	philosopherStatus[philosopher] = NOMMING;
	randomWait(NUMBER_OF_PHILOSOPHERS);
}

void pickupChopstick (int chopstick) {
	pthread_mutex_lock(&chopstickNumber[chopstick]);
    // JD: Sanity check needed here---make sure the chopstick isn't taken
    //     before you pick it up.
	chopstickStatus[chopstick] += 1;
}

void putdownChopstick (int chopstick) {
    // JD: This is reversed---change state *before* unlocking the chopstick,
    //     not after!  The moment you unlock, someone else can butt in.

    // JD: In addition, sanity check needed here---make sure the chopstick
    //     isn't available before you put it down.
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
	printPhilosophers(); // JD: If printing is outside a critical section, you
                         //     run the risk of multiple threads printing
                         //     concurrently, thus producing a garbled display.

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