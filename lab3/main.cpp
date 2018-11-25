#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <omp.h>

using namespace std;

int main() {
#pragma omp parallel
    {
        int n, k;
        n = omp_get_num_threads();
        k = omp_get_thread_num();

        cout << n << ", " << k << endl;
    }

    return 0;
}