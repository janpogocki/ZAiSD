#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

const int INF = 9999999;
const int NIL = -9999999;

int *d;
int *pi;

// edges vertices (file 1st line)
int edges;
int vertices;

int maxFlow;

int *prevArr;
int *nextArr;
int *edgesArr;
int **matrixArr;

int findPath();
int findPathMatrix();
int calculateFlow(int destination);

int printArrays(){
    cout << "Array d:\n";

    for (int i=0; i < vertices; i++){
        cout << d[i] << " ";
    }

    cout << "\n\nArray pi:\n";

    for (int i=0; i < vertices; i++) {
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

    return 0;
}

int allocateGraphArrays(int n){
    prevArr = new int[n];
    nextArr = new int[n];
    edgesArr = new int[n];

    return 0;
}

int allocateMatrix(int n){
    matrixArr = new int*[n];
    for (int i=0; i<n; i++){
        matrixArr[i] = new int[n];
    }

    return 0;
}

int convertFromList(string filename){
    allocateArrays(edges+10000);
    allocateGraphArrays(edges+10000);

    int i = 0;
    string lineToSplit[3];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {

            if (i == 0) {
                istringstream ssin(line);
                int j = 0;
                string token;

                while (getline(ssin, token, ' ')){
                    lineToSplit[j] = token;
                    j++;
                }

                edges = atoi(lineToSplit[0].c_str());
                vertices = atoi(lineToSplit[1].c_str());
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

int convertFromMatrix(string filename){
    allocateArrays(edges+10000);
    allocateMatrix(edges+10000);

    int i = 0;
    string lineToSplit[256];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {

            if (i == 0) {
                istringstream ssin(line);
                int j = 0;
                string token;

                while (getline(ssin, token, ' ')){
                    lineToSplit[j] = token;
                    j++;
                }

                edges = atoi(lineToSplit[0].c_str());
                vertices = atoi(lineToSplit[1].c_str());

                allocateArrays(edges+10000);
            }
            else {
                istringstream ssin(line);
                int j = 0;
                string token;

                while (getline(ssin, token, ' ')){
                    lineToSplit[j] = token;
                    j++;
                }

                for (int k=0; k<edges; k++){
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

/********* LIST **********/

int findPath(){
    for (int i = 0; i < vertices-1; i++){

        for (int j = 0; j < edges; j++){

            if (d[prevArr[j]] != INF && d[nextArr[j]] > d[prevArr[j]] + edgesArr[j] && edgesArr[j] != 0){
                d[nextArr[j]] = d[prevArr[j]] + edgesArr[j];
                pi[nextArr[j]] = prevArr[j];
            }

        }

    }

    return 0;
}

bool isPathExists(int destination){
    allocateArrays(edges+10000);
    findPath();

    return d[destination] != INF;
}

int getEdge(int a, int b){
    for (int i=0; i < edges; i++){
        if (prevArr[i] == a && nextArr[i] == b)
            return edgesArr[i];
    }

    return NIL;
}

int getEdgeIndexInArray(int a, int b){
    for (int i=0; i < edges; i++){
        if (prevArr[i] == a && nextArr[i] == b)
            return i;
    }

    return NIL;
}

int calculateFlow(int destination){
    int p;
    maxFlow = 0;

    while (isPathExists(destination)){
        int pathFlow = INF;

        for (int next = destination; next != 0; next = pi[next]) {
            p = pi[next];
            int edge = getEdge(p, next);
            pathFlow = min(pathFlow, edge);
        }

        for (int next = destination; next != 0; next = pi[next]) {
            p = pi[next];

            int edge = getEdge(p, next);
            if (edge != NIL) {
                edge -= pathFlow;
                edgesArr[getEdgeIndexInArray(p, next)] = edge;
            }

            edge = getEdge(next, p);
            if (edge != NIL) {
                edge += pathFlow;
                edgesArr[getEdgeIndexInArray(next, p)] = edge;
            }
            else {
                edges++;

                prevArr[edges-1] = next;
                nextArr[edges-1] = p;
                edgesArr[edges-1] = pathFlow;
            }
        }

        maxFlow += pathFlow;
    }
    cout << "PRZEPUSTOWOSC LISTY: " << maxFlow << "\n";

    return 0;
}

int runList(int destination){
    convertFromList("D:\\C\\ZAiSD\\lab2\\list.txt");

    findPath();

    calculateFlow(destination);

    return 0;
}

/********* MATRIX **********/

int findPathMatrix(){
    for (int i = 0; i < vertices-1; i++){

        for (int j = 0; j < vertices; j++){

            for (int k = 0; k < vertices; k++){

                if (d[j] != INF && matrixArr[j][k] != NIL && d[k] > d[j] + matrixArr[j][k] && matrixArr[j][k] != 0){
                    d[k] = d[j] + matrixArr[j][k];
                    pi[k] = j;
                }

            }

        }

    }

    return 0;
}

bool isPathExistsMatrix(int destination){
    allocateArrays(edges+10000);
    findPathMatrix();

    return d[destination] != INF;
}

int calculateFlowMatrix(int destination){
    int p;
    int maxFlow = 0;
    while (isPathExistsMatrix(destination)) {
        int pathFlow = INF;

        for (int k = destination; k != 0; k = pi[k]) {
            p = pi[k];
            pathFlow = min(pathFlow, matrixArr[p][k]);
        }

        for (int k = destination; k != 0; k = pi[k]) {
            p = pi[k];
            matrixArr[p][k] -= pathFlow;

            if (matrixArr[k][p] == NIL){
                matrixArr[k][p] = pathFlow;

            }
            else {
                matrixArr[k][p] += pathFlow;
            }
        }
        maxFlow += pathFlow;
    }
    cout << "PRZEPUSTOWOSC MACIERZY: " << maxFlow << "\n";

    return 0;
}

int runMatrix(int destination){
    convertFromMatrix("D:\\C\\ZAiSD\\lab2\\matrix.txt");
    findPathMatrix();

    calculateFlowMatrix(destination);

    return 0;
}

/* --------------------- */

int main() {
    runList(2);

    cout << "-----------------------" << endl;

    runMatrix(2);

    return 0;
}