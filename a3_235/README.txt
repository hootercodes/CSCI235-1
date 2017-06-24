/***************************************************************
 * Title: README.txt
 * Author: Julian Tutuncu-Macias
 * Date Created: 5/3/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 3"
***************************************************************/

Build instructions for makefile: Using the Netbeans IDE, an automatically generated makefile compiles all of my code, distributed between these files:

	main.cpp
	dict.cpp	dict.h
	trie.cpp	trie.h

Parts complete: All portions of my code are complete.

Parts incomplete: None.

Known bugs: There are no known bugs.

Assumptions: I am assuming that no words of length greater than 100 will be inserted into the Trie. My code will not print any words with more than 100 characters upon a call to the suggest function.

Overview:
——————————————————————————————————————————————————
Trie: The Trie class is built as a tree of TrieNodes. Each TrieNode contains a boolean flag that indicates whether that TrieNode is the end of a word, and a map of chars and TrieNode pointers. The map contains the characters ‘a’ through ‘z’ in lowercase, each of which is a possible subsequent character in a word within the Trie. A TrieNode pointer is present for each character that is part of a word represented within the Trie; otherwise, the character corresponds to a nullptr. In this manner of stringing along TrieNodes as parents and children through maps, every possible string utilizing the letters ‘a’ through ‘z’ can be formed. The Trie class contains a single root TrieNode as a private member, and a variety of accessors and mutators, both as specified in the assignment instructions and additional helper functions I defined for my own use:

	TrieNode default constructor: declares the map<char, TrieNode*> m to store the pointers of all child TrieNodes with their corresponding characters, and the boolean flag to indicate whether the TrieNode is at the end of a word. For example, if the word ‘apple’ is alone represented within a Trie, the flag of the TrieNode at ’e’ is set to true, and the flags of all other TrieNodes are set to false.

	TrieNode default destructor: for each of the characters ‘a’ through ‘z’, the corresponding TrieNode pointer is erased from the map of the current TrieNode.

	Trie default constructor: sets the root TrieNode pointer to point at a new default TrieNode.

	Trie default destructor: calls the clear function to delete all TrieNode pointers in tree, and then deletes the root TrieNode pointer.

	Trie overloaded constructor: takes a file input stream as an explicit parameter: 

	Trie load: When the Trie loads from the file input stream, each line is passed as a string into the ‘insert’ function. 

	Trie insert: The characters in the explicit string parameter are parsed into the Trie, TrieNode by TrieNode. For each letter in the string, if the  next letter does not already have a corresponding TrieNode in the current TrieNode’s map, a new TrieNode is created. Once the end of the string has been reached, the last TrieNode pointer will be pointing at the last character in the word, the parent of that TrieNode pointer will be the previous character in the word, and so on.

	Trie contains: this function calls the find function (described below) and sets that function’s return value to a new TrieNode pointer. If that pointer is a nullptr, then the word is not contained within the Trie, and the program returns false. If the string being found was present within the Trie, then the TrieNode’s flag will indicate whether 

	Trie find: similar to the insert function, the find method loops through each character in the inputted string and determines whether the TrieNode pointer for each corresponding character exists. However, if the TrieNode pointer does NOT exist, the program breaks and returns false, as that word is not present within the Trie. Otherwise, it should iterate through all the characters in the inputted word, and return true once it reaches the TrieNode of the last character.

	Trie remove: if the Trie does not contain this string, it returns false; otherwise, the helper function removeHelper is called, with the string, root TrieNode, length of the string, and depth of TrieNode (initially 0).

	Trie removeHelper: this recursive function takes a string, a TrieNode pointer, the length of the string, and the depth of the TrieNode in the Trie as parameters. The boolean deletedSelf indicates whether the current TrieNode is to be deleted, and is returned upon completion of the function call. First, deletedSelf is initially set to false, and the function checks if the TrieNode passed as a parameter exists or is a nullptr (if it is a nullptr, it skips the rest of the code and returns deletedSelf as ‘false’). Otherwise, it checks if the current level is equal to the length of the string, and if so, it checks whether the TrieNode passed as a parameter has children with the hasChildren function (described below). If it does have children, we do not want to delete this TrieNode; even though it is part of the word we want to delete, it is also part of other words in the Trie that we are not deleting, and it must stay there. Furthermore, we can conclude that all TrieNodes that are parents to this TrieNode will also not be deleted. Therefore, we set the current TrieNode’s flag to false to make it no longer a word, and set deletedSelf to false. However, if the current TrieNode does not have children, the TrieNode is set to nullptr (deleted) and deletedSelf is set to true. Otherwise, if the level of the current TrieNode is not yet equal to the length of the string, removeHelper is called recursively on the child TrieNode of the current TrieNode that corresponds to the subsequent letter in the original string. The return value of that recursive call is stored in the boolean childDeleted, which indicated whether the desired child of the current TrieNode was deleted or not. If it was deleted, the TrieNode that was just accessed in the recursive call is erased from the current TrieNode’s map (making it no longer a child TrieNode) and deletedSelf is set to true only if both the currentNode is not the end of a word and if the currentNode has no children. Otherwise, deletedSelf is just set to false.

	Trie hasChildren: takes a TrieNode as a parameter, and loops through characters ‘a’ to ‘z’ in map of that TrieNode to determine whether any child TrieNodes exist; returns a boolean value if any TrieNode children are found, otherwise returns false.

	Trie clear: loops through characters ‘a’ to ‘z’ in map of root TrieNode and deletes each corresponding TrieNode.

	Trie numWords: gets the map of the root TrieNode and sets it to the map current_tree, and calls numWordsHelper on current_tree

	Trie numWordsHelper: takes a map as a parameter, and loops through the TrieNode’s corresponding to characters ‘a’ through ‘z’. For each TrieNode, if the boolean flag is true (that character is the end of a word in the Trie), the integer total is incremented. Then, the function is called recursively on the map of that TrieNode.

	Trie countNodes: gets the map of the root TrieNode and sets it to the map current_tree, and calls countHelper on current_tree

	Trie countHelper: takes a map as a parameter, and loops through the TrieNode’s corresponding to characters ‘a’ through ‘z’. For each TrieNode that is present (not a nullptr), the integer total is incremented. Then, the function is called recursively on the map of that TrieNode.

	Trie print: gets the map of the root TrieNode and sets it to the map current_tree, and calls printHelper on current_tree

	Trie printHelper: takes a map as a parameter, and loops through the TrieNode’s corresponding to characters ‘a’ through ‘z’. For each TrieNode, it prints out the character of the current TrieNode, and if the boolean flag is true (that character is the end of a word in the Trie), it prints a line end (ends). Then, the function is called recursively on the map of that character’s corresponding TrieNode.

	Trie toLower: for a string passed as a parameter, each character is converted to its lowercase version, and recombined in the order of the original string, which is then returned.
