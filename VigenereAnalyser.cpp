
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

#include "VigenereAnalyser.h"

    // An array of frequencies is created
    listOfResults & VigenereAnalyser::frequency(const string& input) {
        for (char current = 'A'; current <= 'Z'; ++current) {
            frequencyResults[current - 'A'] = make_pair(current, 0);
        }

        for (size_t i = 0; i < input.size(); ++i){
            frequencyResults[input[i] - 'A'].second++;
        }
        //Frequency is returned
        return frequencyResults;
    }

    //Analysis correlation
    double VigenereAnalyser::correlation(const string& input)  {
        double result = 0.0;
        frequency(input);

        sort(frequencyResults.begin(), frequencyResults.end(), [](pair<char, double> u, pair<char, double> v)->bool
        { return u.second < v.second; });

        for (size_t i = 0; i < 26; ++i)
            result += frequencyResults[i].second * sorted[i];

        return result;
    }
    VigenereAnalyser::VigenereAnalyser(const array<double, 26>& targetFreqs) {
        targets = targetFreqs;
        sorted = targets;
        sort(sorted.begin(), sorted.end());
    }
    pair<string, string> VigenereAnalyser::scanText(string input)  {
        string cleaned;
        for (size_t i = 0; i < input.size(); ++i)
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
                cleaned += input[i];
            else if (input[i] >= 'a' && input[i] <= 'z')
                cleaned += input[i] + 'A' - 'a';
        }

        size_t bestLength = 0;
        double bestCorr = -100.0;

        // Assume that if there are less than 20 characters
        // per column, the key's too long to guess
        for (size_t i = 2; i < cleaned.size() / 20; ++i)
        {
            vector<string> pieces(i);
            for (size_t j = 0; j < cleaned.size(); ++j)
                pieces[j % i] += cleaned[j];

            // The correlation increases artificially for smaller
            // pieces/longer keys, so weigh against them a little
            double corr = -0.5*i;
            for (size_t j = 0; j < i; ++j)
                corr += correlation(pieces[j]);

            if (corr > bestCorr)  {
                bestLength = i;
                bestCorr = corr;
            }
        }

        if (bestLength == 0)
            return make_pair("Text is too short to scanText", "");

        vector<string> pieces(bestLength);
        for (size_t i = 0; i < cleaned.size(); ++i)
            pieces[i % bestLength] += cleaned[i];

        vector<listOfResults> freqs;
        for (size_t i = 0; i < bestLength; ++i)
            freqs.push_back(frequency(pieces[i]));

        string key = "";
        for (size_t i = 0; i < bestLength; ++i) {
            sort(freqs[i].begin(), freqs[i].end(), [](pair<char, double> u, pair<char, double> v)->bool
            { return u.second > v.second; });

            size_t m = 0;
            double mCorr = 0.0;
            for (size_t j = 0; j < 26; ++j) {
                double corr = 0.0;
                char c = 'A' + j;
                for (size_t k = 0; k < 26; ++k) {
                    int d = (freqs[i][k].first - c + 26) % 26;
                    corr += freqs[i][k].second * targets[d];
                }

                if (corr > mCorr) {
                    m = j;
                    mCorr = corr;
                }
            }

            key += m + 'A';
        }

        string result = "";
        for (size_t i = 0; i < cleaned.size(); ++i)
            result += (cleaned[i] - key[i % key.length()] + 26) % 26 + 'A';

        return make_pair(result, key);
    }

