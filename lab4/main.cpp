#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>

using namespace std;

int partition(int tablica[], int startValue, int endValue){
    int i = startValue;
    int j = endValue;
    int t;
    int w = tablica[(startValue + endValue) / 2];

    while (i <= j){
        while (tablica[i] < w)
            i++;

        while (tablica[j] > w)
            j--;

        if (i <= j) {
            t = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = t;
            i++;
            j--;
        }
    }

    return i;
}

void quickSort(int tablica[], int startValue, int endValue) {
    int length = endValue - startValue;

    if (length < 2) {
        return;
    }
    else {
        int polowa = partition(tablica, startValue, endValue);
        quickSort(tablica, startValue, polowa-1);
        quickSort(tablica, polowa, endValue);
    }
}

/** ********************* **/

void quickSortParallelNested(int tablica[], int startValue, int endValue) {
    int polowa;

    if (startValue < endValue) {
        polowa = partition(tablica, startValue, endValue);
        omp_set_nested(1);
#pragma omp parallel sections num_threads(4)
        {
#pragma omp section
            quickSort(tablica, startValue, polowa-1);
#pragma omp section
            quickSort(tablica, polowa, endValue);
        }
    }
}

void quickSortParallelTasks(int tablica[], int startValue, int endValue) {
    int polowa;
    if (startValue < endValue){
        polowa = partition(tablica, startValue, endValue);
#pragma omp task
        quickSortParallelNested(tablica, startValue, polowa-1);
#pragma omp task
        quickSortParallelNested(tablica, polowa, endValue);
    }
}

void quickSortParallel(int tablica[], int startValue, int endValue) {
    #pragma omp parallel
    #pragma omp single
    quickSortParallelTasks(tablica, startValue, endValue);
}

int tablica[10000000];
int tablica2[10000000];

int main() {
    int tablicaSize = 10000000;
    int attemps = 5;
    srand(time(NULL));

    for (int q=0; q<attemps; q++) {

        cout << "START - " << tablicaSize << " ELEMENTOW" << endl;

        for (int i = 0; i < tablicaSize; i++) {
            int value = rand();
            tablica[i] = value;
            tablica2[i] = value;
        }

        cout << "WYLOSOWANO ELEMENTY" << endl;

        double start_time = omp_get_wtime();
        quickSort(tablica, 0, tablicaSize - 1);
        double time = omp_get_wtime() - start_time;

        cout << "SEKWENCYJNIE: " << time << "s" << endl;

        double start_time2 = omp_get_wtime();
        quickSortParallel(tablica2, 0, tablicaSize - 1);
        double time2 = omp_get_wtime() - start_time2;

        cout << "PARALELNIE: " << time2 << "s" << endl;

        cout << "\n" << ((time2 - time) / time) * 100 << "%" << endl;

        bool control = true;
        for (int i = 0; i < tablicaSize; i++) {
            if (tablica[i] != tablica2[i]) {
                cout << "NIEZGODNOSC TABLIC" << endl;
                control = false;
                break;
            }
        }
        if (control) {
            cout << "TABLICE ZGODNE" << endl;
        }

        cout << "---------------\n\n";
    }

    return 0;
}