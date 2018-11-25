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
    auto lp = static_cast<long long>(1 / dx);
    double sum = 0;

    time_t time1 = time(0);

    for (int i=0; i<lp; i++){
        sum += fun(i*dx)*dx;
    }

    time_t time2 = time(0);
    time_t time = time2-time1;

    cout << sum << endl;
    cout << time << "s" << endl;

    return 0;
}