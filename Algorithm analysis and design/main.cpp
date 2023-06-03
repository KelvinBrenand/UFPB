#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

int readData(string str, int &NUMBER_OF_LINES, int &NUMBER_OF_PRODUCTS, vector<int> &t, vector<vector<int>> &s){
    ifstream inFile(str);
    inFile >> NUMBER_OF_LINES >> NUMBER_OF_PRODUCTS;
    int aux;
    for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
        inFile >> aux;
        t.push_back(aux);
    }
    for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
        vector<int> aux2;
        for (int j = 0; j < NUMBER_OF_PRODUCTS; j++){
            inFile >> aux;
            aux2.push_back(aux);
        }
        s.push_back(aux2);
    }
    inFile.close();
    return 0;
}

void print(vector<vector<int>> curr_order_lines, vector<int> curr_solution_lines, int NUMBER_OF_LINES){
    for (int i = 0; i < NUMBER_OF_LINES; i++){
        cout<<"Line #"<<i+1<<": ";
        for (int j = 0; j < curr_order_lines[i].size(); j++){
            cout<<curr_order_lines[i][j]<<" ";
        }
        cout<<endl; 
    }

    for (int j = 0; j < curr_solution_lines.size(); j++){
        cout<<"Line #"<<j+1<<" solution: "<<curr_solution_lines[j]<<endl;
    }

    cout<<"Final solution: "<<*max_element(curr_solution_lines.begin(), curr_solution_lines.end())<<endl;
    cout<<endl;
}

int computeSolution(vector<int> line, vector<int> t, vector<vector<int>> s){
    int totalTime = 0;
    for (int i=0; i<line.size(); i++){
        totalTime += t[line[i]-1];
    }
    for (int i=0; i<line.size()-1; i++){
        totalTime += s.at(line[i]-1).at(line[i+1]-1);
    } 
    return totalTime;
}

int greedyAlg(int NUMBER_OF_LINES, int NUMBER_OF_PRODUCTS, vector<vector<int>> s, vector<int> t, vector<vector<int>> &lines, vector<int> &line_times){
    /*
    Pseudocódigo do algoritmo guloso
    _______________________________________________________________________
    Inicie com uma solução vazia (As linhas de produção estão vazias)
    Se  numero_de_linhas >=  numero_de_produtos então
    retorne max(t)
    Senão
    Para toda linha de s
        Somar cada uma de suas colunas com cada uma das colunas de t
    Criar a matrix nextProdTime com esses valores

    Para toda linha de nextProdTime
        Somar suas colunas
    Criar o array nextProdTime com esses valores

    Dentre os produtos disponíveis
    Selecionar aquele com o menor valor correspondente em nextProdTime
    Distribuir os itens nas linhas de produção de modo alternado
    _______________________________________________________________________
    Obs.: Algoritmo assume que o tempo de produção dos produtos é similar.
    Produtos com alta variância em seus tempos de produção não serão bem
    distribuidos entre as linhas de produção por esse algoritmo.
    */

    if (NUMBER_OF_LINES >= NUMBER_OF_PRODUCTS){ // Best case scenario
        cout << "THE SOLUTION IS " << *max_element(t.begin(), t.end()) << " MINUTES." << endl;
    }
    else{
        int nextProdTime[NUMBER_OF_PRODUCTS][NUMBER_OF_PRODUCTS] = {}; // Creates a matrix representing next product time + maintenance time

        for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
            for (int j = 0; j < NUMBER_OF_PRODUCTS; j++){
                if (i == j){
                    continue;
                }else{
                    nextProdTime[i][j] = s[i][j] + t[j];
                }
            }
        }

        int nextProdTimeSum[NUMBER_OF_PRODUCTS] = {}; // Sorts the products based on the nextProdTime matrix
        vector<int> prodOrder;

        for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
            for (int j = 0; j < NUMBER_OF_PRODUCTS; j++){
                nextProdTimeSum[i] += nextProdTime[i][j];
            }
            prodOrder.push_back(i + 1);
        }

        pair<int, int> pair_arr[NUMBER_OF_PRODUCTS];

        for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
            pair_arr[i].first = nextProdTimeSum[i];
            pair_arr[i].second = prodOrder[i];
        }

        sort(pair_arr, pair_arr + NUMBER_OF_PRODUCTS);
        for (int i = 0; i < NUMBER_OF_PRODUCTS; i++){
            prodOrder[i] = pair_arr[i].second;
        }

        // Splits the sorted order of products among the production lines
        int count = 0, i = 0;
        while (true){
            if (i >= NUMBER_OF_PRODUCTS){break;}
            if (count >= NUMBER_OF_LINES){count = 0;}
            lines[count].push_back(prodOrder[i]);
            i++;
            count++;
        }

        //Finds out the solution
        for (int i = 0; i < NUMBER_OF_LINES; i++){
            int aux = computeSolution(lines[i], t, s);
            line_times.push_back(aux);
        }
    }
    return 0;
}

