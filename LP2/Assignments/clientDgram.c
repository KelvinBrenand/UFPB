#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SERVER_PORT 9998
#define SERVER_ADDR "127.0.0.1"
#define BUF_SIZE 60

int main(void){
    int serverfd;
    int client_read = 0;
    int client_addr_size = 0;
    int finished = 0;
    char buffer[BUF_SIZE + 1];
    char recv_buffer[BUF_SIZE + 1];
    struct sockaddr_in serveraddr;
    struct sockaddr_in recvaddr;
    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (serverfd == -1){
        printf("socket creation error!\n");
        exit(0);
    }
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serveraddr.sin_port = htons(SERVER_PORT);
    printf("Sending messages to %s on port %d\n", SERVER_ADDR, SERVER_PORT);
    while (!finished){
        printf("Digite o que deseja enviar ao servidor: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(serverfd, (const char *)buffer, strlen(buffer), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        sleep(1);
        int recv_len = 0;
        bzero(&recvaddr, sizeof(recvaddr));
        int server_read = recvfrom(serverfd, (char *)recv_buffer, BUF_SIZE, 0, (struct sockaddr *)&recvaddr, &recv_len);
        recv_buffer[server_read] = '\0';
        printf("Recebi do servidor: %s", recv_buffer);
    }
    return 0;
}