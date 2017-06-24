/*
 * Title: dict.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 5/3/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 3"
 * Description: implements all class and function definitions in dict.h
*/

#include "dict.h"

//initializes Trie object to default
Dict::Dict() {
    Trie t;
};

Dict::~Dict() {
}

//initializes Trie object 
Dict::Dict(std::ifstream& stream) {
    Trie t;
    this->load(stream);    
};

//calls load on Trie
void Dict::load(std::ifstream& stream) {
    t.load(stream);
};

//checks if Trie contains given word
bool Dict::isLegalWord(std::string str) {
    return t.contains(str);
};

//returns numWords call value from Trie
int Dict::numWords() {
    return t.numWords();  
};

/* returns vector of string pointers to all words contained within the subtree 
 of a given TrieNode*/
std::vector<std::string>* Dict::getSubTree(std::vector<std::string>* wordList, std::string prefix, TrieNode* tn){
    if (tn == nullptr) {
        return wordList;
    }
    
    std::map<char, TrieNode*> tree = tn->m;
    if (tn->flag){
        wordList->push_back(prefix);
    }  
    for (std::map<char, TrieNode*>::iterator it = tree.begin(); it!=tree.end(); ++it) 
    {   
        if (t.hasChildren(it->second)) {
            wordList = getSubTree(wordList, prefix + it->first, it->second);
        }
        else if (it->second->flag) {
            std::string word = prefix + it->first;
            wordList->push_back(word);
        }
    }
    return wordList;
}

/* central function of code: returns a string pointer vector of n possible words 
   including the prefix str, sorted by word length and then alphabetized
 * first gets string pointer vector of subtree with getSubtree function
 * then, it sorts each word in subtree vector by word length, then alphabetical
 * finally, feeds in only n of the sorted words into the outputted vector */
std::vector<std::string>* Dict::suggest(std::string str, int n) {
    std::vector<std::string>* vec = new std::vector<std::string>(0);
    
    TrieNode* tn;
    tn = t.find(str); 

    vec = getSubTree(vec, str, tn);

    std::vector<int> *wordCount = new std::vector<int>(100);
    for (int i=0; i< vec->size(); i++) {
        std::string word = vec->at(i);
        
        wordCount->at(word.length())++;
    }
    std::vector<int> *cumWordCount = new std::vector<int>(100);
    int cutoff = 0;
    int toComplete = 0;
    
    for (int i=0; i<100; i++) {
        if (i==0) {
            cumWordCount->at(i) = (*wordCount)[i];
        }
        else {
            cumWordCount->at(i) = (*cumWordCount)[i-1] + (*wordCount)[i];
        }
        if ((cumWordCount->at(i) > n) && (cutoff == 0) )
        {
            cutoff = i;
            toComplete = n - cumWordCount->at(i-1);
        }
    }
    if (cutoff == 0) {
        cutoff = 100;
        toComplete = n;
    }
    
    std::vector<std::string>* suggestWords = new std::vector<std::string>(0);
    for (int l=str.length(); l<cutoff+1; l++){
       for (int i=0; i< vec->size(); i++) 
       {
            std::string word = vec->at(i);
            if (word.length() == l )
            {
                if ((l<cutoff) || ( (l==cutoff) && (toComplete>0) ) )
                {    
                    suggestWords->push_back(word);
                    std::cout << word << std::endl;
                    if (l == cutoff) 
                    {
                        toComplete --;
                    }
                }
            }
        }
    }
       return suggestWords;      
}