int swap(vector<vector<int>> &curr_order_lines, vector<int> &curr_solution_lines, vector<vector<int>> s){
    bool swap = false;
    for (int h = 0; h < curr_solution_lines.size(); h++){
        int best_i=-1, best_j=-1, curr_solutionCopy=curr_solution_lines[h];
        for(int i = 0; i<curr_order_lines[h].size();i++){
            for(int j = i+1; j< curr_order_lines[h].size();j++){
                int best_solution = curr_solution_lines[h];
                set<vector<int>> prep_times;
                if(i==j){continue;}
                try{prep_times.insert({curr_order_lines[h].at(i-1),curr_order_lines[h].at(i)});}catch (...) {}
                prep_times.insert({curr_order_lines[h].at(i),curr_order_lines[h].at(i+1)});
                prep_times.insert({curr_order_lines[h].at(j-1),curr_order_lines[h].at(j)});
                try{prep_times.insert({curr_order_lines[h].at(j),curr_order_lines[h].at(j+1)});}catch (...) {}
                for (auto k : prep_times) {
                    best_solution -= s.at(k[0]-1).at(k[1]-1);
                }
                if(j-i==1){//se forem adjacentes
                    prep_times.clear();
                    try{prep_times.insert({curr_order_lines[h].at(i-1),curr_order_lines[h].at(j)});}catch (...) {}
                    prep_times.insert({curr_order_lines[h].at(j),curr_order_lines[h].at(i)});
                    try{prep_times.insert({curr_order_lines[h].at(i),curr_order_lines[h].at(j+1)});}catch (...) {}
                }else{
                    prep_times.clear();
                    try{prep_times.insert({curr_order_lines[h].at(i-1),curr_order_lines[h].at(j)});}catch (...) {}
                    prep_times.insert({curr_order_lines[h].at(j),curr_order_lines[h].at(i+1)});
                    prep_times.insert({curr_order_lines[h].at(j-1),curr_order_lines[h].at(i)});
                    try{prep_times.insert({curr_order_lines[h].at(i),curr_order_lines[h].at(j+1)});}catch (...) {}
                }
                for (auto k : prep_times) {
                    best_solution += s.at(k[0]-1).at(k[1]-1);
                }
                if(best_solution<curr_solutionCopy){
                    curr_solutionCopy = best_solution;
                    best_i=i;
                    best_j=j;
                }
            }
        }
        if(curr_solutionCopy<curr_solution_lines[h]){
            int aux = curr_order_lines[h][best_i];
            curr_order_lines[h][best_i] = curr_order_lines[h][best_j];
            curr_order_lines[h][best_j] = aux;
            curr_solution_lines[h] = curr_solutionCopy;
            swap = true;
        }
    }
    if(swap){
        return 0;
    }else{
        return -1;
    }
}