——————————————————————————————————————————————————
Dict: The Dict class acts as a wrapper class for the Trie class. It contains a single Trie as its private member, and a variety of accessors and mutators that interact with that Trie and the user interface:

	Dict default constructor: declares the Trie t.

	Dict default destructor: 

	Dict overloaded constructor: takes a file input stream as a parameter, declares the Trie t and calls load on the Dict object with said file input stream

	Dict load: takes a file input stream as a parameter, calls load on the Trie with said file input stream.

	Dict isLegalWord: calls contains on the Trie with the inputted string as a parameter.

	Dict numWords: calls numWords on the Trie.

	Dict getSubTree: passes a string vector pointer, a string prefix and a TrieNode pointer as parameters. If the TrieNode is a nullptr, the string vector is returned as is; otherwise, a map ‘tree’ is set to be the map of the passed TrieNode. If the flag of the TrieNode is true (that TrieNode is a character at the end of a word), the prefix (which should therefore contain an entire word) is pushed into the vector of strings. Then, the map is iterated through for each character ‘a’ through ‘z’. For each iteration, if the TrieNode has children, the vector of strings is reassigned to be the return value of the recursive call of getSubTree, which passes the vector as it is currently, the prefix from the original pass with the character corresponding to the current node appended to its end, and the child TrieNode. If the current TrieNode has no children, but is also the end of a word (the flag of the current TrieNode is true),  the character corresponding to the current node is appended to the end of the prefix, and that new string is pushed back into the string vector. Finally, the string vector is returned.

	Dict suggest: takes a string ‘str’ and an int ’n’ as a parameter. str dictates the prefix of all words to be generated, and n dictates the number of those prefixes  printed to the user. First creates a string vector ‘vec’ and a TrieNode pointer ‘tn’, which is set to the return value of the find function called on the Trie with str as the parameter. Then, the vector ‘vec’ is set to the return value of the getSubTree function call with the appropriate parameters. 

Now, the vector of ints ‘wordCount’ will keep track of how many words of different lengths are present in the vector of words in the subtree. For each ‘word’ in ‘vec’, the value in wordCount at the index of ‘word’s’ length is incremented by one. The vector of ints ‘cumWordCount’ will now sum the total number of possible words up to each index length. Looping through the integers 0 to 100, the value in the 0th in cumWordCount is set automatically to the value in the 0th index in wordCount, while each other index value is set to the sum of the previous index in cumWordCount and the current index in wordCount. If, at any point, the value of the current index of cumWordCount is greater than n (the total number of words we will print for the user), the cutoff for word length is set to the current index, and the int ‘toComplete’ is set to the total number of words to be printed minus the number of words that are accounted for by the previous index in cumWordCount. ‘toComplete’ will be the number of words that will be printed out of whatever number of words that would meet the cutoff in terms of character length, but would be greater in number than n were they all to be printed. Finally, if the cut off has not been changed whatsoever, it is automatically set to the maximum value (100) and toComplete is set to n since we have less than n words in the subtree. As a last step, 