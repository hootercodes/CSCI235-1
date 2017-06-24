/*
 * Title: trie.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 5/3/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 3"
 * Description: implements all structure, class and function definitions in trie.h
*/

#include "trie.h"
#include <unistd.h>
#include <sstream>

//constructor: initializes generic TrieNode, sets 'flag' to false
TrieNode::TrieNode() {
    std::map<char, TrieNode*> m;
    bool flag = false;
};

//destructor: deletes all nodes in map
TrieNode::~TrieNode() {
  for(char c = 'a';c <= 'z'; c++) {
     m.erase(c);
  }
};

//constructor: initializes the Trie, sets root node to an empty TrieNode
Trie::Trie() {
  root = new TrieNode;
};

//destructor: clears Trie of all TrieNodes, then deletes root TrieNode
Trie::~Trie() {
  this->clear();
  delete root;
}

//constructor overload: takes file input stream and loads it
Trie::Trie(std::ifstream& stream) {
    root = new TrieNode;
    load(stream);
};

//loads from file input stream; inserts each line in the file into the Trie
void Trie::load(std::ifstream& stream) {
  std::string in;
  while(getline(stream, in)){
      insert(in);
  }
}

/* inserts string into Trie
 * converts string to lower case, checks if string is already present 
   (returns false if it is and does not modify Trie)
 * iterating through each character in the string, it checks if a node 
   for that character has already been created in the map; 
   if it hasn't, a new node is created
 * once the last character of the string being inserted is reached, the flag 
   of that TrieNode is set to true indicating that the node is the 
   end of a legal word */
bool Trie::insert(std::string str) {
    TrieNode *temp = root;
    
    str = toLower(str);
    if (contains(str)) {
        return false;
    }
    for(int i = 0; i < str.length(); i++){
            char c = str[i];
        if( (temp->m.count(c)) == 0){
            
            temp->m[c] = new TrieNode;
        }
        temp = temp->m[str[i]];
    }
    //cout << endl;
    temp->flag = true;
    return true;
    
}

//checks if a string is already mapped within the Trie
bool Trie::contains(std::string str) {
    TrieNode* n = find(str);
    return (n != nullptr) && (n->flag);
}

/*returns TrieNode pointer to last character in 'str' if it is within the Trie
 * for each char in string, moves to subsequent char in string if present in the 
   current TrieNode's map; if not present, returns nullptr */
TrieNode* Trie::find(std::string str) {
    
    TrieNode* cur = root;
    std::map<char,TrieNode*>::iterator it;
 
    for (int i = 0; i < str.length(); i++) {
        it = cur->m.find(str[i]);
        if (it != cur->m.end()) {
            cur = cur->m[str[i]];
        }
        else return nullptr;
    }
    return cur;      
}

//checks if a string is present, if it is calls removeHelper
bool Trie::remove(std::string str) {
    if (!contains(str)) {
        return false;
    }
    return removeHelper(str, root, str.length(), 0);
}

/*traces through word, deletes any nodes in Trie that are both in the 
  given string and not in any other string in the Trie*/
bool Trie::removeHelper(std::string str, TrieNode* n, int length, int level) {
    bool deletedSelf = false;
    if (n) {
        if (length == level) {
            if (hasChildren(n)) {
                /* other words contain str, so do not delete 
                 * anything, just update flag*/
                n->flag = false;
                deletedSelf = false;
            }
            else {
                /* reached end of word, no children, so node needs to
                 be deleted. Set deletedSelf to true. Actual deletion of
                 the node happens in the recursive call from the parent 
                 node */
                n = nullptr;
                deletedSelf = true;
            }
        }
        else
        {
            // recursive call to the next level
            bool childDeleted = removeHelper(str, n->m[str[level]], length, level+1);
            if (childDeleted)
            {
                /* delete child node and determine whether the current node
                   needs to be deleted as well*/
                n->m.erase(str[level]);    
                deletedSelf = (!n->flag && !hasChildren(n));
            }
            else
            {
                deletedSelf = false;
            }        
        }
    }    
    return deletedSelf;
}

//determines whether any child TrieNodes are present in map of some TrieNode
bool Trie::hasChildren(TrieNode *n) {
    for(char c = 'a'; c <= 'z'; c++) {
        if( (n->m.count(c)) != 0){  
            return true;
        }
    }
    return false;
}

//deletes all nodes in root node's map
void Trie::clear() {
    for(char c = 'a';c <= 'z'; c++) {
        root->m.erase(c);
    }
}

//calls numWordsHelper on map of root node to count total number of words in Trie
int Trie::numWords() {
    std::map<char, TrieNode*> current_tree = root->m;
    return numWordsHelper(current_tree);
}

/* Takes map as parameter
 * if the child map is empty, return 0; otherwise:
 * for each TrieNode in map, calls itself on subsequent map, adding that value to sum total*/
int Trie::numWordsHelper(std::map<char, TrieNode*> tree) {   
      int total = 0;
    if (tree.empty()) {
        return 0;
    }

    for (std::map<char, TrieNode*>::iterator it=tree.begin(); it!=tree.end(); ++it) {
        if (it->second->flag) {
            total ++;
        }
        total += numWordsHelper(it->second->m);
    }
    return total;
}

//calls countHelper on map of root node to count total number of TrieNodes in Trie
int Trie::countNodes() {
    std::map<char, TrieNode*> current_tree = root->m;
    return countHelper(current_tree);
}

/* Takes map as parameter
 * if the child map is empty, return 0; otherwise:
 * for each TrieNode in map, calls itself on subsequent map, adding that value to sum total*/
int Trie::countHelper(std::map<char, TrieNode*> tree) {
    int total = 0;
    if (tree.empty()) {
        return 0;
    }

    for (std::map<char, TrieNode*>::iterator it=tree.begin(); it!=tree.end(); ++it) {
        total ++;
        total += countHelper(it->second->m);
    }
    return total;
}

//calls printHelper on map of root node to print every word in Trie
void Trie::print() {
  std::map<char, TrieNode*> current_tree = root->m;
  printHelper(current_tree);
}


/* Takes map as parameter
 * if the child map is empty, return 0; otherwise:
 * for each TrieNode in map, calls itself on subsequent map*/
void Trie::printHelper(std::map<char, TrieNode*> tree) {
  if (tree.empty()) {
    return;
  }

  for (std::map<char, TrieNode*>::iterator it=tree.begin(); it!=tree.end(); ++it) {
      std::cout << it->first;
    if(it->second->flag){
        std::cout << std::endl;
    }
    printHelper(it->second->m);
  }
}

/* converts every inputted string to lowercase so as to simplify Trie building 
and function calls with explicit parameters (insert, contains, find, etc.) */
std::string Trie::toLower(std::string str) {
    int i = 0;
    char c;
  while (str[i])
  {
    c=str[i];
    str[i] = tolower(c);
    i++;
  }
    return str;
}