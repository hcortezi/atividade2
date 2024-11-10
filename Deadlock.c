#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *task1(void *arg) {
	pthread_mutex_lock(&lockA);
	sleep(1); // Simula tempo de processamento
	pthread_mutex_lock(&lockB);

	printf("Task 1 is in critical section.\n");

	pthread_mutex_unlock(&lockB);
	pthread_mutex_unlock(&lockA);
	return NULL;
}

void *task2(void *arg) {
	pthread_mutex_lock(&lockB);
	sleep(1); // Simula tempo de processamento
	pthread_mutex_lock(&lockA);

	printf("Task 2 is in critical section.\n");

	pthread_mutex_unlock(&lockA);
	pthread_mutex_unlock(&lockB);
	return NULL;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, task1, NULL);
	pthread_create(&t2, NULL, task2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
