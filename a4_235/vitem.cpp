/*
 * Title: vitem.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4"
 * Description: implements all class and function definitions in vitem.h
*/

#include "vitem.h"

//declares 'word' and 'pos' strings
VItem::VItem() {
    word = "default";
    pos = "default";
}

//deletes 'word' and 'pos' strings
VItem::~VItem() {
	//delete word;
	//delete pos;
}

//takes a word w as a parameter, then finds Part of Speech
VItem::VItem(std::string w) {
    word = w;
}

//takes a word w and a Part Of Speech p as parameters
VItem::VItem(std::string w, std::string p) {
    word = w;
    pos = p;
}

// takes in word from input stream, then finds Part of Speech
std::istream& operator>>(std::istream &is, VItem& v) {
   std::string temp;
   //getline(is, temp);
   is >> temp;
   std::cout << temp << std::endl;
   //std::cout << v.word << std::endl;
    //std::cout << v.pos << std::endl;
    
    v.word = temp;
    //v.pos = v.findPOS(v.word);*/
  //is >> v.word >> v.pos;
  return is;
};

//returns word to output stream
std::ostream& operator<<(std::ostream& os, const VItem& v) {
    //os << v.word << " (" << v.pos << ")";
    return os;
};

std::string VItem::getWord() {
    return word;
}

void VItem::setWord(std::string w) {
    word = w;
}

std::string VItem::getPOS() {
    return pos;
}

//determines the Part Of Speech that string 'w' is, returns that as a string
std::string VItem::findPOS(std::string w) {   
    std::string p;
    VItem * vocabu;
    vocabu = vocab();
    //std::cout << sizeof(*vocabu) << std::endl;
    for (int i = 0; i < sizeof(*vocabu); ++i) {
        //std::cout << (vocabu+i)->word << (vocabu+i)->pos << std::endl;
    	if (this->toLower(w) == (vocabu+i)->word) {
            p = (vocabu+i)->pos;
            break;
        }
    }
    if (p == "") {
        std::invalid_argument(w + " is not a recognized part of speech in the vocabulary.");
    }
    pos = p;
    return pos;
}


/* converts every inputted string to lowercase so as to simplify Trie building 
and function calls with explicit parameters (insert, contains, find, etc.) */
std::string VItem::toLower(std::string str) {
    int i = 0;
    char c;
  while (str[i])
  {
    c=str[i];
    str[i] = tolower(c);
    i++;
  }
    std::cout << str << std::endl;
    return str;
}

//creates an array of VItems to make up a dictionary; returns array as pointer
VItem * vocab() {
    static VItem vocab[11];
    vocab[0] = VItem("man", "noun");
    vocab[1] = VItem("woman", "noun");
    vocab[2] = VItem("fish", "noun");
    vocab[3] = VItem("strong", "adjective");
    vocab[4] = VItem("short", "adjective");
    //std::cout << sizeof(vocab)/sizeof(vocab[0]) << std::endl;
    vocab[5] = VItem("red", "adjective");
    vocab[6] = VItem("caught", "verb");
    vocab[7] = VItem("kissed", "verb");
    vocab[8] = VItem("is", "verb");
    vocab[9] = VItem("a", "article");
    vocab[10] = VItem("the", "article");
    //std::cout << sizeof(vocab)/sizeof(vocab[0]) << std::endl;
    return vocab;
};

