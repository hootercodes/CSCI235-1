/*
 * Title: corpus.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/23/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professors: William Sakas, Michael Garod
 * Purpose: "Assignment 4"
 * Description: defines Corpus class
*/

#ifndef CORPUS_H
#define CORPUS_H

#include "sentence.h"

class Corpus {
 public:
     Corpus();
     Corpus(int n);
     friend std::istream& operator>>(std::istream& is, Corpus& c);
     friend std::ostream& operator<<(std::ostream& os, const Corpus& c);
     Corpus translate(VItem v[]);
 private:
     Sentence sentences[100];
};

#endif /* CORPUS_H */

