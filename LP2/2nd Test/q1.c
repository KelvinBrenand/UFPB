/*
    Faça um programa em C/C++ que simule o controle de temperatura de um motor. 
O programa deverá ter uma variável global do tipo int chamada temperatura (que 
armazenará a temperatura em Celsius do motor, com valor inicial 600 C) e três 
threads além da main, realizando funções diferentes. A primeira thread 
realizará um incremento na temperatura com um valor aleatório entre -10 e 50 e 
depois dormirá 300ms. A segunda thread realizará um incremento na temperatura 
com valor aleatório entre -20 e 20 e depois dormirá 400ms. A terceira thread 
deverá conter um mecanismo que detecte o quanto antes quando o valor da 
temperatura ultrapassar 1000C, reduzindo o valor da variável global para 600 
novamente. O programa deverá ser finalizado depois de 5 reduções de temperatura 
do motor.
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define QTD_THREADS 3
#define MAX_REDUCOES 5
#define MAX_TEMP 1000
int temperatura = 600;
int reducoes = 0;
int number = 1;
int next = 1;
int turn[QTD_THREADS];

void *function1(void *p){
    long idx = (long)p; //Armazena o identificador da thread.
    srand(clock());
    while(reducoes != MAX_REDUCOES){ 
        turn[idx] = __sync_fetch_and_add(&number, 1); //Protocolo de entrada da seção crítica.
        while (!(turn[idx] == next)); //Protocolo de entrada da seção crítica.
        temperatura += rand() % (50 + 1 - (-10)) + (-10); //Modifica o valor da temperatura entre -10 e 50.
        printf("[%ld] alterou a temperatura para %.d graus Celsius.\n", idx, temperatura); 
        __sync_fetch_and_add(&next, 1); //Protocolo de saída da seção crítica.
        usleep(300);
    }
    return 0;
}
void *function2(void *p){ 
    long idx = (long)p;
    srand(clock());
    while(reducoes != MAX_REDUCOES){
        turn[idx] = __sync_fetch_and_add(&number, 1);
        while (!(turn[idx] == next));
        temperatura += rand() % (20 + 1 - (-20)) + (-20); //Modifica o valor da temperatura entre -20 e 20.
        printf("[%ld] alterou a temperatura para %.d graus Celsius.\n", idx, temperatura);
        __sync_fetch_and_add(&next, 1);
        usleep(400); 
    }
    return 0;
}
void *function3(void *p){
    long idx = (long)p;
    while(reducoes != MAX_REDUCOES){
        turn[idx] = __sync_fetch_and_add(&number, 1);
        while (!(turn[idx] == next));
        if (temperatura > MAX_TEMP){ 
            temperatura = 600;
            reducoes++; 
            printf(" A redução de temperatura #%d acaba de ocorrer!\n", reducoes);
        }
        __sync_fetch_and_add(&next, 1);
    }
    return 0;
}
int main(){
    pthread_t thread1, thread2, thread3;
    for (int i = 0; i < QTD_THREADS; i++){ 
        turn[i] = 0;
    }
    pthread_create(&thread1, NULL, function1, (void *)0);
    pthread_create(&thread2, NULL, function2, (void *)1);
    pthread_create(&thread3, NULL, function3, (void *)2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf(" O motor será desligado!\n");
    return 0;
}