/*
 * Title: trie.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 5/3/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 3"
 * Description: defines TrieNode structure and Trie class
*/

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

struct TrieNode {
  std::map<char, TrieNode*> m;
  bool flag;
  TrieNode();
  ~TrieNode();
};

class Trie {
 public:
  Trie();
  ~Trie();
  Trie(std::ifstream& stream);
  void load(std::ifstream& stream);
  bool insert(std::string str);
  bool contains(std::string str);
  TrieNode* find(std::string str);
  bool remove(std::string str);
  bool hasChildren(TrieNode* n);
  void clear();
  int numWords();
  int countNodes();
  void print();
 private:
  TrieNode *root;
  bool removeHelper(std::string str, TrieNode* n, int length, int level);
  int numWordsHelper(std::map<char, TrieNode*> tree);
  int countHelper(std::map<char, TrieNode*> tree);
  void printHelper(std::map<char, TrieNode*> tree);
  std::string toLower(std::string str);
};


#endif /* TRIE_H */

