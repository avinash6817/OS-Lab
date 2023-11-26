#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readCount = 0, data = 0;

void *reader(void *arg) {
    int readerId = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d read data: %d\n", readerId, data);
        sleep(1);

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writerId = *((int *)arg);
    while (1) {
        sem_wait(&wrt);

        // Writing section
        data++;
        printf("Writer %d wrote data: %d\n", writerId, data);
        sleep(2);

        sem_post(&wrt);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[3], writers[2];
    int readerIds[3] = {1, 2, 3};
    int writerIds[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
