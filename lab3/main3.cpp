#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <omp.h>
#include <sys/time.h>

using namespace std;

double fun(double x){
    return 4*(1/(1+(x*x)));
}

int main() {
    double dx = 0.000000001;
    double sumArray[] = {0,0,0,0};

    time_t time1 = time(0);

#pragma omp parallel
    {
        int n = omp_get_num_threads();

        auto lp = static_cast<long long>(1 / dx);
        int k = omp_get_thread_num();
        double localSum = 0;

        for (int i=k; i<lp; i+=n){
            localSum += fun(i*dx)*dx;
        }

        sumArray[k] = localSum;
    }
    
    time_t time2 = time(0);
    time_t time = time2-time1;

    double sum = 0;

    for (double i : sumArray) {
        sum += i;
    }

    cout << sum << endl;
    cout << time << "s" << endl;

    return 0;
}