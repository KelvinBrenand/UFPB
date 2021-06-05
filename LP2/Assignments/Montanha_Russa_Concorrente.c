/*
Montanha Russa concorrente
Suponha que existam n passageiros e um carro em uma montanha russa em um parque.
Os passageiros, repetidamente, esperam para dar uma volta no carro. O carro tem 
capacidade para C passageiros, com C < n.  O carro só pode partir  quando 
estiver cheio. Após dar uma volta na montanha russa, cada passageiro passeia 
pelo parque de diversões e depois retorna à montanha russa para a próxima volta. 
O programa a ser desenvolvido deverá utilizar o algoritmo do ticket apresentado 
em sala de aula. 

Tanto o carro quanto os passageiros devem ser representados por threads. A 
implementação das threads dos passageiros e dos carros devem executar funções 
que se baseiam nos seguintes pseudocódigos:

thread passageiro[i = 1 to n]  {
    while (!fechouParque) { 
        entraNoCarro(); //Incrementa contador que registra o número de passageiros transportados pelo carro.
        esperaVoltaAcabar(); 
        saiDoCarro(); // decrement o contador
        passeiaPeloParque(); // tempo aleatório
    }
}
thread carro {
    while (existemPassageirosNoParque) {
        esperaEncher();
        daUmaVolta();
        esperaEsvaziar(); 
        volta++; // Indicador para o fechamento do parque.
    }
}

Locks devem ser utilizados para a sincronização do acesso às seções críticas, 
barreiras devem sincronizar as múltiplas threads. A implementação deverá ser 
feita em C/C++ utilizando a biblioteca Pthreads ou as threads STD (C++11). A 
implementação deverá atender às quatro propriedades de uma solução para o 
problema da seção crítica: exclusão mútua, ausência de deadlock, ausência de 
atraso desnecessário e entrada eventual. A saída do seu programa deve ser bem 
planejada, de forma a mostrar o que está acontecendo a cada momento.

$gcc -pthread Montanha_Russa_Concorrente.c -o Montanha_Russa_Concorrente
$./Montanha_Russa_Concorrente
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define QTD_THREADS 5  
#define CAPACITY 4     
#define MAX_VOLTAS 2   
#define TEMPO_VOLTA 2  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t controle_barreira;
int fechouParque = 0, Npassageiros = 0, number = 1, next = 1, voltas = 0, varAux = 1, turn[QTD_THREADS];

void *passageiro(void *p){
    while (1){ //Enquanto o parque estiver aberto...
        long idx = (long)p;
        srand((int)idx);
        int wait_ret = pthread_barrier_wait(&controle_barreira); //Barreira para sincronizar os passageiros.
        if(fechouParque == 1){
            break;
        }
        turn[idx] = __sync_fetch_and_add(&number, 1); //Entrando na seção crítica #1 usando o algoritmo do ticket.
        while (!(turn[idx] == next));
        if (Npassageiros < CAPACITY){ 
            Npassageiros++; //Passageiro entrou no carro.
            printf("[%ld] entrou no carro\n", idx);
            puts("..");
            __sync_fetch_and_add(&next, 1); //Saindo da seção crítica #1.
            while (varAux != voltas);//Os passageiros esperam a volta acabar.
            pthread_mutex_lock(&mutex); //Entrando na seção crítica #2. Dessa vez utilizando a função de lock da biblioteca Pthread.
            Npassageiros--; //Passageiro sai do carro.
            pthread_mutex_unlock(&mutex); //Saindo da seção crítica #2.
            printf("[%ld] saiu do carro\n", idx);
            puts("..");
            while (Npassageiros != 0); //Passageiros esperam o carro completar de esvaziar.
            varAux = voltas+1;
            sleep(rand()%10+1); //Passeia pelo parque um tempo aleatório.
        }else{ //Caso não tenha vagas no carro, o passageiro vai embora.
            __sync_fetch_and_add(&next, 1);
        }
    }
    return 0;
}
void *carro(void *p){
    while (1){ //Sempre existirão passageiros enquanto o parque estiver aberto.
        if (Npassageiros == CAPACITY){
            sleep(TEMPO_VOLTA); //Representa dar uma volta.
            voltas++;
            printf("O carro está dando uma volta.\n");
            puts("..");
        }
        if (voltas == MAX_VOLTAS){
            fechouParque = 1;
            printf("O parque fechou!\n");
            puts("..");
            break;
        } 
    }
    return 0;
}
int main(){
    pthread_t threads[QTD_THREADS], car;
    for (int i = 0; i < QTD_THREADS; i++){
        turn[i] = 0;
    }
    int init_bar_ret = pthread_barrier_init(&controle_barreira, NULL, QTD_THREADS);
    pthread_create(&car, NULL, carro, NULL); 
	for (long i = 0; i < QTD_THREADS; ++i){ 
		pthread_create(&threads[i], NULL, passageiro, (void*)i);
	}
    pthread_join(car, NULL);
	for (int i = 0; i < QTD_THREADS; ++i){
        pthread_join(threads[i], NULL);
        printf("%d foi embora do parque.\n", i);
        puts("..");
	}
	printf("O programa finalizou.\n");
    return 0;
}