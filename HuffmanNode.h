
#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H
#include <iostream>
#include <string>
using std::string;

class HuffmanNode{
private:
    int count;
    char character;
    string code;

    HuffmanNode* left;
    HuffmanNode* right;
public:
    HuffmanNode();
    ~HuffmanNode();

    int getCount() const;
    char getCharacter() const;
    HuffmanNode*getLeft();
    HuffmanNode*getRight();

    void setCount(int);
    void setChar(char);
    void setLeft(HuffmanNode *);
    void setRight(HuffmanNode *);
    void setCode(string a);
};
#endif