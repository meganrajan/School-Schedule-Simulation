#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recursiveFill(string& currentWord, int index, const string& in, vector<int>& usedFloating, const string& floating, set<string>& results, const set<string>& dict);
bool isWordValid(const string& word, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    string currentWord = in;
    vector<int> usedFloating(floating.length(), 0); // tracks usage of floating characters
    set<string> results;
    recursiveFill(currentWord, 0, in, usedFloating, floating, results, dict);
    return results;

}

// // Define any helper functions here
bool isWordValid(const string& word, const set<string>& dict) {
    return dict.find(word) != dict.end();
}

void recursiveFill(string& currentWord, int index, const string& in, vector<int>& usedFloating, const string& floating, set<string>& results, const set<string>& dict) {
    if (index == currentWord.size()) {
        // check if all floating characters have been used
        for (int count : usedFloating) {
            if (count == 0) return;

        }
        if (isWordValid(currentWord, dict)) {
            results.insert(currentWord);
        }

        return;
    }

    // at the beginning -- # dahses < floating characters; return;
    int numDashes = 0;
    int floatingLeft = 0;

    for(int i = 0; i < usedFloating.size(); i++) {
        if(usedFloating[i] == 0) {
            floatingLeft++;
        }
    }

    for(int i = 0; i < currentWord.size(); i++) {
        if(currentWord[i] == '-') {
            numDashes++;
        }
    }

    if(numDashes < floatingLeft) {
        return;
    }
    

    if (currentWord[index] != '-') {
        recursiveFill(currentWord, index + 1, in, usedFloating, floating, results, dict);

    } else {
        // try all possible letters if the position is not fixed
        int ind = 0;

        for (char c = 'a'; c <= 'z'; ++c) {
            currentWord[index] = c;
       
            // check if curr is a floating char
            bool isFloating = false;

            for (size_t i = 0; i < floating.size(); ++i) {

                if (floating[i] == c && usedFloating[i] < 1) {
                    usedFloating[i]++;

                    ind = i;
                    isFloating = true;
                    break;
                }

            }

            recursiveFill(currentWord, index + 1, in, usedFloating, floating, results, dict);

            // if alr used ->reset the floating usage
            if (isFloating) {

                usedFloating[ind]--;

            }

            currentWord[index] = '-';
        }
    }
}