#include <iostream>

using namespace std;

const int INF = 9999999;
const int NIL = -9999999;

int printArrays(int d[], int pi[]){
    cout << "Array d:\n";

    for (int i=0; i < sizeof(d)-1; i++){
        cout << d[i] << " ";
    }

    cout << "\n\nArray pi:\n";

    for (int i=0; i < sizeof(pi)-1; i++){
        cout << pi[i] << " ";
    }

    cout << "\n\n";

    return 0;
}

int runList(int prev[], int next[], int edges[]){
    int d[7] = {0, INF, INF, INF, INF, INF, INF};
    int pi[7] = {NIL, NIL, NIL, NIL, NIL, NIL, NIL};

    for (int i = 0; i < sizeof(prev)-2; i++){
        
    }

    printArrays(d, pi);

    return 0;
}

int main() {
    int prev[7] = {0,1,1,0,2,3,5};
    int next[7] = {1,5,3,2,3,4,4};
    int edges[7] = {2,3,-10,3,5,4,2};

    runList(prev, next, edges);

    return 0;
}