/*
 * Title: sentence.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4"
 * Description: defines Sentence class
*/

#include "vitem.h"

class Sentence {
public:
    Sentence();
    ~Sentence();
    Sentence(VItem w[]);
    friend std::istream& operator>>(std::istream& is, Sentence& s);
    friend std::ostream& operator<<(std::ostream& os, const Sentence& s);
    Sentence translate(VItem v[]);
private:
    VItem words[10];
    VItem getVItem(int i);
};