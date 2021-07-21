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
char abcString[] = "ABC"; //String para nomear os arquivos txt
sem_t empty, full;
sem_t mutexD, mutexF;

void *produtor(void *p){
    int indice = (long)p; //Identificação das threads
    srand(clock()+indice);
    int randNum = 0;
    char randChar = 'a';
    int contador = 0; //Quando o contador alcancar o numero de vezes que o buffer deve ser consumido, as threads são finalizadas
    while (1){
        if(rear == 0){
            contador++;
        }
        if(contador >= QTD_CONSUMO_BUFFER+1){ //+1 pois a contagem começa em 0. Quando ele alcança QTD_CONSUMO_BUFFER, ele ainda precisa terminar a "volta"
            break;
        }
        sem_wait(&empty);
        randNum = rand() % (255 + 1 - 0) + 0;
        randChar = (char)randNum;
        sem_wait(&mutexD);
        buf[rear] = randChar;
        printf("[PROD-%d] produziu o char \"%c\" de valor %d e o armazenou na posicao %d do buffer.\n", 
        indice, randChar, randNum, rear);
        rear = (rear + 1) % TAM_BUF; //Incrementa rear
        sem_post(&mutexD);
        sem_post(&full);
        usleep(150*1000); //150000 microseconds *1000 = 150ms
    }
    pthread_exit(0);
}
void *consumidor(void *p){ 
    int indice = (long)p;
    char result[5]; 
    srand(clock()+indice);
    char file[10];
    FILE *FilePtr;
    snprintf(file, 10, "%c.txt", abcString[indice]);
    FilePtr = fopen(file, "w");
    while (1){
        sem_wait(&full); 
        sem_wait(&mutexF);
        result[0] = buf[front]; //Consome a informacao do buffer
        fputs(result, FilePtr); //Salva as informações nos arquivos
        fputs("\n", FilePtr); 
        printf("[CONS-%d] consumiu \"%c\"\n", indice, result[0]);
        front = (front + 1) % TAM_BUF; //Incrementa front
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
    for (int i = 0; i < QTD_PROD; i++){ //Aguarda as threads produtoras retornarem
		pthread_join(prod[i], NULL); 
	}
    sleep(2); //Aguarda dois segundos e finaliza o programa.
    /*
    Neste caso, como temos mais consumidores que produtores e eles dormem um tempo menor ou igual ao tempo dos produtores,
    então os consumidores sempre finalizarão imediatamente após as threads produtoras. De modo que um sleep(2) ou de até 
    menos tempo é uma solução interessante e funcional para 100% dos casos dessa atividade.
    */
    return 0;
}

/*
De maneira similar aos semáforos da vida real, os semáforos na programação concorrete agem de forma a prover um mecanismo
de sinalização e, como foi evidenciado ao longo desse programa, são usados para resolver problemas decorrentes de se tra-
balhar com regiões críticas no código, como garantir a exclusão mutua. Os semáforos podem ainda ser usados para problemas
de sincornização, como foi o caso com esse progrma, onde precisavamos sincronizar os produtores e consumidores.

Eseencialmente, semáforos são variáveis compartilhadas que são manipuladas através de duas operações atómicas P e V. Como
já mencionado, sua função é controlar o acesso a recursos compartilhados num ambiente multithread. Utilizando a biblioteca
semaphore.h, para utilizar os semáforos precisa-se das sequintes instruções:

sem_t empty, full; Sua declaração.

sem_init(&empty, 0, TAM_BUF); Sua inicialização.
sem_init(&full, 0, 0);

sem_wait(&empty); //Protocolo de entrada na região crítica
sem_wait(&full);

sem_post(&full); //Protocolo de saída da região crítica
sem_post(&empty);
*/