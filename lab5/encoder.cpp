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

class BTNode {
public:
    BTNode* leftChild = nullptr;
    BTNode* rightChild = nullptr;
    char letter;
    int frequency;

    BTNode(char letter, int frequency) : letter(letter), frequency(frequency) {}

    BTNode(BTNode *leftChild, BTNode *rightChild, char letter, int frequency) : leftChild(leftChild),
                                                                                rightChild(rightChild), letter(letter),
                                                                                frequency(frequency) {}

    BTNode(const BTNode &node){
        leftChild = node.leftChild;
        rightChild = node.rightChild;
        letter = node.letter;
        frequency = node.frequency;
    }
};

vector<BTNode*> btVector;
map<char, string> encodedMap;

void countCharsFreq(string text) {
    map<char, int> charsFreq;

    for (char c : text) {
        charsFreq[c]++;
    }

    for (auto const& x : charsFreq) {
        BTNode* btNode = new BTNode(x.first, x.second);
        btVector.push_back(btNode);
    }
}

vector<int> getMinTwoKeysOfBtList() {
    vector<int> returned;
    int firstMinValueKey = -1;

    for (int j=0; j<2; j++){
        int minValue = INT32_MAX;
        int minValueKey = -1;

        for (int i=0; i<btVector.size(); i++){
            if (i != firstMinValueKey && btVector[i]->frequency < minValue){
                minValue = btVector[i]->frequency;
                minValueKey = i;
            }
        }

        returned.push_back(minValueKey);
        firstMinValueKey = minValueKey;
    }

    sort(returned.begin(), returned.end());
    return returned;
}

void minimalizeVectorOfTrees() {
    while (btVector.size() > 1) {
        vector<int> minNodes = getMinTwoKeysOfBtList();

        BTNode* nodeLeft = new BTNode(*btVector[minNodes[0]]);
        BTNode* nodeRight = new BTNode(*btVector[minNodes[1]]);

        BTNode* newNode = new BTNode(nodeLeft, nodeRight, -1, nodeLeft->frequency + nodeRight->frequency);

        btVector.erase(btVector.begin() + minNodes[1]);
        btVector.erase(btVector.begin() + minNodes[0]);

        btVector.push_back(newNode);
    }
}

void visitNode(BTNode* node, const string &currentPath){
    if (node->leftChild != nullptr)
        visitNode(node->leftChild, string(currentPath).append("0"));

    if (node->rightChild != nullptr)
        visitNode(node->rightChild, string(currentPath).append("1"));

    if (node->leftChild == nullptr && node->rightChild == nullptr)
        encodedMap[node->letter] = currentPath;
}

string getEncodedText(string text) {
    string returned;

    for (char c : text) {
        returned.append(encodedMap[c]);
    }

    return returned;
}

void saveFiles(const string &text) {
    string filename = "D:\\C\\ZAiSD\\lab5\\encoded.txt";
    string filenameArray = "D:\\C\\ZAiSD\\lab5\\encodedArray.txt";

    ofstream encodedFile;
    encodedFile.open(filename);
    encodedFile << text;
    encodedFile.close();

    encodedFile.open(filenameArray);

    for (auto const& element : encodedMap){
        encodedFile << (int)element.first << "x" << element.second << "\n";
    }

    encodedFile.close();
}

int main() {
    string text = "AGH WD to zaakceptowana przez AGH, jedyna taka aplikacja dla studentow, dzieki ktorej wreszcie mozesz przegladac swoj indeks AGH na smartfonie lub tablecie. Czytelnie i przejrzyscie!";

    countCharsFreq(text);
    minimalizeVectorOfTrees();
    visitNode(btVector[0], "");

    string encodedText = getEncodedText(text);
    saveFiles(encodedText);

    return 0;
}