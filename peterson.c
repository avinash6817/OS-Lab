#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int turn;
int interested[2] = {FALSE, FALSE};

void enter_critical_section(int process_number) {
    int other_process = 1 - process_number;
    interested[process_number] = TRUE;
    turn = process_number;
    
    while (turn == process_number && interested[other_process] == TRUE);
    // Critical Section
    printf("Process %d is in critical section.\n", process_number);
}

void leave_critical_section(int process_number) {
    interested[process_number] = FALSE;
    printf("Process %d left critical section.\n", process_number);
}

void* process(void* arg) {
    int process_number = *(int*)arg;

    while (TRUE) {
        enter_critical_section(process_number);

        // Critical Section
        printf("Process %d is executing in critical section.\n", process_number);

        leave_critical_section(process_number);

        // Remainder Section
        printf("Process %d is in remainder section.\n", process_number);

        // Simulating non-critical section work
        sleep(rand() % 5);
    }
}

int main() {
    pthread_t thread[2];
    int process_numbers[2] = {0, 1};

    // Initialize pthreads
    pthread_create(&thread[0], NULL, process, (void*)&process_numbers[0]);
    pthread_create(&thread[1], NULL, process, (void*)&process_numbers[1]);

    // Join pthreads
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);




    return 0;
}
