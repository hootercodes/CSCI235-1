/*
 * Title: sentence.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/22/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professors: William Sakas, Michael Garod
 * Purpose: "Assignment 4"
 * Description: implements all class and function definitions in sentence.h
*/

#include "sentence.h"

//declares VItem array, sets length to 0
Sentence::Sentence() {
    VItem words[MAX_WORDS];
    length = 0;
}

/* randomly generates a sentence according to the rules of 'Eng--', with the 
 * passed boolean r determining if the sentence will be a declarative statement
 * or a question*/
Sentence::Sentence(bool r) {
    int i = 0;
    if (r) { //will produce a declarative statement

        if(rand()%2){ //may or may not add an article
            words[i] = VItem("article", 0);
            ++i;
        }
        while(rand() % 2){ //adds a random number of adjectives
            words[i] = VItem("adjective", 0);
            ++i;
        }
        words[i] = VItem("noun", 1); //adds a noun
        ++i;
        words[i] = VItem("verb", 0); //adds a verb
        ++i;
        if(words[i-1].getWord() == "is") { //checks if the verb just made was "is"
           words[i] = VItem("adjective", 0); //adds a single adjective
           ++i;
        }
        else {
           if(rand()%2){ //may or may not add an article
               words[i] = VItem("article", 0);
               ++i;
           }
           while(rand() % 2){
                words[i] = VItem("adjective", 0);
                ++i;
            }
            words[i] = VItem("noun", 0);
            ++i;
        }        
    }
    else {
        words[i] = VItem("is");
        ++i;
        if(rand()%2){
            words[i] = VItem("article", 0);
            ++i;
        }
        while(rand() % 2){
            words[i] = VItem("adjective", 0);
            ++i;
        }
        words[i] = VItem("noun", 1);
        ++i;
        words[i] = VItem("adjective", 0);
        ++i;
    } 
    length = i;
}

//puts each word from stream into a new VItem in the 'words' array
std::istream& operator>>(std::istream& is, Sentence& s) {
    std::string word;
    int i = 0;
    while(getline(is, word, ' ')) {
       std::stringstream ss;
       ss << word;
       ss >> s.words[i];
       i++;
    }
    s.length = i;
    return is;
};

//returns each word that is not an empty string to output stream
std::ostream& operator<<(std::ostream& os, const Sentence& s) {
    for (int i = 0; i < s.length; ++i) {
        if(s.words[i].getWord() != "") {
            os << s.words[i] << " ";
        }
    }
    return os;
};

//translates the sentence from Eng-- to Eng++
Sentence Sentence::translate() {
    
    bool question = (words[0].getWord() == "is");/* determines whether sentence 
                                                  * is a declarative statement 
                                                  *  a question */
    bool subject = true;
    VItem temp;
    int j;
    
    for (int i = 0; i < length; ++i) {//checks Part of Speech of each word and translates accordingly
        if(words[i].getPOS() == "noun") {
            std::string suffix;
            if (subject) { //checks if subject of sentence has already been translated
                words[i].setWord(words[i].getWord() + "-ga");
                subject = false;
            }
            else {
                words[i].setWord(words[i].getWord() + "-o");
            }
        }
        else if (words[i].getPOS() == "adjective") {
            //does nothing
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
    
    //moves verb to end of sentence
    for(; j < length-1; ++j) {
        words[j] = words[j+1];
    }
    words[j] = temp;
    
    return *this;
}
