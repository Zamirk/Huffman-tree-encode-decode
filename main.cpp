#include <iostream>
#include "HuffmanCode.h"
#include "VigenereAnalyser.h"

//X00110033
//Samir Kahvedzic
//Created with Clion 1.24

using namespace std;
/*****************************************************************************************
 *
 *     Title: ROT13--How to make a Caesar cipher in c++,
 *     Author: David Caron
 *     Date: 2012
 *     Code version: 1.0
 *     Availability: https://www.youtube.com/watch?v=_EQ6TJs_TEk
 *
***************************************************************************************/
string test(string a) {
	string myText = a;

	int count = 0, length;

	length = (int)myText.length();
	for (count = 0; count<length; count++) {
		if (isalpha(myText[count])) {
			myText[count] = tolower(myText[count]);
			for (int i = 0; i < 13; i++) {
				if (myText[count] == 'z')
					myText[count] = 'a';
				else
					myText[count]++;
			}
		}
	}
	return myText;
}

void testSecret(){
	string encryptedTxt = "";
	string line = "";

	ifstream file;
	file.open("secret.txt");

	////Looping lines of encoded text
	while (getline(file, line)) {
		encryptedTxt += line;
	}

	//The occurance of each letter of the alphabet in the english language, approximately
	//ABCDEFGHIJKLMNOPQRSTUVWXYZ
	array<double, 26> englishLanguageFrequency = {
			0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
			0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
			0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
			0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
			0.01974, 0.00074};

	VigenereAnalyser test(englishLanguageFrequency);

	pair<string, string> output = test.scanText(encryptedTxt);

	cout << "The Key: " << output.second << endl << endl;
	cout << "The decrypted text (correct after first 2 sentences): " << output.first << endl;

	//Outputting decoded poem to a file
	ofstream outputFilea("SecretDecrypted.txt");
	outputFilea << output.first;
};

int main(){
	HuffmanCode* theHuffmanCode = new HuffmanCode();

	cout << "Part 1: Reading data from poem.txt" << endl;
	theHuffmanCode->readData();
	//theHuffmanCode->displayData();
	cout << "Part 2: Creating Queue" << endl;
	theHuffmanCode -> createQueue();
	cout << "Part 2: Creating Hoffman Table" << endl;
	theHuffmanCode -> createTable();
	cout << "Part 4: Encoding poem and saving to file encoded.txt" << endl;
	theHuffmanCode -> encodeString();
	cout << "Part 5: Decoding poem from encoded file and saving to file decoded.txt" << endl;
	theHuffmanCode -> decodeFile();
	cout << "Part 6: Compressing encoded.txt and writing to compressedFile.txt" << endl;
	theHuffmanCode -> compressFile();
	cout << "Part 7: DeCompressing compressedFile.txt and writing to decompressedFile.txt" << endl;
	theHuffmanCode -> decompressFile();
	cout << "Part 7 test: Un-encoding decompressed file to decompressedFileUn-encoded.txt" << endl;


	string myText = "";
	string line = "";

	ifstream file;
	file.open("poem.txt");

	////Looping lines of encoded text
	while (getline(file, line)) {
		myText += line;
	}
	cout << "Part B: 1b: Rot-13 cipher, a C++ implementd" << endl;
	cout << "" << endl;
	cout << "Poem.txt Encoded" << endl;
	string encoded = test(myText);
	cout << encoded << endl;
	cout << "" << endl;
	cout << "Poem.txt Decoded" << endl;
	cout << "Decoded" << endl;
	string decoded = test(encoded);
	cout << decoded;


	cout << "Part B: 2" << endl;
	cout << "Decrypting SECRET.TXT, Using Frequency of English Language" << endl;
	testSecret();
	cout << "Created and compiled in CLion 1.2" << endl;
	system("pause");
	return 0;
}