#include <stdio.h> //Biblioteca para trabalhar com leitura e escrita de dados.
#include <unistd.h> //Biblioteca para trabalhar com certas constantes.
#include <string.h> //Biblioteca para trabalhar com strings.
#include <pthread.h> //Biblioteca para trabalhar com threads.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //Mutex para limitar o acesso à região crítica por parte das threads.
char abcPrint[] = "AAAA"; //String que será inserida nos arquivos, com 4 letras, como especificado.
char abcString[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //String do alfabeto.

void* abcPermut(void* param){ //Função responsavel por fazer a escrita das strings nos arquivos.
    char file[10]; //String que irá armazenar o nome do arquivo a ser criado (26 arquivos, um por letra).
    FILE *FilePtr;
    snprintf(file, 10, "%c.txt", abcString[(long)param]); //Instrução que seleciona o nome do arquivo da vez a ser criado, baseado no parametro passado para a função abcPermut
    FilePtr = fopen(file, "w"); //Abre o arquivo a ser trabalhado.
    pthread_mutex_lock(&mutex); //Instrução que fecha o mutex para que só uma thread use a região crítica por vez.
    abcPrint[0] = abcString[(long)param]; //A partir do parametro da função, determina a letra inicial da thread da vez.
    for (int i = 0; i < strlen(abcString); i++){ //Sucessivos for's que farão a permutação das letras do alfabeto (abcString) na string a ser escrita (abcPrint).
        abcPrint[1] = abcString[i];
        for (int i = 0; i < strlen(abcString); i++){
            abcPrint[2] = abcString[i];
            for (int i = 0; i < strlen(abcString); i++){
                abcPrint[3] = abcString[i];
                fputs(abcPrint, FilePtr); //fputs é a função de inserir dados nos arquivos.
                fputs("\n", FilePtr);
            } 
        }
    }
    pthread_mutex_unlock(&mutex); //Destravo o mutex, para que outra thread possa usar a função.
    fclose(FilePtr); //Fecho o arquivo
	return 0; //Fim da função.
}
int main(){
    const int nthreads = 26; //Numero de threads que serão criadas. 26 = uma por letra do alfabeto.
    pthread_t threads[nthreads]; //Array de threads.
    for (long i = 0; i < nthreads; i++){
		pthread_create(&threads[i], NULL, abcPermut, (void*)i); //Cria as threads com a função que estas devem executar.
	}
    for (int i = 0; i < nthreads; i++){
		pthread_join(threads[i], NULL); //Garante que a thread main não será finalizada antes que todas as threads filhas tenham sido finalizadas.
	}
    return 0; //Fim do programa
}