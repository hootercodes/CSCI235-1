/*
 * Title: sentence.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professors: William Sakas, Michael Garod
 * Purpose: "Assignment 4"
 * Description: defines Sentence class
*/

#include "vitem.h"

const int MAX_WORDS = 100;

class Sentence {
public:
    Sentence();
    Sentence(bool r);
    friend std::istream& operator>>(std::istream& is, Sentence& s);
    friend std::ostream& operator<<(std::ostream& os, const Sentence& s);
    Sentence translate();
private:
    VItem words[MAX_WORDS];
    int length;
};
