/*
 * Title: dict.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 5/3/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 3"
 * Description: defines Dict class
*/

#ifndef DICT_H
#define DICT_H

#include "trie.h"

class Dict {
public:  
     Dict();
     ~Dict();
     Dict(std::ifstream& stream);
     void load(std::ifstream& stream);
     bool isLegalWord(std::string str);
     int numWords();
     std::vector<std::string>* suggest(std::string str, int n);
private:  
    Trie t;
    std::vector<std::string>* getSubTree(std::vector<std::string>* wordList, std::string prefix, TrieNode* n);
};


#endif /*DICT_H*/

