/*
 * Title: sentence.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4"
 * Description: implements all class and function definitions in sentence.h
*/

#include "sentence.h"

Sentence::Sentence() {
    VItem words[MAX_WORDS];
}

Sentence::~Sentence() {
   //delete words; 
}

/* randomly generates a sentence, with the passed boolean r determining if 
 * the sentence will be a declarative statement or a question*/
Sentence::Sentence(bool r) {
    //VItem* words;
    int i = 0;
    if (r) {
        while(rand() % 2){
            words[i] = VItem("adjective", 0);
            ++i;
        }
        words[i] = VItem("noun", 1);
        ++i;
        words[i] = VItem("verb", 0);
        ++i;
        while(rand() % 2){
            words[i] = VItem("adjective", 0);
            ++i;
        }
        words[i] = VItem("noun", 0);
        ++i;
        
    }
    else {
        words[i] = VItem("is");
        ++i;
        while(rand() % 2){
            words[i] = VItem("adjective", 0);
            ++i;
        }
        words[i] = VItem("noun", 1);
        ++i;
        words[i] = VItem("adjective", 0);
        ++i;
    }
    std::cout << *this;
    
    
}

std::istream& operator>>(std::istream& is, Sentence& s) {
    std::string word;
    VItem* words;
    int i = 0;
    while(getline(is, word, ' ')) {
       std::stringstream ss;
       ss << word;
       ss >> s.words[i];
       i++;
    }
    return is;
};

//returns Date in MM/DD/YYYY format to output stream
std::ostream& operator<<(std::ostream& os, const Sentence& s) {
    for (int i = 0; i < (sizeof(s.words)/sizeof(*s.words)); ++i) {
        //std::cout << s.words[i] << " ";
        os << s.words[i] << " ";
    }
    return os;
};

VItem Sentence::getVItem(int i) {
    return words[i];
}

Sentence Sentence::translate() {
    
    bool question = (words[0].getWord() == "is");
    bool subject = true;
    VItem temp;
    int j;
    
    for (int i = 0; i < (sizeof(words)/sizeof(*words)); ++i) {
        if(words[i].getPOS() == "noun") {
            std::string suffix;
            if (subject) {
                words[i].setWord(words[i].getWord() + "-ga");
                subject = false;
            }
            else {
                words[i].setWord(words[i].getWord() + "-o");
            }
        }
        else if (words[i].getPOS() == "adjective") {

        }
        else if (words[i].getPOS() == "verb") {
            if(question) {
                words[i].setWord(words[i].getWord() + "-ka");
            }
            temp = words[i];
            j = i;
        }
        else if (words[i].getPOS() == "article") {
            words[i].setWord("");
        }
        else {
            std::invalid_argument(words[i].getPOS() + " is not a recognized part of speech in the vocabulary.");
        }
    }
    
    
            for(; j < ((sizeof(words)/sizeof(*words))-1); ++j) {
                words[j] = words[j+1];
            }            
            words[j] = temp;
    
    
    
    return *this;
}