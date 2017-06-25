/*
 * Title: main.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4"
 * Description: creates 100 sentences in Eng--, translates each of them to Eng++
*/

#include "corpus.h"

Corpus translate (Corpus c, VItem v[]);

/*
 * 
 */
int main(int argc, char** argv) {
    
    srand (time(NULL));

    Corpus eng; //eng--
    Corpus ENG; //eng++
    
    std::ifstream is;
    is.open("eng--.txt");
    std::ofstream os;
    os.open("eng++.txt");
    
    is >> eng;
    ENG = translate(eng, vocab());
    os << ENG;
    /*
    Corpus rando(100);
    Corpus randi;
    
    std::ofstream randos;
    randos.open("randin.txt");
    randos << rando;
    
    std::ifstream randis;
    randis.open("randin.txt");
    randis >> randi;
    
    randi = translate(randi, vocab());
    os << randi << std::endl;
    */
    is.close();
    os.close();
     
    return 0;
};


Corpus translate (Corpus c, VItem v[]) {
    c.translate(v);
    return c;
}