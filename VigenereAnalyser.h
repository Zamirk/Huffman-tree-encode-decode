
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
using namespace std;

#ifndef UNTITLED5_VIGENEREANALYSER_H
#define UNTITLED5_VIGENEREANALYSER_H

/*****************************************************************************************
 *
 *     Title: Extract the key and plaintext from a Vigenère cipher
 *     Author: User: MagiMaster
 *     Date: 2011
 *     Code version: 2.0
 *     Availability: http://rosettacode.org/wiki/Vigen%C3%A8re_cipher/Cryptanalysis
 *
***************************************************************************************/

//Explanation of code

//As an input, it takes only the encrypted text.
//It is assumed that the un encrypted text is in English for this to work.
//Frequency analysis is done first,
//The key is found,
//The key is used to decrypt and output the original plaintext.
//The algorithm is not perfect and can have mistakes


typedef array<pair<char, double>, 26> listOfResults;

class VigenereAnalyser {
private:
    //Targets/sorted results are places in here
    array<double, 26> targets, sorted;
    listOfResults frequencyResults;
public:
    listOfResults &frequency(const string& input);
    double correlation(const string& input);
    VigenereAnalyser(const array<double, 26>& targetFreqs);
    pair<string, string> scanText(string input);
};

#endif //UNTITLED5_VIGENEREANALYSER_H
