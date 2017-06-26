/*
 * Title: vitem.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professors: William Sakas, Michael Garod
 * Purpose: "Assignment 4"
 * Description: defines VItem class
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#ifndef VITEM_H
#define VITEM_H

class VItem {
public:
     VItem();
     VItem(std::string w);
     VItem(std::string p, int s);
     VItem(std::string w, std::string p);
     VItem operator=(const VItem& rhs);
     friend std::istream& operator>>(std::istream& is, VItem& v);
     friend std::ostream& operator<<(std::ostream& os, const VItem& v);
     std::string getWord() const;
     void setWord(std::string w);
     std::string getPOS() const;
private:
    std::string findPOS(std::string w);
    std::string toLower(std::string str);
    std::string word;
    std::string pos; //POS short for Part Of Speech
};

#endif /* VITEM_H */

VItem * vocab();
