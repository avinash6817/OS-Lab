#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t hydrogen_sem;
    sem_t oxygen_sem;
    pthread_mutex_t mutex;
    int hydrogen_count;
} WaterMonitor;

void initWaterMonitor(WaterMonitor *monitor) {
    sem_init(&monitor->hydrogen_sem, 0, 0);
    sem_init(&monitor->oxygen_sem, 0, 0);
    pthread_mutex_init(&monitor->mutex, NULL);
    monitor->hydrogen_count = 0;
}

void Hydrogen(WaterMonitor *monitor) {
    pthread_mutex_lock(&monitor->mutex);

    monitor->hydrogen_count++;
    if (monitor->hydrogen_count == 2) {
        // Wake up waiting oxygen thread
        sem_post(&monitor->oxygen_sem);
    } else {
        // Wait for the other hydrogen atom
        pthread_mutex_unlock(&monitor->mutex);
        sem_wait(&monitor->hydrogen_sem);
    }

    // Form water molecule
    printf("Hydrogen atom formed water molecule.\n");

    pthread_mutex_unlock(&monitor->mutex);
}

void Oxygen(WaterMonitor *monitor) {
    pthread_mutex_lock(&monitor->mutex);

    // Wait for two hydrogen atoms
    sem_wait(&monitor->oxygen_sem);

    // Form water molecule
    printf("Oxygen atom formed water molecule.\n");

    // Signal both waiting hydrogen atoms
    sem_post(&monitor->hydrogen_sem);
    sem_post(&monitor->hydrogen_sem);

    pthread_mutex_unlock(&monitor->mutex);
}

void *hydrogenThread(void *arg) {
    WaterMonitor *monitor = (WaterMonitor *)arg;
    Hydrogen(monitor);
    return NULL;
}

void *oxygenThread(void *arg) {
    WaterMonitor *monitor = (WaterMonitor *)arg;
    Oxygen(monitor);
    return NULL;
}

int main() {
    WaterMonitor monitor;
    initWaterMonitor(&monitor);

    // Example usage
    pthread_t hydrogen1, hydrogen2, oxygen;

    pthread_create(&hydrogen1, NULL, hydrogenThread, (void *)&monitor);
    pthread_create(&hydrogen2, NULL, hydrogenThread, (void *)&monitor);
    pthread_create(&oxygen, NULL, oxygenThread, (void *)&monitor);

    pthread_join(hydrogen1, NULL);
    pthread_join(hydrogen2, NULL);
    pthread_join(oxygen, NULL);

    return 0;
}
