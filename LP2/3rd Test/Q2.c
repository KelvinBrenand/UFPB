#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#define TAM_BUF 256
#define QTD_PROD 2 
#define QTD_CONS 3
#define QTD_CONSUMO_BUFFER 4
char buf[TAM_BUF];
int front = 0, rear = 0;
sem_t empty, full;
sem_t mutexD, mutexF; 

typedef struct{ //Monitor dos arquivos
    pthread_mutex_t mutex;
} txtMonitor;

void insereCaractere(txtMonitor *m, FILE *file, char c){ //Função do monitor para inserir em um único arquivo
    pthread_mutex_lock(&m->mutex);
    char Aux[5];
    Aux[0] = c;
    
    fputs(Aux, file); //Salva as informações no arquivo
    fputs("\n", file);
    pthread_mutex_unlock(&m->mutex);
}

txtMonitor txtM1;

void *produtor(void *p){ 
    int indice = (long)p;
    srand(clock()+indice);
    int randNum = 0;
    char randChar = 'a';
    int contador = 0;
    while (1){
        if(rear == 0){
            contador++;
        }
        if(contador >= QTD_CONSUMO_BUFFER+1){
            break;
        }
        sem_wait(&empty);
        randNum = rand() % (255 + 1 - 0) + 0;
        randChar = (char)randNum;
        sem_wait(&mutexD);
        buf[rear] = randChar;
        printf("[PROD-%d] produziu o char \"%c\" de valor %d e o armazenou na posicao %d do buffer.\n", 
        indice, randChar, randNum, rear);
        rear = (rear + 1) % TAM_BUF;
        sem_post(&mutexD);
        sem_post(&full);
        usleep(150*1000);
    }
    pthread_exit(0);
}
void *consumidor(void *p){ 
    int indice = (long)p; 
    srand(clock()+indice);
    FILE *FilePtr;
    FilePtr = fopen("file.txt", "w");
    while (1){
        sem_wait(&full);
        sem_wait(&mutexF);
        insereCaractere(&txtM1, FilePtr, buf[front]);
        printf("[CONS-%d] consumiu \"%c\"\n", indice, buf[front]);
        front = (front + 1) % TAM_BUF;
        sem_post(&mutexF);
        sem_post(&empty);
        usleep((rand() % (150 + 1 - 50) + 50)*1000);
    }
    fclose(FilePtr);
    pthread_exit(0); 
}
int main(){
    pthread_t prod[QTD_PROD], cons[QTD_CONS]; 
    sem_init(&empty, 0, TAM_BUF); 
    sem_init(&full, 0, 0);
    sem_init(&mutexD, 0, 1);
    sem_init(&mutexF, 0, 1);
    for (long i = 0; i < QTD_PROD; i++){ 
        pthread_create(&prod[i], NULL, produtor, (void *)i);
    }
    for (long i = 0; i < QTD_CONS; i++){
        pthread_create(&cons[i], NULL, consumidor, (void *)i);
    }
    for (int i = 0; i < QTD_PROD; i++){ 
		pthread_join(prod[i], NULL); 
	}
    sleep(2);
    return 0;
}