#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H

using namespace std;
#include <string>
#include<map>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "HuffmanNode.h"

using std::string;
using std::map;

class HuffmanCode{
private:
    map<char, int> charFrequency;
    map<char, string> huffmanMap;

    //The Compare struct
    //Used to compare 2 differnt nodes together by their count
    struct compareStruct {
    public:
        bool operator()(const HuffmanNode* one, const HuffmanNode* two){
            return one->getCount() > two->getCount();
        }
    };
    //Declaring priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareStruct> huffmanQueue;

    string poem;
    string zerosAndOnes;

    HuffmanNode *root;
    int extraZeros = 0;
public:
    HuffmanCode();
    ~HuffmanCode();

    void readData();
    void displayData();
    void createQueue();
    void createTable();
    void display();
    void encodeHuffmanTable(HuffmanNode *, string);
    void encodeString();
    void decodeString(string);
    void setRoot(HuffmanNode *a)      {root = a;};
    HuffmanNode* getRoot() { return root;};

    string getChar()						        {return poem;};
    string getEncodedString()						{return zerosAndOnes;};
    void displayTable();
    void displayHuffmanTable();
    void decodeFile();
    void compressFile();
    void decompressFile();
};
#endif
