#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <omp.h>
#include <ctime>
#include <cmath>

using namespace std;

class Point {
public:
    int x, y;

    Point(){
        x = 0;
        y = 0;
    }

    Point(int max){
        x = rand() % (max+1);
        y = rand() % (max+1);
    }
};

bool isPointInCircle(Point *point, double r){
    return pow(point->x - r, 2) + pow(point->y - r, 2) <= pow(r, 2);
}

int main() {
    srand(time(NULL));
    int counter = 50000000;
    double r = 500;

    int circleCounter[4] = {0,0,0,0};

    time_t time1 = time(0);

#pragma omp parallel
    {
    int n = omp_get_num_threads();
    int k = omp_get_thread_num();

    for (int i=0; i<counter; i+=n){
        Point *point = new Point(2 * r);

        if (isPointInCircle(point, r))
            circleCounter[k]++;
    }
}

    time_t time2 = time(0);
    time_t time = time2-time1;

    int circleCounterSum = 0;

    for (int i=0; i<4; i++){
        circleCounterSum += circleCounter[i];
    }

    double pi = ((double)(4*circleCounterSum)) / counter;

    cout << "pi = " << pi << endl;
    cout << time << "s" << endl;

    return 0;
}