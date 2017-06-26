/*
 * Title: main.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professors: William Sakas, Michael Garod
 * Purpose: "Assignment 4"
 * Description: creates 100 sentences in Eng--, translates each of them to Eng++
*/

#include "corpus.h"

Corpus translate (Corpus c, VItem v[]);

/*
 * 
 */
int main(int argc, char** argv) {
    
    srand (time(NULL)); //resets seed of random generator
    
    std::ofstream eng_mm;
    eng_mm.open("eng--.txt");
    std::ofstream eng_pp;
    eng_pp.open("eng++.txt");
    
    Corpus random_eng_mm(100); //100 randomly generated Eng-- sentences
    Corpus random_eng_pp; //empty Eng++ Corpus
    random_eng_pp = translate(random_eng_mm, vocab()); //translates Eng-- to Eng++
    eng_mm << random_eng_mm;
    std::cout << "eng--.txt has been created." << std::endl;
    eng_pp << random_eng_pp;
    std::cout << "eng++.txt has been created." << std::endl;
    
    eng_mm.close();
    eng_pp.close();
     
    return 0;
};

//calls translate on the passed corpus value
Corpus translate (Corpus c, VItem v[]) {
    c.translate(v);
    return c;
}
