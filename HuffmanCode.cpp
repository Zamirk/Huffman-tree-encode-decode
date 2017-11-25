
#include "HuffmanCode.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

HuffmanCode::HuffmanCode(){
    zerosAndOnes = "";
    poem = "";
}

void HuffmanCode::readData() {
    //Map of character frequency
    string line = "";

    ifstream myPoem;
    myPoem.open("poem.txt");

    //Looping lines of poem
    while(getline(myPoem,line)) {
        //Looping trough the line, adding each character
        for (int i = 0; i < line.length(); i++) {
            charFrequency[line[i]]++; //add one
            poem += line[i];
        }
    }
    myPoem.close();
}

void HuffmanCode::displayData(){
    cout << "Frequency Map:" << endl;
    cout << "Character \t Frequency" << endl;
    for(auto it = charFrequency.cbegin(); it != charFrequency.cend(); ++it) {
        std::cout << it->first << "\t" << it->second << endl;
    }
}

void HuffmanCode::createQueue(){
    //Creating tree
    for(auto it = charFrequency.cbegin(); it != charFrequency.cend(); ++it) {
        //Creating new node
        HuffmanNode* node = new HuffmanNode;
        node->setChar(it->first);
        node->setCount(it->second);

        //Initialising to null
        node->setRight(NULL);
        node->setLeft(NULL);
        huffmanQueue.push(node);
    }
}


/*****************************************************************************************
 *
 *     Title: An In-Depth Look At Huffman Encoding
 *     Author: Knowles Atchison Jr
 *     Date: 2011
 *     Code version: 1.0
 *     Availability: www.dreamincode.net/forums/blog/324/entry-3150-an-in-depth-look-at-huffman-encoding/
 *
***************************************************************************************/
void HuffmanCode::createTable() {
    //While priority queue is greater or equal to 2
    HuffmanNode* combined = NULL;
    while(huffmanQueue.size() >= 2) {
        //Remove the lowest
        HuffmanNode* lowest1 = huffmanQueue.top();
        huffmanQueue.pop();

        HuffmanNode* lowest2 = huffmanQueue.top();
        huffmanQueue.pop();

        //The new combine node
        combined = new HuffmanNode;
        combined->setChar(NULL);
        combined->setCount(lowest1->getCount()+lowest2->getCount());

        huffmanQueue.push(combined);
        combined->setLeft(lowest1);
        combined->setRight(lowest2);
        //Combined node points to 2 child nodes
    }
    HuffmanNode* last = huffmanQueue.top();
    HuffmanNode* root = new HuffmanNode;

    //Last one is the root of your encoding tree
    root->setChar(NULL);
    root->setCount(combined->getCount()+last->getCount());
    root->setLeft(combined);
    root->setRight(last);
    setRoot(root);
    encodeHuffmanTable(root, "");
}
void HuffmanCode::encodeHuffmanTable(HuffmanNode *root, string code){
    if(root->getLeft() == NULL){
        root->setCode(code);
        huffmanMap.insert(pair<char, string>(root->getCharacter(), code));
        return;
    }
    else{
        encodeHuffmanTable(root->getLeft(), code + "0");
        encodeHuffmanTable(root->getRight(), code + "1");
    }
}
void HuffmanCode::display(){
    cout << "Frequency Map:" << endl;
    for(auto it = huffmanMap.cbegin(); it != huffmanMap.cend(); ++it) {
        std::cout << it->first << "\t" << it->second << endl;
    }
}

void HuffmanCode::encodeString(){
    for(size_t i = 0; i < poem.length(); i++){
       zerosAndOnes.append(huffmanMap[poem.at(i)]);
   }
    ofstream outputFile("EncodedFile.txt");
    outputFile << zerosAndOnes;
}


void HuffmanCode::decodeFile() {
    string decodedPoem = "";
    string myText = "";
    string line = "";

    HuffmanNode*node = getRoot();

    ifstream file;
    file.open("EncodedFile.txt");

    //Looping lines of encoded text
    while(getline(file,line)) {
        myText +=line;
    }
    file.close();

    //Checking map against binary
   for (int i = 0; i != myText.size(); i++) {
       //If it is 0, go left, else if it is 1, go right
       if (myText[i] == '0') {
           node = node -> getLeft();
       } else if (myText[i] == '1'){
           node = node -> getRight();
       }

       // If we have reached a node with a letter
       // Adding decoded letter
       // Node is reset to the root
       if (node->getCharacter() != NULL) {
           decodedPoem += node->getCharacter();
           node = getRoot();
       }
   }
    //Outputting decoded poem to a file
    ofstream outputFile("DecodedFile.txt");
    outputFile << decodedPoem;
}

/*****************************************************************************************
 *
 *     Title: An In-Depth Look At Huffman Encoding
 *     Author: Knowles Atchison Jr
 *     Date: 2011
 *     Code version: 1.0
 *     Availability: http://stackoverflow.com/questions/23344257/convert-a-string-of-binary-into-an-ascii-string-c
 *
***************************************************************************************/
void HuffmanCode::compressFile() {
    string myText = "";
    string line = "";
    string myChar = "";
    string compressedText = "";

    ifstream file;
    file.open("EncodedFile.txt");

    //Looping lines of encoded text
    while (getline(file, line)) {
        myText += line;
    }
    file.close();

    //Turning into 8 bit pieces
    while (myText.length()%8!=0){
        extraZeros++;
        myText += "0";
    }

    for (int i = 0; i < myText.length(); i++) {
        myChar += myText.at(i);

        if ((i + 1) % 8 == 0) {

            std::stringstream mystream(myChar);
            std::string myOutput;
            while (mystream.good()) {
                std::bitset<8> bits;
                mystream >> bits;
                char a = char(bits.to_ulong());
                myOutput += a;
            }
            compressedText += myOutput;
            myChar = "";
        }
    }
    //Outputting compressed poem to a file
    ofstream outputFile("CompressedFile.txt");
    outputFile << compressedText;
}

void HuffmanCode::decompressFile() {
    string myText, line, decompressedText = "";

    ifstream file;
    file.open("CompressedFile.txt");

    //Looping lines of encoded text
    while (getline(file, line)) {
        myText += line;
    }

    file.close();
    //cout << myText;
    //Decompressing Converting ascii to binary,
    for (int i = 0; i < myText.size(); i += 2) {
        decompressedText += (std::bitset<8>(myText[i]).to_string());
    }

    //Removing extra zeros
    for(int i=0;i<extraZeros;i++){
        decompressedText.erase(decompressedText.length()-1);
    }

    //Outputting decompressed poem in binary to a file
    ofstream outputFile("DecompressedFile.txt");
    outputFile << decompressedText;

    //Extra test
    cout << "\nConverting decompressedFile.txt from binary" << endl;
    string aaa;
    HuffmanNode* node = getRoot();
    //Checking map against binary
    for (int i = 0; i != decompressedText.size(); i++) {
        //If it is 0, go left, else if it is 1, go right
        if (decompressedText[i] == '0') {
            node = node -> getLeft();
        } else if (decompressedText[i] == '1'){
            node = node -> getRight();
        }

        // If we have reached a node with a letter
        // Adding decoded letter
        // Node is reset to the root
        if (node->getCharacter() != NULL) {
            aaa += node->getCharacter();
            node = getRoot();
        }
    }
    //Outputting decoded poem to a file
    ofstream outputFilea("DecompressedFile_UNENCODED.txt");
    outputFilea << aaa;
}

