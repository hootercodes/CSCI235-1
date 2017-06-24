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
    VItem words[10];
}

Sentence::~Sentence() {
   //delete words; 
}

Sentence::Sentence(VItem w[]) {
    for(int i = 0; i < (sizeof(w)/sizeof(w[0])); ++i) {
        words[i] = w[i];
    }
}

std::istream& operator>>(std::istream& is, Sentence& s) {
    std::string word;
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
    //std::cout << (sizeof(s.words)/sizeof(*s.words)) << std::endl;
    for (int i = 0; i < (sizeof(s.words)/sizeof(*s.words)); ++i) {
        os << s.words[i];
        os << " ";
    }
    return os;
};

VItem Sentence::getVItem(int i) {
    return words[i];
}

Sentence Sentence::translate(VItem v[]) {
    for (int i = 0; i < (sizeof(words)/sizeof(*words)); ++i) {
  	for(int j = 0; j < (sizeof(v)/sizeof(*v)); ++j) {
            if (words[i].getPOS() == v[j].getPOS()) {
                if(words[i].getPOS() == "noun") {

                }
                else if (words[i].getPOS() == "adjective") {

                }
                else if (words[i].getPOS() == "verb") {
                    words[i].setWord(words[i].getWord() + "-ka");
                }
                else if (words[i].getPOS() == "article") {

                }
                else {
                    std::invalid_argument(words[i].getPOS() + " is not a recognized part of speech in the vocabulary.");
                }
            }
        }
    }
    
    return *this;
}