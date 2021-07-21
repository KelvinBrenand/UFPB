/*
Faça um programa em C/C++ que crie um servidor TCP que aguarde conexões na porta 9000. Este servidor deverá ser capaz de receber 
e tratar conexões de até 10 clientes simultâneos. Cada nova conexão deverá receber uma string de início de conexão (ex. “START”). 
Faça o programa gerenciar um buffer compartilhado composto por até 1024 caracteres. Este buffer deverá ser modificado concatenando 
cada nova string recebida de cada um dos clientes. Sempre que receber uma nova string de um dos clientes, o servidor modifica o 
buffer e o envia para todos os cliente.
Exemplo de execução:

3 clientes se conectam;
servidor envia “START” para os 3 clientes;
cliente 1 envia a string “ABC” para o servidor;
servidor envia buffer para o cliente 1: “ABC”;
cliente 2 envia a string “XYZ” para o servidor;
servidor envia buffer para cliente 2: “ABC\nXYZ”
cliente 3 envia a string “IJK” para o servidor;
servidor envia buffer para cliente 3: “ABC\nXYZ\nIJK”;

Se 4 dos clientes enviarem a string “SHUTDOWN” o servidor deverá ser finalizado. Utilize uma barreira para implementar esta 
funcionalidade.

O programa deverá utilizar a biblioteca POSIX Threads (PThreads) ou as threads STD (C++11) e a biblioteca sockets.h (ou winsock.h). 
A saída do seu programa deve ser bem planejada, de forma a mostrar o que está acontecendo em cada momento relevante. Para testes do 
servidor, usar netcat (nc) ou telnet para o lado do cliente.
*/
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define SERVER_PORT 9000 
#define MAX_CLIENTS 10 
#define MAX_SIZE 10 //Tamanho máximo das mensagens
pthread_barrier_t controle_barreira;
int simultaneousClients = 0; 
char shared_buf[1024];

void *handleClient(void *param){
    int clifd = (int)(long)param;
    char *msg = "\nHello, client!\n";
    char buf[MAX_SIZE+1];
    write(clifd, msg, strlen(msg));
    while (1){
        bzero(buf, MAX_SIZE); 
        read(clifd, buf, MAX_SIZE);
        if (strlen(buf) > 0){
            if (strstr(buf, "GOODBYE") != NULL){
                break;
            }
            if (strstr(buf, "SHUTDOWN") != NULL){
                int wait_ret = pthread_barrier_wait(&controle_barreira); 
                if ((wait_ret != 0) && (wait_ret != PTHREAD_BARRIER_SERIAL_THREAD)){
                    printf("BARRIER ERROR!\n");
                }
                exit(0);
            }
            printf("Client #%d says: %s", clifd, buf);
            strcat(shared_buf, buf); //Concatena a última mensagem com todas as anteriores
            write(clifd, shared_buf, strlen(shared_buf));
        }
    }
    close(clifd); 
    simultaneousClients--; 
    pthread_exit(0);
}
int main(){
    int serverfd, sizecliaddr;
    int init_bar_ret = pthread_barrier_init(&controle_barreira, NULL, 4);
    pthread_t clientThread[MAX_CLIENTS];
    struct sockaddr_in serveraddr, cliaddr; 
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1){ 
        printf("Server socket creation error\n");
        exit(0);
    }
    bzero(&serveraddr, sizeof(serveraddr)); 
    serveraddr.sin_family = AF_INET; //Familia de protocolos da internet
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //Informa que o programa será um servidor
    serveraddr.sin_port = htons(SERVER_PORT); //Porta em que o servidor ira aguardar conexões
    if (bind(serverfd, ((struct sockaddr *)&serveraddr), sizeof(serveraddr)) != 0){ //Executa a função bind e verifica erros
        printf("Server socket bind error\n"); 
        exit(0);
    }
    if (listen(serverfd, 1) != 0){ //Executa a função listen e verifica erros
        printf("Server socket listen error\n");
        exit(0);
    }
    printf("Server socket listening on port: %d\n", SERVER_PORT);
    int t_idx = 0; //Identificação dos clientes
    while (1){
        if (simultaneousClients < MAX_CLIENTS){
            long clientfd = accept(serverfd, ((struct sockaddr *)&cliaddr), &sizecliaddr); //Aceitar um cliente
            printf("Connection received!\n");
            pthread_create(&clientThread[t_idx], NULL, handleClient, (void *)clientfd);
            t_idx++;
            simultaneousClients++;
        }else{ 
            printf("Maximum number of clients reached!\n"); 
            while(simultaneousClients >= MAX_CLIENTS){
                sleep(1); //Aguarde
            }
        }
    }
    return 0;
}