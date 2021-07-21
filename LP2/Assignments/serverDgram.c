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
#define BUF_SIZE 60

int main(void){
    int serverfd;
    int client_read = 0;
    int client_addr_size = 0;
    int finished = 0;
    char buffer[BUF_SIZE + 1];
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    serverfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverfd == -1){
        printf("socket creation error!\n");
        exit(0);
    }
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    int bind_return = bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (bind_return != 0){
        printf("bind error!\n");
        exit(0);
    }
    printf("Waiting for messages on port %d\n", SERVER_PORT);
    while (!finished){
        client_read = recvfrom(serverfd, buffer, BUF_SIZE, 0, ((struct sockaddr *)&clientaddr), &client_addr_size);
        if (client_read == -1){
            printf("recvfrom error!\n");
        }
        sleep(1);
        buffer[client_read] = '\0';
        printf("Recebi: %s", buffer);
        if (strstr(buffer, "BYE") != NULL){
            finished = 1;
        }
        int client_sent = sendto(serverfd, buffer, sizeof(buffer), 0, ((const struct sockaddr *)&clientaddr), sizeof(clientaddr));
        if (client_read == -1){
            printf("sendto error!\n");
        }
        printf("Enviei: %s", buffer);
    }
    return 0;
}