#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h> 
#define N 30

void* tCreated(void* param){
	printf("A thread has been created.\n");
	sleep(2);
	return 0;
}
int pCreated(){
	printf("A process has been created.\n");
	sleep(2);
	return 0;
}
int main(){
	pthread_t threads[N];
	pid_t processes[N];
	int child_status;
	struct timeval tBeginning, tEnd, pBeginning, pEnd;
	gettimeofday(&tBeginning, NULL);
	for (int i = 0; i < N; ++i){
		pthread_create(&threads[i], NULL, tCreated, NULL);
	}
	gettimeofday(&tEnd, NULL);
	for (int i = 0; i < N; ++i){
		pthread_join(threads[i], NULL);
	}
	gettimeofday(&pBeginning, NULL);
	for (int i = 0; i < N; i++){
		if ((processes[i] = fork()) == 0){
		    pCreated();
		    exit(0);
		}
	}
	gettimeofday(&pEnd, NULL);
    for (int i = 0; i < N; i++){
		pid_t wpid = waitpid(processes[i], &child_status, 0);
	}
	printf("All threads were created in %ld seconds and %ld microseconds.\n", 
		(tEnd.tv_sec - tBeginning.tv_sec), (tEnd.tv_usec - tBeginning.tv_usec));
	printf("All processes were created in %ld seconds and %ld microseconds.\n", 
		(pEnd.tv_sec - pBeginning.tv_sec), (pEnd.tv_usec - pBeginning.tv_usec));
	return 0;
}