int interSwap(vector<vector<int>> &curr_order_lines, vector<int> &curr_solution_lines, vector<vector<int>> s, vector<int> t){
    int biggestSolution = *max_element(curr_solution_lines.begin(), curr_solution_lines.end());

    for(int i=0;i<curr_order_lines.size();i++){
        for(int j=0;j<curr_order_lines.size();j++){
            if(i==j){continue;}
            for(int k=0;k<curr_order_lines[i].size();k++){
                for(int l=0;l<curr_order_lines[j].size();l++){
                    int solution1 = curr_solution_lines[i];
                    int aux1 = curr_solution_lines[i]-t[curr_order_lines[i][k]-1]+t[curr_order_lines[j][l]-1];
                    try{aux1 = aux1-s.at(curr_order_lines[i][k-1]-1).at(curr_order_lines[i][k]-1);}catch (...) {}
                    try{aux1 = aux1-s.at(curr_order_lines[i][k]-1).at(curr_order_lines[i][k+1]-1);}catch (...) {}
                    try{aux1 = aux1+s.at(curr_order_lines[i][k-1]-1).at(curr_order_lines[j][l]-1);}catch (...) {}
                    try{aux1 = aux1+s.at(curr_order_lines[j][l]-1).at(curr_order_lines[i][k+1]-1);}catch (...) {}

                    int solution2 = curr_solution_lines[j];
                    int aux2 = curr_solution_lines[j]-t[curr_order_lines[j][l]-1]+t[curr_order_lines[i][k]-1];
                    try{aux2 = aux2-s.at(curr_order_lines[j][l-1]-1).at(curr_order_lines[j][l]-1);}catch (...) {}
                    try{aux2 = aux2-s.at(curr_order_lines[j][l]-1).at(curr_order_lines[j][l+1]-1);}catch (...) {}
                    try{aux2 = aux2+s.at(curr_order_lines[j][l-1]-1).at(curr_order_lines[i][k]-1);}catch (...) {}
                    try{aux2 = aux2+s.at(curr_order_lines[i][k]-1).at(curr_order_lines[j][l+1]-1);}catch (...) {}

                    curr_solution_lines[i] = aux1;
                    curr_solution_lines[j] = aux2;
                    if (*max_element(curr_solution_lines.begin(), curr_solution_lines.end()) < biggestSolution){
                        int aux3 = curr_order_lines[i][k];
                        curr_order_lines[i][k] = curr_order_lines[j][l];
                        curr_order_lines[j][l] = aux3;
                        return 0;
                    }else{
                        curr_solution_lines[i] = solution1;
                        curr_solution_lines[j] = solution2;
                    }
                }
            }
        }
    }
    return -1;
}

int VND(vector<vector<int>> &curr_order_lines, vector<int> &curr_solution_lines, vector<vector<int>> s, vector<int> t){
    int r=2; //Estruturas diferentes de vizinhança
    int k=1; //Estrutura de vizinhaça corrente
    while (k<=r){
        int aux = (k==1) ? swap(curr_order_lines, curr_solution_lines, s) : interSwap(curr_order_lines, curr_solution_lines, s, t);
        if(aux==0){
            k=1;
        }else{
            k++;
        }
    }
    return 0;
}

int main(){
    int NUMBER_OF_LINES, NUMBER_OF_PRODUCTS;
    vector<int> t;
    vector<vector<int>> s;
    readData("instancias\\data.txt", NUMBER_OF_LINES, NUMBER_OF_PRODUCTS, t, s);
    
    vector<vector<int>> lines(NUMBER_OF_LINES);
    vector<int> line_times;

    auto start = high_resolution_clock::now();
    greedyAlg(NUMBER_OF_LINES, NUMBER_OF_PRODUCTS, s, t, lines, line_times);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    print(lines, line_times, NUMBER_OF_LINES);
    cout << "Time taken by greedyAlg: "<< duration.count() << " microseconds" << endl;

    auto start2 = high_resolution_clock::now();
    VND(lines, line_times, s, t);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    print(lines, line_times, NUMBER_OF_LINES);
    cout << "Time taken by VND: "<< duration2.count() << " microseconds" << endl;
    return 0;
}