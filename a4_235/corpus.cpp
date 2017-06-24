/*
 * Title: corpus.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/23/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4"
 * Description: implements all class and function definitions in corpus.h
*/

#include "corpus.h"

Corpus::Corpus() {
    Sentence sentences[10];
}

Corpus::~Corpus() {
    //delete sentences;
}

Corpus::Corpus(std::istream& is) {
    is >> *this;
}


std::istream& operator>>(std::istream& is, Corpus& c) {
    std::string temp;
    int i = 0;
    while(getline(is, temp)){
        std::stringstream ss;
        ss << temp;
        ss >> c.sentences[i];
        std::cout << c.sentences[i] << std::endl;
        i++;
    }
    return is;
};

//returns Date in MM/DD/YYYY format to output stream
std::ostream& operator<<(std::ostream& os, const Corpus& c) {
  for (int i = 0; i < (sizeof(c.sentences)/sizeof(*c.sentences)); ++i) {
  	os << c.sentences[i] << std::endl;
  }
  return os;
};

Corpus Corpus::translate(VItem v[]) {
    for (int i = 0; i < (sizeof(sentences)/sizeof(*sentences)); ++i) {
  	sentences[i].translate(v);
    }
    return *this; 
}