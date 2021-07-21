#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char abcPrint[] = "AAAA"; //String que será inserida nos arquivos, com 4 letras, como especificado.
char abcString[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void* abcPermut(void* param){
    char file[10];
    FILE *FilePtr;
    snprintf(file, 10, "%c.txt", abcString[(long)param]); 
    FilePtr = fopen(file, "w");
    pthread_mutex_lock(&mutex);
    abcPrint[0] = abcString[(long)param]; //A partir do parametro da função, determina a letra inicial da thread da vez.
    for (int i = 0; i < strlen(abcString); i++){
        abcPrint[1] = abcString[i];
        for (int i = 0; i < strlen(abcString); i++){
            abcPrint[2] = abcString[i];
            for (int i = 0; i < strlen(abcString); i++){
                abcPrint[3] = abcString[i];
                fputs(abcPrint, FilePtr);
                fputs("\n", FilePtr);
            } 
        }
    }
    pthread_mutex_unlock(&mutex); //Destrava o mutex, para que outra thread possa usar a função.
    fclose(FilePtr);
	return 0;
}
int main(){
    const int nthreads = 26; //Numero de threads que serão criadas. 26 = uma por letra do alfabeto.
    pthread_t threads[nthreads];
    for (long i = 0; i < nthreads; i++){
		pthread_create(&threads[i], NULL, abcPermut, (void*)i);
	}
    for (int i = 0; i < nthreads; i++){
		pthread_join(threads[i], NULL);
	}
    return 0;
}