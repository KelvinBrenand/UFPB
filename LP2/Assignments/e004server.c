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
#define SERVER_PORT 6000
#define MAX_CLIENTS 6
#define MAX_SIZE 12
int simultaneousClients = 0;

int isPalindrome(char str[]){
    int l = 0;
    int h = strlen(str) - 3; // -3 por conta do garbage que vem com o telnet.
    while (h > l){
        if (str[l++] != str[h--]){
            return 0;
        }
    }
    return 1;
}
void *handleClient(void *param){
    int clifd = (int)(long)param;
    char *msg = "\nHello, client!\n";
    char buf[MAX_SIZE+1];
    write(clifd, msg, strlen(msg));
    while (1){
        bzero(buf, MAX_SIZE);
        read(clifd, buf, MAX_SIZE);
        if (strlen(buf) > 0){
            if (strstr(buf, "BYEBYE") != NULL){
                break;
            }
            if (strstr(buf, "SHUTDOWN") != NULL){
                printf("Finishing connection.\n");
                exit(0);
            }
            printf("Client #%d says: %s", clifd, buf);
            int palindrome = isPalindrome(buf);
            if (palindrome == 1){
                write(clifd, "PALINDROMO=TRUE\n", strlen("PALINDROMO=TRUE\n"));
            }else{
                write(clifd, "PALINDROMO=FALSE\n", strlen("PALINDROMO=FALSE\n"));
            }
        }
    }
    close(clifd);
    simultaneousClients--;
    pthread_exit(0);
}
int main(){
    int serverfd, sizecliaddr;
    pthread_t clientThread[MAX_CLIENTS];
    struct sockaddr_in serveraddr, cliaddr;
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1){
        printf("Server socket creation error\n");
        exit(0);
    }
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (bind(serverfd, ((struct sockaddr *)&serveraddr), sizeof(serveraddr)) != 0){
        printf("Server socket bind error\n");
        exit(0);
    }
    if (listen(serverfd, 1) != 0){
        printf("Server socket listen error\n");
        exit(0);
    }
    printf("Server socket listening on port: %d\n", SERVER_PORT);
    int t_idx = 0;
    while (1){
        if (simultaneousClients < MAX_CLIENTS){
            long clientfd = accept(serverfd, ((struct sockaddr *)&cliaddr), &sizecliaddr);
            printf("Connection received!\n");
            printf("IP address is: %s\n", inet_ntoa(cliaddr.sin_addr));
            pthread_create(&clientThread[t_idx], NULL, handleClient, (void *)clientfd);
            t_idx++;
            simultaneousClients++;
        }else{
            printf("Maximum number of clients reached!\n");
            while(simultaneousClients >= MAX_CLIENTS){
                sleep(1);
            }
        }
    }
    return 0;
}

/*
Fa??a um programa em C/C++ que atue como um servidor de verifica????o de pal??ndromos.
O servidor dever?? aceitar e tratar at?? 6 conex??es simult??neas de clientes;
ao receber uma nova conex??o, o servidor dever?? dedicar uma thread a ela, para sua correta manipula????o. DONE
O servidor enviar?? uma string de boas vindas para cada nova conex??o (???BEMVINDO???),
e dever?? exibir o endere??o do novo cliente conectado no terminal local.
Os clientes poder??o enviar uma quantidade arbitr??ria de strings com at?? 10 caracteres para o servidor, DONE
???PALINDROMO=TRUE??? caso a string contenha um pal??ndromo else ???PALINDROMO=FALSE???.

Caso o cliente insira a string ???BYEBYE??? sua conex??o dever?? ser finalizada.
O servidor dever?? tratar conex??es indefinidamente DONE
cliente insira a string ???SHUTDOWN???, a?? ent??o o servidor dever?? ser finalizado.
*/