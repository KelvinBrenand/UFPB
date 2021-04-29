#include<iostream>
#include<cstdlib>
#include<chrono>
#include<fstream>
#include<omp.h>
using namespace std;
using namespace std::chrono;

int main(){
	int N = 802;
    for (int n = 1; n < N; n+=50){
	    int i;
	    int * x;
	    int * y;
	    int * z;
	    x = new int [n*n*n];
	    y = new int [n*n*n];
	    z = new int [n*n*n];

	    #pragma omp parallel default(none) shared(n,x,y,z) private(i)
	    {
	    	#pragma omp for
	    	for (i = 0; i < n*n*n; i++){
	        x[i] = rand()%30 + 10000;
	        y[i] = rand()%30 + 10000;
		    }
	    }

	    auto start = high_resolution_clock::now();
	    #pragma omp parallel default(none) shared(n,x,y,z) private(i)
	    {
		    #pragma omp for nowait
		    for (int i = 0; i < n*n*n; i++){
		        z[i] = x[i] * y[i];
		    }
	    }
	    auto end = high_resolution_clock::now();
	    
	    delete[] x;
	    delete[] y;
	    delete[] z;
	    auto duration = duration_cast<microseconds>(end - start);
	    cout << "Time taken: " << duration.count() << " microseconds" << endl;
	    cout << endl;
	    fstream myfile;
	    myfile.open ("vp.txt",ios::app);
	    myfile << duration.count() << ",";
	    myfile.close();
    }
    cout << "Program finished" << endl;
    return 0;
}