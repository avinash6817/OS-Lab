#include <stdio.h>
#include <pthread.h>

long int a,b;

void *thread1(){
    for(int i=1;i<=100;i++){
        if(i % 2 == 0){
            printf("Thread-1 active\t Thread id : %ld\nEven : %d\n",a,i);
        }
    }
}

void *thread2(){
    for(int i=1;i<=100;i++){
        if(i % 2 != 0){
            printf("Thread-2 active\t Thread id : %ld\nOdd : %d\n",b,i);
        }
    }
}

int main(){
    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,thread1,NULL);
    a = tid1;

    pthread_create(&tid2,NULL,thread2,NULL);
    b = tid2;

    pthread_join(tid1,NULL);
    // printf("Thread-1 id : %ld",tid1);

    pthread_join(tid2,NULL);
    // printf("Thread-1 id : %ld",tid2);

    return 0;
}