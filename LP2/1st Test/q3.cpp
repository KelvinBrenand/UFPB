#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

void corrida(int lebre, double maxdist, char c){
    double somaDosSaltos = 0.0, salto = 0.0;
    srand(getpid());
    while (1){
        salto = 1.0 + rand()%(int)maxdist/10;
        somaDosSaltos = somaDosSaltos+salto;
        printf("A lebre #%d acabou de saltar %.1f centímetros e já percorreu %.1f metros.\n", lebre, salto, somaDosSaltos);
        sleep(1);
        if (somaDosSaltos >= maxdist){
            if (c == 't' || c == 'T'){
                printf("A lebre %d venceu!\n", lebre);
                exit(0);
            }
            break;
        }
    }
}
int main(){
    char pOrT;
    int child_status, insts, smallerTime = 100000000, smaller;
    double dist;
    printf("Usar (p)rocessos ou (t)hreads?\n");
    scanf("%c", &pOrT);
    printf("Quantas instancias devem ser criadas?\n");
    scanf("%d", &insts);
    printf("Quantos metros tera a pista?\n");
    scanf("%lf", &dist);
    if (pOrT == 'p' || pOrT == 'P'){
        pid_t processes[insts];
        for (int i = 0; i < insts; i++){
            if ((processes[i] = fork()) == 0){
                steady_clock::time_point start = steady_clock::now();
                corrida(i, dist, pOrT);
                steady_clock::time_point end = steady_clock::now();
                float dur_seconds = duration<float>(end - start).count();
                exit((int)dur_seconds);
            }
	    }
        for (int i = 0; i < insts; i++){
            pid_t wpid = waitpid(processes[i], &child_status, 0);
            if (WEXITSTATUS(child_status) < smallerTime){
                smallerTime = WEXITSTATUS(child_status);
                smaller = i;
            }
        }
        printf("A lebre %d venceu!\n", smaller);
    }else if (pOrT == 't' || pOrT == 'T'){
        std::vector<std::thread> threads;
        for (int i = 0; i < insts; i++){
            threads.push_back(std::thread(corrida, i, dist, pOrT));
        }
        for (int i = 0; i < insts; i++){
            threads[i].join();
        }
    }else{
        printf("Erro!\n");
    }
    return 0;
}