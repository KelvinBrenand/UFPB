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