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
#define STR_LENGTH 12
#define MAX_CHARS 6
#define STR_AMOUNT 10
#define SERVER_PORT 6000
char strAux1[STR_LENGTH];

const char* strRand() {
    srand(clock());
    int randNum = 0;
    char strAux2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < MAX_CHARS; i++){
        randNum = rand() % (int)(25 + 1 - 0) + 0;
        strAux1[i] = strAux2[randNum];
    }
    return strAux1;
}
int main(){
    int clientfd;
    struct sockaddr_in serveraddr;
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1){
        printf("Client socket creation error\n");
        exit(0);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(SERVER_PORT);
    int con_res = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (con_res != 0){
        printf("Connection error!\n");
        exit(0);
    }
    printf("Client connected to port %d\n", SERVER_PORT);
    char buf[20], myMsg[STR_LENGTH];
    int end = 0;
    while (1){
        bzero(buf, 20);
        bzero(myMsg, STR_LENGTH);
        read(clientfd, buf, 20);
        if (strlen(buf) > 0){
            printf("Server says: %s\n", buf);
        }
        if (end == 10){
            strcpy(myMsg, "SHUTDOWN");
            printf("Finishing connection.\n");
            write(clientfd, myMsg, strlen(myMsg));
            break;
        }
        strcpy(myMsg, strRand());
        printf("Sending %s to server.\n", myMsg);
        strcat(myMsg, "\n ");
        write(clientfd, myMsg, strlen(myMsg));
        sleep(1);
        end++;
    }
}
/*
Faça um programa cliente para o programa do quarto exercício prático (E004). DONE
Se conecte a um servidor DONE
Gere 10 strings aleatórias de 6 caracteres DONE
enviado-as com chamadas intercaladas à função sleep com 1 segundo de argumento. DONE
O cliente deverá também exibir todas as informações (strings) que recebe do servidor. DONE
*/