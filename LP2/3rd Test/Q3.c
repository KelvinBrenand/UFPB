#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define SERVER_PORT 8600
#define MAX_CLIENTS 10
#define MAX_SIZE 50 //Tamanho máximo das mensagens
int simultaneousClients = 0;

void strrev(char* name){ //Função responsavel por gerar o contrário de uma dada string name
    char r[strlen(name)];
    int begin;
    int end = strlen(name)-1;
    for (begin = 0; begin < strlen(name); begin++) {
        r[begin] = name[end];
        end--;
    }
    r[begin] = '\0';
    strcpy(name, r);
}
int randNum(){ //Função responsavel por retornar um int entre 0 e 1000
    srand(clock());
    return rand() % (1000 + 1 - 0) + 0;
}

void *handleClient(void *param){ //Função principal do servidor, responsável por lidar com os clientes na forma de threads
    int clifd = (int)(long)param; //Identificação do cliente
    char *msg = "\nWELCOME!\n\n"; 
    char buf[MAX_SIZE+1]; //Buffer das mensagens
    char Aux[7]; //String para auxiliar na opção BCKWRD <STRING>
    write(clifd, msg, strlen(msg));
    while (1){
        bzero(buf, MAX_SIZE);
        read(clifd, buf, MAX_SIZE); 
        if (strlen(buf) > 0){ //Caso uma mensagem seja enviada...
            printf("Client #%d says: %s", clifd, buf);
            if (strstr(buf, "FINISH") != NULL){
                break;
            }
            if (strstr(buf, "CRTIME") != NULL){ //Opção do cliente solicitar a data e hora corrente
                char str[MAX_SIZE];
                time_t t = time(NULL); 
                struct tm tm = *localtime(&t); //Struct de onde serão obtidos todos os dados de tempo, como mes, ano, horas, etc.
                sprintf(str,"Date: %d-%02d-%02d\nHour: %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, 
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec); //Armazena em str os dados de tempo no formato de string
                write(clifd, str, strlen(str)); //Envia para o cliente as informações de tempo no formato DD/MM/AAAA HH:MM:SS
                write(clifd, "\n\n", strlen("\n\n"));
                continue;
            }
            if (strstr(buf, "RANDNUM") != NULL){ //Opção do cliente solicitar um número entre 0 e 1000
                char str[MAX_SIZE]; 
                int return_value = randNum(); 
                sprintf(str, "%d", return_value);
                write(clifd, str, strlen(str));  
                write(clifd, "\n\n", strlen("\n\n"));
                continue;
            }
            strncpy(Aux, buf, 6); //Faz uma cópia dos 6 primeiros caracteres enviados pelo usuario, para o caso dele pedir "BCKWRD"
            Aux[7] = '\0'; //Adiciona o final da string Aux
            if(strstr(Aux, "BCKWRD") != NULL){ 
                for (int i = 0; i < MAX_SIZE; i++){ //Remove a substring do comando "BCKWRD " da mensagem do cliente
                    buf[i] = buf[i+6];
                }
                strrev(buf);
                write(clifd, buf, MAX_SIZE); 
                write(clifd, "\n\n", strlen("\n\n"));
                continue;
            }
            write(clifd, "ERROR", strlen("ERROR")); //Se nenhum dos comandos foi selecionado, o cliente é informado de um erro 
            write(clifd, "\n\n", strlen("\n\n"));
        }
    }
    close(clifd); //Caso o cliente tenha mandado "FINISH", ele sai do loop
    simultaneousClients--;
    pthread_exit(0);
}
int main(){
    int serverfd, sizecliaddr;
    pthread_t clientThread[MAX_CLIENTS];
    struct sockaddr_in serveraddr, cliaddr;
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1){ //Verificação de erro na criação do socket
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
        }else{ //Caso o máximo de clientes tenha sido alcançado...
            printf("Maximum number of clients reached!\n");
            while(simultaneousClients >= MAX_CLIENTS){
                sleep(1);
            }
        }
    }
    return 0;
}
/*
No protocolo TCP (que garante a entrega das informações), o servidor possui um papel mais passivo, onde ele aguarda por pedidos
dos clientes. Os servidores podem se conectar com uma vasta quantidade de clientes e, após atender os seus pedidos, ele os respon-
de com os dados solicitados.
Para a criação de um servidor TCP, os seguintes comandos são necessários:

serverfd = socket(AF_INET, SOCK_STREAM, 0); A criação do socket deve conter o AF_INET, que corresponde a familia de protocolos da
internet, bem como conter o SOCK_STREAM, que determina que se trabalhará com o o protocolo TCP. Caso essa constante fosse alterada
para SOCK_DGRAM, por exemplo, ja não seria mais o protocolo TCP, mas o UDP.

serveraddr.sin_family = AF_INET; Este comando informa para a struct que iremos trabalhar com a familia AF_INET
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); Este comando, através da constante INADDR_ANY, informa que a aplicação irá receber
conexões de outro sockets, portanto, será um servidor.

serveraddr.sin_port = htons(SERVER_PORT); Este comando determina a porta em que o servidor irá aguardar por conexões

bind(serverfd, ((struct sockaddr *)&serveraddr), sizeof(serveraddr)); O comando bind é responsavel por fazer a associação
da estrutura serveraddr com o socket serverfd, que foi previamente criado.
listen(serverfd, 1); Após tudo isso, o comando listen é executado. Esse comando serve para aceitar as conexões no socket File Descriptor.

Já o cliente, é responsavel por fazer os requests ao servidor e esperar por respostas, tudo isso utilizando os recursos da rede.
Para a criação de um cliente TCP, os seguintes comandos são necessários:

clientfd = socket(AF_INET, SOCK_STREAM, 0); Comando que já foi explicado na parte do servidor.
serveraddr.sin_family = AF_INET; Comando que já foi explicado na parte do servidor.
serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Comando que, dessa vez, associa um IP especifico ao cliente.
serveraddr.sin_port = htons(SERVER_PORT); Comando que, neste caso, devermina onde o servidor está aguardando as conexões.
connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)); Por fim, o comando que faz a conexão do cliente com o ser-
vidor para a troca de informações.
*/