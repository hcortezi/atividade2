#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int available = 0;

void *producer(void *arg) {
	sleep(1); // Simula tempo de produção
	pthread_mutex_lock(&mutex);
	available = 1;
	printf("Produced an item.\n");
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *consumer(void *arg) {
	pthread_mutex_lock(&mutex);
	while (!available) {
    	pthread_cond_wait(&cond, &mutex);
	}
	printf("Consumed the item.\n");
	available = 0;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main() {
	pthread_t prod, cons;
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	return 0;
}
