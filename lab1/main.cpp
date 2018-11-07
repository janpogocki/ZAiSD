#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

const int INF = 9999999;
const int NIL = -9999999;

int *d;
int *pi;

int n;
int *prevArr;
int *nextArr;
int *edgesArr;
int **matrixArr;

int printArrays(){
    cout << "Array d:\n";

    for (int i=0; i < sizeof(d)-2; i++){
        cout << d[i] << " ";
    }

    cout << "\n\nArray pi:\n";

    for (int i=0; i < sizeof(pi)-2; i++) {
        if (pi[i] == NIL)
            cout << "NIL ";
        else
            cout << pi[i] << " ";
    }

    cout << "\n\n";

    return 0;
}

int allocateArrays(int n){
    d = new int[n];
    pi = new int[n];

    for (int i=0; i<n; i++) {
        if (i == 0)
            d[i] = 0;
        else
            d[i] = INF;

        pi[i] = NIL;
    }

    prevArr = new int[n];
    nextArr = new int[n];
    edgesArr = new int[n];

    matrixArr = new int*[n];
    for (int i=0; i<n; i++){
        matrixArr[i] = new int[n];
    }

    return 0;
}

int convertFromList(string filename){
    int i = 0;
    string lineToSplit[3];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {

            if (i == 0) {
                n = atoi(line.c_str());
                allocateArrays(n);
            }
            else {
                istringstream ssin(line);
                int j = 0;
                string token;

                while (getline(ssin, token, ' ')){
                    lineToSplit[j] = token;
                    j++;
                }

                prevArr[i-1] = atoi(lineToSplit[0].c_str());
                nextArr[i-1] = atoi(lineToSplit[1].c_str());
                edgesArr[i-1] = atoi(lineToSplit[2].c_str());
            }

            i++;
        }
        file.close();
    }

    return 0;
}

int runList(){
    convertFromList("D:\\C\\ZAiSD\\lab1\\list.txt");

    for (int i = 0; i < n-1; i++){

        for (int j = 0; j < n; j++){

            if (d[nextArr[j]] > d[prevArr[j]] + edgesArr[j]){
                d[nextArr[j]] = d[prevArr[j]] + edgesArr[j];
                pi[nextArr[j]] = prevArr[j];
            }

        }

    }

    printArrays();

    return 0;
}

int convertFromMatrix(string filename){
    int i = 0;
    string lineToSplit[256];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {

            if (i == 0) {
                n = atoi(line.c_str());
                allocateArrays(n);
            }
            else {
                istringstream ssin(line);
                int j = 0;
                string token;

                while (getline(ssin, token, ' ')){
                    lineToSplit[j] = token;
                    j++;
                }

                for (int k=0; k<n; k++){
                    if (lineToSplit[k] == "*")
                        matrixArr[k][i-1] = NIL;
                    else
                        matrixArr[k][i-1] = atoi(lineToSplit[k].c_str());
                }
            }

            i++;
        }
        file.close();
    }

    return 0;
}

int runMatrix(){
    convertFromMatrix("D:\\C\\ZAiSD\\lab1\\matrix.txt");

    for (int i = 0; i < n-1; i++){

        for (int j = 0; j < n; j++){

            for (int k = 0; k < n; k++){

                if (matrixArr[j][k] != NIL
                        && d[k] > d[j] + matrixArr[j][k]){
                    d[k] = d[j] + matrixArr[j][k];
                    pi[k] = j;
                }

            }

        }

    }

    printArrays();

    return 0;
}

int main() {
    cout << "List:\n\n";

    runList();

    cout << "-----------------------\n\n";

    cout << "Matrix:\n\n";

    runMatrix();

    return 0;
}