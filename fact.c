#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>


int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);

    if (num < 0) {
        fprintf(stderr, "Please provide a non-negative number.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(EXIT_FAILURE);
    } 
    // Child process
    else if (pid == 0) {
        printf("Child process: Calculating factorial sequence...\n");
        for (int i = 1; i <= num; ++i) {
            printf("%d! = %d\n", i, factorial(i));
        }
    } 
    // Parent process
    else{
        wait(NULL);  // Wait for the child process to complete
        printf("Parent process : Child process completed.\n");
    }



    return 0;
}

// ./factorial_sequence 5
