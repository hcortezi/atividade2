#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4
pthread_barrier_t barrier;

void *task(void *arg) {
	int id = *((int *)arg);
	printf("Thread %d waiting at the barrier.\n", id);
	pthread_barrier_wait(&barrier);
	printf("Thread %d passed the barrier.\n", id);
	return NULL;
}

int main() {
	pthread_t threads[NUM_THREADS];
	int ids[NUM_THREADS];

	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	for (int i = 0; i < NUM_THREADS; i++) {
    	ids[i] = i;
    	pthread_create(&threads[i], NULL, task, &ids[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++) {
    	pthread_join(threads[i], NULL);
	}

	pthread_barrier_destroy(&barrier);
	return 0;
}
