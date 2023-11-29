#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct {
    sem_t sem;
    pthread_mutex_t mutex;
    int count;
    pthread_t* queue;
    int front;
    int rear;
    int capacity;
} FIFO_Semaphore;

void initSemaphore(FIFO_Semaphore *s, int initialValue, int capacity) {
    s->count = initialValue;
    s->queue = (pthread_t*)malloc(sizeof(pthread_t) * capacity);
    s->front = 0;
    s->rear = -1;
    s->capacity = capacity;

    sem_init(&s->sem, 0, 0);
    pthread_mutex_init(&s->mutex, NULL);
}

void P(FIFO_Semaphore *s) {
    pthread_mutex_lock(&s->mutex);

    if (s->count > 0) {
        s->count--;
        pthread_mutex_unlock(&s->mutex);
    } else {
        s->rear = (s->rear + 1) % s->capacity;
        s->queue[s->rear] = pthread_self();
        pthread_mutex_unlock(&s->mutex);
        sem_wait(&s->sem);
    }
}

void V(FIFO_Semaphore *s) {
    pthread_mutex_lock(&s->mutex);

    if (s->rear != -1) {
        pthread_t threadToWake = s->queue[s->front];
        s->front = (s->front + 1) % s->capacity;
        sem_post(&s->sem);
        pthread_mutex_unlock(&s->mutex);

        // Allow the woken thread to acquire the mutex before releasing it
        pthread_mutex_lock(&s->mutex);
        pthread_mutex_unlock(&s->mutex);

        pthread_mutex_unlock(&s->mutex);
    } else {
        s->count++;
        pthread_mutex_unlock(&s->mutex);
    }
}

void *exampleThread(void *arg) {
    FIFO_Semaphore *sem = (FIFO_Semaphore *)arg;

    P(sem);
    printf("Thread %lu entered the critical section.\n", pthread_self());
    // Critical Section
    V(sem);

    return NULL;
}

int main() {
    FIFO_Semaphore sem;
    initSemaphore(&sem, 3, 10);

    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, exampleThread, (void *)&sem);
    pthread_create(&thread2, NULL, exampleThread, (void *)&sem);
    pthread_create(&thread3, NULL, exampleThread, (void *)&sem);
    pthread_create(&thread4, NULL, exampleThread, (void *)&sem);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;
}
