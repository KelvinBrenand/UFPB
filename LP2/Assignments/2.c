/*
Faça um programa em que três processos executam paralelamente as seguintes ações:
Processo original:
	Cria processos "Descendente 0" e "Descendente 1"
	Imprime números de 1 a 50, com um intervalo de 1 segundo entre cada número.
	Após imprimir todos os números, imprime a frase “Processo original parou de contar”.
	Deverá finalizar o processo "descendente 0" usando a função kill()
	Invocar a função exit()

Processo Descendente 0:
	Executa a função gastarProcessamento() (dos exemplos da disciplina). 

Processo Descendente 1:
	Imprime os números de 100 a 200, com um intervalo de 1 segundo entre cada número.
	Antes de imprimir os números, imprime a frase “Descendente 1 foi criado”.
	Após imprimir todos os números, imprime a frase “Descendente 1 vai morrer”.

Requisitos/Dicas:
	Em cada printf os processos devem imprimir o seu pid.
	Use a instrução puts(“..”); depois da linha do printf().
	sleep(1) bloqueia ("dorme") o processo por 1 segundo.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <signal.h>

void GastarProcessamento(){
	for (int i = 0; i < 999999999; ++i){
		for (int i = 0; i < 99999; ++i){
		}
	}
}
int main(){
    pid_t Descendente0;
	int fork_return = fork();
	if(fork_return > 0){
		if((Descendente0 = fork()) == 0){ //Descendente 0
			GastarProcessamento();
		}
		for(int i = 1; i < 51; ++i){ //Processo Pai
			printf("%d says: %d\n", getpid(), i);
			puts("..");
			sleep(1);
		}
		printf("%d says: Processo original parou de contar\n", getpid());
		puts("..");
		kill(Descendente0, SIGKILL);
		exit(EXIT_SUCCESS);
	}else if(fork_return == 0){ //Descendente 1
		printf("%d says: Descendente 1 foi criado\n", getpid());
		puts("..");
		for(int i = 100; i < 201; ++i){
			printf("%d says: %d\n", getpid(), i);
			puts("..");
			sleep(1);
		}
		printf("%d says: Descendente 1 vai morrer\n", getpid());
		puts("..");
	}
	return 0;
}
