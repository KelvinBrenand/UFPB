#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bibliotecas usadas para criar a conexão usando sockets 
	e enviar dados pela rede*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Constante que define o tamanho máximo da mensagem enviada ou recebida*/
#define TAM_MAX 100
/* Constante que define a porta utilizada para conexão */
#define PORTA 12345

/* Variáveis globais usadas na conexão, envio e recebimento de dados*/
static int sockfd, newFD;

/**
	Função que cria uma conexão com o cliente.
	A função é bloqueante e fica esperando um pedido de conexão do cliente. 
	Quando esse pedido é feito pelo cliente, se estiver tudo ok, a conexão é aceita. 
	Retorno: 1 se a conexão foi realizada com sucesso e -1 caso contrário.
 */
int conecta(){
	struct sockaddr_in myAddr;
	struct sockaddr_in cliente;
	
	// Cria o socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd ==-1){
		printf("Socket não pode ser criado\n");
		return -1;
	}

	//Prepara a estrutura sockaddr_in 
	myAddr.sin_family = AF_INET; 			// Protocolo IP
	myAddr.sin_addr.s_addr = INADDR_ANY; 	// Permite receber conexoes de qualquer cliente
	myAddr.sin_port = htons( PORTA ); 		// Porta utilizada na conexão
     
	//Bind
	if(bind(sockfd,(struct sockaddr *)&myAddr , sizeof(myAddr)) < 0){
    	printf("Bind falhou\n");
	}
	printf("Bind feito com sucesso\n");
   
    //Listen
    listen(sockfd, 3);
     
    // Esperando e aceitando conexões
    printf("Esperando por conexões...\n");
    int c = sizeof(struct sockaddr_in);
    newFD = accept(sockfd, (struct sockaddr *)&cliente, 
    	(socklen_t*)&c);
    
    if (newFD<0){
        printf("Conexão não aceita\n");
    }
    
    printf("Conexão aceita de %s \n", inet_ntoa(cliente.sin_addr));
    return 1;
}

/**
	Envia uma mensagem (pacote) pela rede para o cliente conectado. 
	Parametros: uma string com a mensagem a ser enviada e o tamanho (numero de bytes) dessa string. 
	IMPORTANTE: A mensagem só será recebida se o cliente tiver chamada a função para receber a mensagem.
	Retorno: o número de bytes enviados na mensagem
 */
int enviaMensagem(char *msg, int tamMsg){
	return send(newFD, msg, tamMsg, 0);
}

/**
	Recebe uma mensagem (pacote) do cliente conectado. 
	A função é bloqueante, e fica esperando o cliente enviar o pacote.
	Parametros: uma string com a mensagem a ser enviada e o tamanho maximo de caracteres que podem ser preenchidos na mensagem. 
	Retorno: número de bytes recebidos na mensagem
 */
int recebeMensagem(char *msg, int tamMsg){
	return recv(newFD, msg, tamMsg, 0);
}


int main(){
	int ret;
	int tamMsg;
	char msgEnv[TAM_MAX];
	char msgRec[TAM_MAX];
	int compara;
	/* Espera o cliente pedir para se conectar e se conecta */
	ret	= conecta();
	if (ret != -1){
		
		/*No server, o que fiz foi basicamente colocar as funcoes de envio e recepção
		das mensagens num loop infinito, onde a opção de saida é controlada pelo usuário
		ou o EOF (Ctrl + z) no terminal*/
		while(1)
		{
			/* Lê uma mensagem do usuário e envia pela rede*/
			printf("Digite a mensagem para enviar: ");
			fgets(msgEnv, TAM_MAX, stdin);
			tamMsg = strlen(msgEnv); 
		
			ret = enviaMensagem(msgEnv, tamMsg);
			printf("Enviou uma mensagem com %d bytes\n", ret);

			/* Recebe uma mensagem pela rede */
			ret = recebeMensagem(msgRec, TAM_MAX);
			compara = strcmp(msgRec, "END\n");//No caso do usuario encerrar a conversa.
			if(compara == 0)
			{
				printf("O usuario encerrou a conversa.\n");
				break;
			}
			else
			{
				printf("Msg recebida: %s \n", msgRec);
			}
		}
	}
}
