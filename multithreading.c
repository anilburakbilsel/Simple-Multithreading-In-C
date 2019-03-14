// Concurrency in C

#include <stdio.h> 
#include <stdlib.h>
// Header file for sleep() 
#include <unistd.h> 
// Header file for threads
#include <pthread.h> 

volatile long int a = 0;
pthread_mutex_t aLock;


void threadFunc1(void *arg){
    long int localA = 0;
    int i;
    for(i = 0; i < 10; i++){
        pthread_mutex_lock(&aLock);
        a = a + i;
        pthread_mutex_unlock(&aLock);
    }
}

void threadFunc2(void *arg){
    long int localA = 0;
    int i;
    for(i = 10; i < 20; i++){
        pthread_mutex_lock(&aLock);
        a = a + i;
        pthread_mutex_unlock(&aLock);
    }
}


int main(int argc, char **argv){
    pthread_t one, two;
    int i;
    a = 0;

    pthread_mutex_init(&aLock, NULL);

    pthread_create(&one, NULL, (void*)&threadFunc1, NULL);
    pthread_create(&two, NULL, (void*)&threadFunc2, NULL);

    pthread_join(one, NULL);
    pthread_join(two, NULL);

    printf("%ld\n", a);
}