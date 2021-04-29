#include<iostream>
#include<cstdlib>
#include<chrono>
#include<fstream>
using namespace std;
using namespace std::chrono;

int main(){
	int N = 802;
    for (int n = 1; n < N; n+=50){
	    int*** x = new int**[n]; //Dynamically allocate memory for 3D arrays
	    int*** y = new int**[n];
	    int*** z = new int**[n];
	    for (int i = 0; i < n; i++)
	    {
	        x[i] = new int*[n];
	        y[i] = new int*[n];
	        z[i] = new int*[n];
	        for (int j = 0; j < n; j++){
	            x[i][j] = new int[n];
	            y[i][j] = new int[n];
	            z[i][j] = new int[n];
	        }
	    }
	    for (int i = 0; i < n; i++){
	        for (int j = 0; j < n; j++){
	            for (int k = 0; k < n; k++){
	                x[i][j][k] = rand()%30 + 10000;
	                y[i][j][k] = rand()%30 + 10000;
	            }
	        } 
	    }
	    auto start = high_resolution_clock::now();
	    for (int k = 0; k < n; k++){
	        for (int j = 0; j < n; j++){
	            for (int i = 0; i < n; i++){
	                z[i][j][k] = x[i][j][k] * y[i][j][k];
	            }
	        } 
	    }
	    auto end = high_resolution_clock::now();
	    //Deallocate the memory
	    for (int i = 0; i < n; i++)
	    {
	        for (int j = 0; j < n; j++){
	            delete[] x[i][j];
	            delete[] y[i][j];
	            delete[] z[i][j];
	        }
	        delete[] x[i];
	        delete[] y[i];
	        delete[] z[i];
	    }
	    delete[] x;
	    delete[] y;
	    delete[] z;
	    auto duration = duration_cast<microseconds>(end - start);
	    cout << "Time taken: " << duration.count() << " microseconds" << endl;
	    cout << endl;
	    fstream myfile;
	    myfile.open ("vno.txt",ios::app);
	    myfile << duration.count() << ",";
	    myfile.close();
    }
    cout << "Program finished" << endl;
    return 0;
}