#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<string, char> encodedMap;
string encodedString, decodedString;

void readEncodedMap() {
    string filenameArray = "D:\\C\\ZAiSD\\lab5\\encodedArray.txt";

    ifstream file(filenameArray);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int j = 0;
            string lineToSplit[2];
            istringstream ssin(line);
            string token;

            while (getline(ssin, token, 'x')){
                lineToSplit[j] = token;
                j++;
            }

            encodedMap[lineToSplit[1].c_str()] = (char)atoi(lineToSplit[0].c_str());
        }
        file.close();
    }
}

void readEncodedString() {
    string filename = "D:\\C\\ZAiSD\\lab5\\encoded.txt";

    ifstream file(filename);
    if (file.is_open()) {
        getline(file, encodedString);
        file.close();
    }
}

void decodeString() {
    int start = 0;
    int end = 1;

    while (start + end <= encodedString.length()){
        if (encodedMap.find(encodedString.substr(start, end)) != encodedMap.end()){
            decodedString += encodedMap[encodedString.substr(start, end)];
            start += end;
            end = 1;
        }
        else
            end++;
    }
}

void saveDecodedStringToFile() {
    string filenameDecoded = "D:\\C\\ZAiSD\\lab5\\decoded.txt";

    ofstream encodedFile;
    encodedFile.open(filenameDecoded);
    encodedFile << decodedString;
    encodedFile.close();
}

int main() {
    readEncodedMap();
    readEncodedString();
    decodeString();
    saveDecodedStringToFile();

    cout << decodedString;

    return 0;
}