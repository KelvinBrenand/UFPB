#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define QTD_THREADS 10
#define MAX 50.0
float x = 0.0, y = 0.0;
sem_t mutex1, mutex2;

void *par(void *p){
    long idx = (long)p;
    srand(clock());
    do
    {
        sem_wait(&mutex1);
        x += rand() % (int)(10 + 1 - 0.5) + 0.5;
        printf("[#%ld] x = %.2f\n", idx, x);
        puts("..");
        sem_post(&mutex1);
        usleep(250);
    } while (x+y < MAX);
    exit(0); //Diferente da return ou da pthread_exit, a funcao exit encerra a thread main imediatamente, bem como todas as threads filhas.
}
void *impar(void *p){
    long idx = (long)p;
    srand(clock());
    do
    {
        sem_wait(&mutex2);
        y += rand() % (int)(7.5 + 1 - 2.5) + 2.5;
        printf("[#%ld] y = %.2f\n", idx, y);
        puts("..");
        sem_post(&mutex2);
        usleep(rand() % (300 + 1 - 100) + 100);
    } while (x+y < MAX);
    exit(0);
}
int main(){
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    pthread_t threads[QTD_THREADS];
    for (long i = 0; i < QTD_THREADS; ++i){
		if (i%2 == 0){
            pthread_create(&threads[i], NULL, par, (void*)i);
        }else{
            pthread_create(&threads[i], NULL, impar, (void*)i);
        }
	}
    for (int i = 0; i < QTD_THREADS; ++i){
        pthread_join(threads[i], NULL);
	}
    printf("O programa será finalizado.\n");
    return 0;
}
