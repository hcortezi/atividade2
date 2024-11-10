#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writeLock = PTHREAD_MUTEX_INITIALIZER;
int readers = 0;

void *reader(void *arg) {
	int id = *((int *)arg);
	pthread_mutex_lock(&mutex);
	readers++;
	if (readers == 1) {
    	pthread_mutex_lock(&writeLock);
	}
	pthread_mutex_unlock(&mutex);

	printf("Reader %d is reading.\n", id);
	sleep(1);
	printf("Reader %d finished reading.\n", id);

	pthread_mutex_lock(&mutex);
	readers--;
	if (readers == 0) {
    	pthread_mutex_unlock(&writeLock);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *writer(void *arg) {
	int id = *((int *)arg);
	pthread_mutex_lock(&writeLock);
	printf("Writer %d is writing.\n", id);
	sleep(1);
	printf("Writer %d finished writing.\n", id);
	pthread_mutex_unlock(&writeLock);
	return NULL;
}

int main() {
	pthread_t r[5], w[2];
	int ids[5] = {1, 2, 3, 4, 5};

	for (int i = 0; i < 5; i++) {
    	pthread_create(&r[i], NULL, reader, &ids[i]);
	}
	for (int i = 0; i < 2; i++) {
    	pthread_create(&w[i], NULL, writer, &ids[i]);
	}

	for (int i = 0; i < 5; i++) {
    	pthread_join(r[i], NULL);
	}
	for (int i = 0; i < 2; i++) {
    	pthread_join(w[i], NULL);
	}
	return 0;
}
