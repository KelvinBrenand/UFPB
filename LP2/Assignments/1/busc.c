#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <string.h>
#define N 5

int buscador(int i, char word[]){
    char file[10], txtWord[11];
    int count = 0;
    FILE *FilePtr;
    snprintf(file, 10, "%d.txt", i);
    FilePtr = fopen(file, "r");
    while(fgets(txtWord, 11, FilePtr) != NULL){
        if(strcmp(txtWord,word) == 0){
            count++;
        }
    }
  fclose(FilePtr);
  return count;
}
int main(){
    pid_t pid[N];
    char word[11];
    int child_status, total = 0;
    printf("Enter the word: ");
    fgets(word, 11, stdin);
    for (int i = 0; i < N; i++){
		if ((pid[i] = fork()) == 0){
		    exit(buscador(i,word));
		}
	}
    for (int i = 0; i < N; i++){
		pid_t wpid = waitpid(pid[i], &child_status, 0);
		printf("The child %d found the word '%s' %d time(s).\n",wpid, word, WEXITSTATUS(child_status));
		total += WEXITSTATUS(child_status);
	}
	printf("The word '%s' was found %d time(s)!\n", word, total);
    return 0;
}