#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set> 
#endif

#include "wordle.h"
#include "dict-eng.h"
#include <string>
using namespace std;


// Add prototypes of helper functions here
set<string> findstring(string in, string floating, int n, int count);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int counter = 0;

    for(int i = 0; i < (int)in.length(); i++){
        if(in[i] == '-'){
            counter++;
        }
    }
    set<string> tempset = findstring(in,floating, 0, counter);
    set<string> finalset;


    for(set<string>::iterator it = tempset.begin(); it != tempset.end(); ++it){
        if(dict.find(*it) != dict.end()){
            finalset.insert(*it);
        }
    }
    return finalset;
}

set<string> findstring(string in, string floating, int n, int count){
    if(n == (int)in.length()){
        set<string> temp = {in};
        return temp;
    }
    set<string> finalanswer;
    if(in[n] == '-'){
        for(int i = 0; i < (int)floating.length(); i++){
            in[n] = floating[i];
            string tempfloat = floating.substr(0,i) + floating.substr(i+1);
            set <string> temp = findstring(in, tempfloat, n + 1, count - 1);
            finalanswer.insert(temp.begin(), temp.end());

            in[n] = '-';
        }
        if((int)floating.length() < count){
            for(int i = 0; i < 26; i++){
                in[n] = (char)(i + 97);
                set<string> temp = findstring(in, floating, n + 1, count - 1);
                finalanswer.insert(temp.begin(), temp.end());

                in[n] ='-';
            }
        }
    }else {
        set<string>temp = findstring(in,floating,n+1, count);
        finalanswer.insert(temp.begin(), temp.end());
    }
    return finalanswer;
}
// Define any helper functions here
