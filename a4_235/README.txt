/***************************************************************
 * Title: README.txt
 * Author: Julian Tutuncu-Macias
 * Date Created: 6/23/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 4”
***************************************************************/

Build instructions for makefile: Using the Netbeans IDE, an automatically generated makefile compiles all of my code, distributed between these files:

	main.cpp
	corpus.cpp	corpus.h
	sentence.cpp	sentence.h
	vitem.cpp	vitem.h

Parts complete: All portions of my code are complete.

Parts incomplete: None.

Known bugs: There are no known bugs.

Assumptions: I am assuming that no sentences of word length greater than 100 will be generated, and no Corpuses will contain more than 100 sentences. 

Overview:
——————————————————————————————————————————————————
VItem: the VItem class stores two private members, a string containing the word itself (‘word’) and a string containing the Part of Speech (‘pos’) that word is. In the Eng—- language, for example:

	man	noun
	woman	noun
	fish	noun
	strong	adjective
	short	adjective
	red	adjective
	caught	verb
	kissed	verb
    	is	verb
	a	article
	the	article

There are a number of overloaded constructors and operators, as well as some public and private helper methods:

	VItem default constructor: declares the ‘word’ and ‘pos’ to be empty strings.

	VItem overloaded constructor (string w): takes a single string ‘w’ as a parameter and sets ‘word’ equal to it, then calls findPOS(defined below) on that ‘w’.
	
	VItem overloaded constructor (string p, int s): sets the object to be a randomly selected VItem of the Part of Speech defined by the parameter ‘p’. It first creates a temporary array of VItems called ‘options’ to store all the possible words that are the same Part of Speech as ‘p’. After looping through the vocabulary and pulling every matching word and putting it into ‘options’, it randomly selects a VItem from ‘options’ and sets the current object to that object. The int s is not used, it is in the definition solely to distinguish it from the previously defined constructor.

	VItem overloaded constructor (string w, string p): takes two strings, ‘w’ and ‘p’, and sets ‘word’ and ‘pos’ equal to them respectively.

	VItem overloaded operator =: copies over the ‘word’ and ‘pos’ values from the right hand side VItem.

	VItem overloaded operator >>: calls getline on the input stream, storing the word in ‘temp’. It then sets ‘word’ to be equal to ‘temp’ and then calls findPOS(defined below) on ‘temp’.

	VItem overloaded operator <<: returns ‘word’ to the output stream.

	VItem getWord: returns ‘word’.

	VItem setWord: taking a string ‘w’ as a parameter, it sets ‘word’ to be equal to ‘w’.

	VItem getPOS: returns ‘pos’.

	VItem findPOS: this function takes a string ‘w’ as a parameter, and searches through the vocabulary to find the Part of Speech the word ‘w’ is. If ‘w’ is not in the vocabulary, an error is thrown. Otherwise, the ‘pos’ of the current object is set to the ‘pos’ of the VItem corresponding to ‘w’, and ‘pos’ is returned.

	VItem toLower: for a string passed as a parameter, each character is converted to its lowercase version, and recombined in the order of the original string, which is then returned.

	(non-member function) vocab: creates an array of VItems, and manually populates it with the words defined in the Eng—- language.
——————————————————————————————————————————————————
Sentence: the sentence class contains an array of MAX_WORDS (100) VItem objects (‘words’), as well as a integer ‘length’. It contains overloaded operators and a public helper method:

	Sentence default constructor: initializes a VItem array ‘words’ with a size of MAX_WORDS and sets length to 0.

	Sentence overloaded constructor: taking a boolean ‘r’ as a parameter, this constructor creates a randomly generated sentence following the rules of the Eng—- language. If the boolean ‘r’ is true, the constructor will create a declarative statement; if it is false, it will create a question. 

		If creating a statement: first, a randomly selected article is randomly decided to be placed before the subject, and a random number of randomly selected adjectives proceed the subject. Then, a noun and a verb are randomly selected. If the verb selected was ‘is’, a single adjective is randomly selected to complete the sentence. If not, a randomly selected article is randomly included (or not), some random number of adjectives is randomly generated, and an object is randomly selected.

		If creating a question: first, the word “is” is inserted, followed possibly by a randomly selected article, a random number of randomly selected adjectives, and a random subject. Finally, there is a single randomly selected adjective.
	
	Sentence overloaded operator >>: while getline can be called on the input stream with ‘ ‘ as a delimiter, the input is stored in ‘word’. It then streams ‘word’ through a stringstream into each index in the ‘words’ array, incrementing the index each time.

	Sentence overloaded operator <<: for each item in the ‘words’ array, the VItem is returned to the output stream.

	Sentence translate: this function translates some Sentence object from Eng— to Eng++. First, it is determined whether the sentence is a question by checking if the first word in the sentence is “is”. Then, a boolean ‘subject’, which indicates whether the subject of the sentence has yet to be processed, is created. Then, the initial loop goes through every word in the Sentence, and looks at the Part of Speech of each word and translates accordingly. If it is a noun, it first checks if the subject has been processed yet: if not, it appends “-ga”; if it has, it appends “-o” (because the current noun is the object, not the subject). If it is an adjective, nothing is done. If it is a verb, it checks whether the current sentence is a question: if it is, it appends “-ka”; otherwise, it does nothing. Then, the index within the ‘words’ array for the verb and the VItem itself are stored into the integer j and the VItem temp, respectively. If the current word is an article, it is replaced by an empty string. Otherwise, an exception is thrown for the word being an invalid argument. The second loop is run to move the verb to the end of the sentence. Starting at index j, it shifts every word in the array backward an index in order to insert the verb, stored in the VItem ‘temp’, at the very end. Finally, the Sentence object is returned.
——————————————————————————————————————————————————
Corpus: the Corpus class contains an array of 100 Sentence objects (‘sentences’). It contains overloaded operators and helper methods:

	Corpus default constructor: initializes a Sentence array ‘sentences’ with size 100

	Corpus overloaded constructor: taking an int ’n’ as a parameter, the ‘sentences’ array is filled with n randomly generated sentences, which take either 1 or 0 as parameters, indicating whether the sentence is declarative or not. 

	Corpus overloaded operator >>: while getline can be called on the input stream, the input is stored in the string ‘temp’. It then streams ‘temp’ through a stringstream into each index in the ‘sentences’ array, incrementing the index each time.

	Corpus overloaded operator <<: for each item in the ‘sentences’ array, the Sentence is returned to the output stream.

	Corpus translate: taking a VItem array ‘v’ as the vocabulary, this function loops through the ‘sentences’ array and translates each one.