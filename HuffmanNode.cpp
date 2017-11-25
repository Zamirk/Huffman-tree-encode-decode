
#include "HuffmanNode.h"
using namespace std;

HuffmanNode::HuffmanNode(){
    //Initial values
    left = NULL;
    right = NULL;
    count = 0;
}

HuffmanNode::~HuffmanNode(){
    //Deleting left anf right pointers
    if(left != NULL) delete left;
    if(right != NULL) delete right;
}

int HuffmanNode::getCount() const{
    return count;
}
char HuffmanNode::getCharacter() const{
    return  character;
}
HuffmanNode* HuffmanNode::getLeft(){
    return left;
};
HuffmanNode* HuffmanNode::getRight(){
    return right;
};

void HuffmanNode::setCount(int a){
    count = a;
};
void HuffmanNode::setChar(char a){
    character = a;
};
void HuffmanNode::setLeft(HuffmanNode *a){
    left = a;
};
void HuffmanNode::setRight(HuffmanNode *a){
    right = a;
};
void HuffmanNode::setCode(string a){
    code + a;
};

