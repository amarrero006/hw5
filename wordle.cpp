#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#include <vector>

#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

bool isWord(const string& word, const set<string>& dict);
void makeCombo(string word,  int n, int pos, string& letters, const set<string>& dict, set<string>& results);
void getPermutations(string& word, int n, int x, vector<char>& floatingChars, string& current, int currentIndex, int floatIndex, const set<string>& dict, set<string>& results);

// Definition of primary wordle function

set<string> wordle( const std::string& in, const std::string& floating, const std::set<std::string>& dict){
    // Add your code here
    
    std::set<std::string> results;
    vector<string> perms;
    int n = in.length();
    string fixedWord = in;
    int pos = 0;
    int x = (int) floating.length();
    vector<char> floatingChars;
    for(char c:floating){
      floatingChars.push_back(c);
    }
    string current(n, '-');
    getPermutations(fixedWord, n, x, floatingChars, current, 0,0, dict, results);

    return results;
   
}

// Define any helper functions here


void getPermutations(string& word,  int n,  int x,  vector<char>& floatingChars, string& current, int currentIndex, int floatIndex, const set<string>& dict, set<string>& results){
  if (currentIndex == n) {
        // Check if all floating letters are present in the current permutation
        bool flag = true;
        int count;
        for (char floatingChar : floatingChars) {
            int countfloat = std::count(floatingChars.begin(), floatingChars.end(), floatingChar) + std::count(word.begin(), word.end(), floatingChar) ;
            int countWord = std::count(current.begin(), current.end(), floatingChar);
            if (countfloat != countWord) {
                flag = false;
                break;
            }
        }
    if(flag){
      string canidate(n, '-');
      makeCombo(canidate, n, 0, current, dict, results);
    }
    return;
    }

    if(word[currentIndex] == '-'){
      if(floatIndex < x){
        for(int i = 0; i < floatingChars.size(); i++){
          current[currentIndex] = floatingChars[i]; 
          getPermutations(word, n, x, floatingChars, current, currentIndex +1, floatIndex + 1, dict, results);
        }
        current[currentIndex] = '-';
      }
      getPermutations(word, n, x, floatingChars, current, currentIndex +1, floatIndex, dict, results);
    }

    else{
      current[currentIndex] = word[currentIndex];
      getPermutations(word, n, x, floatingChars, current, currentIndex +1, floatIndex, dict, results);
    }

}


bool isWord(const string& word, const set<string>&dict, set<string>& results){
  return ( dict.find(word) != dict.end() && (results.find(word) == results.end()));
}

void makeCombo(string word, int n, int pos, string& fixed, const set<string>& dict, set<string>& results){
    if(pos == fixed.length()){
      if(isWord(word, dict, results)){  
          results.insert(word);
      }
        return;
    }

    if(fixed[pos] != '-'){
      word[pos] = fixed[pos];
      makeCombo(word, n, pos+1, fixed, dict, results);
      word[pos] = '-';
    }

    else{
      for(char c = 'a'; c <= 'z'; c++){
        word[pos] = c;
        makeCombo(word, n, pos+1, fixed, dict, results);
        word[pos] = '-';
      }
    }

  
}
