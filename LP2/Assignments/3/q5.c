#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
double global_var = 0.0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* parityChecker(void* param){
	srand(time(NULL));
	double value = ((long)param)%2 ? 1.0 : -1.0;
	for (int i = 0; i < 10; ++i){
		pthread_mutex_lock(&mutex);
		global_var += value;
		pthread_mutex_unlock(&mutex);
		printf("THREAD #%ld changed the global variable value to: %.1f\n", (long)param, global_var);
		sleep((rand()%4)+1);
	}
	return 0;
}
int main(){
	pthread_t arr[10];
	long j = 0;
	for (j = 0; j < 10; ++j){
		pthread_create(&arr[j], NULL, parityChecker, (void*)j);
	}
	for (int i = 0; i < 10; ++i){
		pthread_join(arr[i], NULL);
	}
	printf("Global variable final value = %.1f\n", global_var);
	return 0;
}