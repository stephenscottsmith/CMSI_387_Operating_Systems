#include <pthread.h>
#include <semaphore.h>

#define WANTNOMS 0
#define NOMMING 1
#define PHILOSOPHIZING 2 

int philosopher[5];
int philosopherStatus[5];

pthread_mutex_t chopsticks[5];
int chopstickStatus[5];

int main () {
	int i;
	// Initialize thread with 5 philosophers
	pthread_t philosphers[5];

	for (i = 0; i < 5; i++) {
		philosopherStatus[i] = PHILOSOPHIZING;
		philosopher[i] = i;
		chopstickStatus[i] = 0;
		pthread_mutex_init(&chopsticks[i], NULL);
		pthread_create(&philosphers[i], NULL, dineThePhilosophers, &philosopher[i]);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(philosphers[i], NULL);
	}

	return 0;
}