#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CARS 3

int cars_on_bridge = 0;
int direction_on_bridge = -1;  // -1 represents no direction

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t can_cross;

void *ArriveBridge(void *arg) {
    int direction = *(int *)arg;

    pthread_mutex_lock(&mutex);

    // Wait until the bridge is clear for the car to enter
    while (cars_on_bridge == MAX_CARS || (cars_on_bridge > 0 && direction != direction_on_bridge)) {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }

    // Car can enter the bridge
    cars_on_bridge++;
    if (cars_on_bridge == 1) {
        direction_on_bridge = direction;
        sem_post(&can_cross);
    }

    printf("Car arrived on the bridge, direction: %d\n", direction);

    pthread_mutex_unlock(&mutex);

    // Car is on the bridge

    return NULL;
}

void *ExitBridge() {
    pthread_mutex_lock(&mutex);

    // Car is leaving the bridge
    cars_on_bridge--;
    if (cars_on_bridge == 0) {
        direction_on_bridge = -1;  // Reset direction when no cars are on the bridge
    }

    printf("Car exited the bridge\n");

    pthread_mutex_unlock(&mutex);

    // Signal that the bridge is available for others
    sem_post(&can_cross);

    return NULL;
}

int main() {
    sem_init(&can_cross, 0, 0);

    // Example usage
    pthread_t car1, car2, car3;

    int direction1 = 0, direction2 = 1, direction3 = 0;

    pthread_create(&car1, NULL, ArriveBridge, (void *)&direction1);
    pthread_create(&car2, NULL, ArriveBridge, (void *)&direction2);
    pthread_create(&car3, NULL, ArriveBridge, (void *)&direction3);

    pthread_join(car1, NULL);
    pthread_join(car2, NULL);
    pthread_join(car3, NULL);

    pthread_create(&car1, NULL, ExitBridge, NULL);
    pthread_create(&car2, NULL, ExitBridge, NULL);
    pthread_create(&car3, NULL, ExitBridge, NULL);

    pthread_join(car1, NULL);
    pthread_join(car2, NULL);
    pthread_join(car3, NULL);

    sem_destroy(&can_cross);

    return 0;
}