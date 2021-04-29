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
static int sockfd;
	
/**
	Função que cria uma conexão com o servidor. 
	Ele faz o pedido de conexão ao servidor e espera a resposta. 
	IMPORTANTE: O servidor precisa estar rodando esperando o pedido de conexão para que a mesma seja realizada 
	
	Parametros: uma string contendo o endereço IP do servidor. 
	Retorno: 1 se a conexão foi realizada com sucesso e -1 caso contrário.
 */
int conecta(char *ipServidor){
	struct sockaddr_in server;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd ==-1){
		printf("Socket não pode ser criado\n");
	}

	server.sin_addr.s_addr = inet_addr(ipServidor);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTA);
 
    //Connect to remote server
    if (connect(sockfd, (struct sockaddr *)&server,sizeof(server)) < 0){
        printf("Erro de conexão\n");
        return -1;
    }
     
    printf("Conectado\n");
    return 1;
}

int enviaMensagem(char *msg, int tamMsg){
	// Envia mensagem
	return send(sockfd, msg, tamMsg, 0);
}

int recebeMensagem(char *msg, int tamMsg){
	// Envia mensagem
	return recv(sockfd, msg, tamMsg, 0);
}


int main()
{
	int tamMsg;
	char msgEnv[TAM_MAX];
	char msgRec[TAM_MAX];

	int ret, x = 0, y, idade, count = 0, s, compara = 1, w;
	FILE *fptr, *fptr2;
	char nome[30], ip[20], sexo[15], amigConver[30];


  	/*Fiz while x!= EOF para que apenas usuario, através do menu, tenha
  	controle de quando o programa é encerrado. */
	while(x != EOF)
	{
		

		fptr = fopen("friendlist.txt", "a+"); //Abre o arquivo (ou cria,se não existir) para read and write.
		if(fopen == NULL) //Verifica se o arquivo foi lido com sucesso.
  		{
  			printf("Erro na abertura do arquivo!\n");
  			return 1;
  		}

		printf("1.Ver lista de amigos\n2.Adicionar amigo\n3.Remover amigo\n"
		"4.Coversar\n5.Sair\n\n"); //Menu de opções para o usuario selecionar.
		scanf("%d", &x);

		if(x == 1) //Opção de mostrar a lista de amigos.
		{
			/*Nesta opção, o programa exibe o nome dos amigos previamente cadastrados e armazenados num txt
			chamado friendlist.txt*/


			/*Utilizei o comando abaixo para limpar a tela, pois, após algumas entradas, a tela 
			ficava extremamente poluída. Li que, aparentemente, isso reduz a portabilidade do código.
			No entanto, optei por utilizar, afinal, o código, com suas funções de envio e 
			recepção de mensagens, foi pensado para rodar em linux.*/
			system("clear");
			printf("Lista de amigos:\n");
			while(fgets(nome, 30, fptr) != NULL) //Lê uma linha do arquivo.
			{
				if(count%4 == 0) //Garante que apenas os nomes dos amigos serão exibidos.
				{
					printf("%s", nome);
				}
				count++;
			}
			fclose(fptr); //Fecha o arquivo após mostrar a lista de amigos.

			/*Abaixo a opção para voltar ao menu ou encerrar o programa.Essa escolha
			se repetirá ao longo das outras opções do menu.*/
			printf("\n1.Retornar ao menu\n2.Encerrar\n\n");
			scanf("%d", &y);
			if(y == 1)
			{
				system("clear");
				count = 0;
				continue;
			}
			if(y == 2)
			{
				break;
			}
		}
		if(x == 2) //Opção de adcionar amigo.
		{
			/*Nesta opção, o programa adciona um novo amigo ao arquivo friendlist.txt, contendo
			nome, ip, idade e sexo. Optei por não usar estruturas pois achei que da forma que fiz, ficou
			mais simples e mais legível*/

			system("clear");
			printf("Digite o nome do seu amigo:\n");
			scanf("%s", nome);
			fprintf(fptr, "%s\n", nome);

			printf("Digite o IP do seu amigo:\n");
			scanf("%s", ip);
			fprintf(fptr, "%s\n", ip);

			printf("Digite a idade do seu amigo:\n");
			scanf("%d", &idade);
			fprintf(fptr, "%d\n", idade);

			printf("Digite o sexo do seu amigo:\n");
			scanf("%s", sexo);
			fprintf(fptr, "%s\n", sexo);

			fclose(fptr); //Fecha o arquivo após adcionar o amigo.
			printf("Amigo adicionado com sucesso\n");


			printf("\n1.Retornar ao menu\n2.Encerrar\n\n");
			scanf("%d", &y);
			if(y == 1)
			{
				system("clear");
				continue;
			}
			if(y == 2)
			{
				break;
			}
		}
		if (x == 3) //Opção de remover amigo.
		{
			/*Na opção de remover amigo, o programa irá criar um novo arquivo .txt e copiar
			todos os dados de friendlist.txt, exceto os dados referentes ao amigo que o usuário optar
			por remover.*/
			system("clear");
			/*Optei por utilizar o método de fechar e abrir o arquivo friendlist.txt para resetar o cursor*/
			fclose(fptr);
			fptr = fopen("friendlist.txt", "a+");
			if(fopen == NULL)
  			{
  				printf("Erro na abertura do arquivo!\n");
  				return 1;
  			}

			fptr2 = fopen("temporario.txt", "w"); //Cria um txt temporario para write.
			if(fopen == NULL) //Verifica se o arquivo foi lido com sucesso.
  			{
  				printf("Erro na abertura do arquivo!\n");
  				return 1;
  			}

			printf("Lista de amigos:\n");

			/*Exibe a lista de amigos para que o usuário selecione o amigo a ser removido*/
			while(fgets(nome, 30, fptr) != NULL) //Lê uma linha do arquivo.
			{
				if(count%4 == 0) //Garante que apenas os nomes dos amigos serão exibidos.
				{
					printf("%s", nome);
				}
				count++;
			}
			getchar();

			/*Optei por utilizar o método de fechar e abrir o arquivo friendlist.txt para resetar o cursor*/
			fclose(fptr);
			fptr = fopen("friendlist.txt", "a+");
			if(fopen == NULL)
  			{
  				printf("Erro na abertura do arquivo!\n");
  				return 1;
  			}

			printf("\nDigite o nome do amigo que voce quer remover:\n");
			printf("Escreva exatamente como aparece!\n");
			fgets(amigConver, 30, stdin);

			/*Aqui o programa compara o nome do amigo a ser lido com a linha lida no arquivo
			friendlist.txt. Se for diferente, ele copia a string para o arquivo temporário. Se for igual,
			entra no if e pula as strings referentes ao nome, ip, idade e sexo do amigo a ser removido*/
			while(fgets(nome, 30, fptr) != NULL)
			{
				compara = strcmp(nome, amigConver);
				if(compara == 0)
				{
					fgets(nome, 30, fptr);
					fgets(nome, 30, fptr);
					fgets(nome, 30, fptr);
				}
				else
				{
					fprintf(fptr2, "%s", nome);
				}
			}

			printf("Amigo removido com sucesso!\n");
			fclose(fptr);//Fecha o arquivo friendlist.txt
			fclose(fptr2);//Fecha o arquivo temporario.txt
			remove("friendlist.txt");//Remove o arquivo friendlist.txt
			/*Substitui o arquivo antigo friendlist.txt pelo arquivo temporario.txt que será
			renomeado para friendlist.txt, já tendo sido removido o amigo selecionado.*/
			rename("temporario.txt", "friendlist.txt");


			printf("\n1.Retornar ao menu\n2.Encerrar\n\n");
			scanf("%d", &y);
			if(y == 1)
			{
				system("clear");
				continue;
			}
			if(y == 2)
			{
				break;
			}
		}
		if (x == 4) //Opção de conversar.
		{
			getchar();
			system("clear");
			printf("Lista de amigos:\n");
			while(fgets(nome, 30, fptr) != NULL)
			{
				if(count%4 == 0)
				{
					printf("%s", nome);
				}
				count++;
			}

			/*Novamente fechei e abri o friendlist.txt para resetar o cursor*/ 
			fclose(fptr);
			fptr = fopen("friendlist.txt", "a+"); 
			if(fopen == NULL)
  			{
  				printf("Erro na abertura do arquivo!\n");
  				return 1;
  			}

			printf("\nDigite o nome do amigo que voce quer conversar:\n");
			printf("Escreva exatamente como aparece!\n");
			fgets(amigConver, 30, stdin);

			/*Estrutura que compara o nome do amigo para comversar com as strings do arquivo
			friendlist.txt. Quando encontra o amigo, executa fgets novamente para pegar o ip do amigo*/
			while(fgets(nome, 30, fptr) != NULL)
			{
				compara = strcmp(nome, amigConver);
				if(compara == 0)
				{
					fgets(nome, 30, fptr);
					break;
				}
			}
			system("clear");

			/* Pede para se conectar no servidor */
			ret	= conecta(nome); //Conecta com o amigo.
			if (ret != -1)
			{
				printf("Para sair da conversa digite END.\n");
				while(1)
				{
						/* Recebe uma mensagem do servidor pela rede */
					ret = recebeMensagem(msgRec, TAM_MAX);
					printf("Msg recebida: %s \n", msgRec);
	
					/* Lê uma mensagem do usuário e envia pela rede para o servidor*/
					printf("Digite a mensagem para enviar: ");
					fgets(msgEnv, TAM_MAX, stdin);
					tamMsg = strlen(msgEnv);
					compara = strcmp(msgEnv, "END\n"); //Opção de sair do chat, como pedido nas especificações.
					if (compara == 0)
					 {
					 	ret = enviaMensagem(msgEnv, tamMsg);
						printf("Enviou uma mensagem com %d bytes\n", ret);
					 	break;
					 }
					 else
					 {
					 	ret = enviaMensagem(msgEnv, tamMsg);
						printf("Enviou uma mensagem com %d bytes\n", ret);
					 }
				}
				break;
			}
		}
		if (x == 5) //Encerrar o programa. 
		{
			fclose(fptr); //Fecha o arquivo e encerra o programa.
			break;
		}
		if ((x < 1) || (x > 5)) //Contra usuário malandro.
		{
			fclose(fptr);
			printf("Opcao invalida. Escolha novamente:\n\n");
			continue;
		}
	}
	return 0;
 }