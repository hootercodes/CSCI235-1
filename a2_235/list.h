/*
 * Title: list.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: defines structure Node and class LinkedList
*/

#ifndef LIST_H
#define LIST_H

#include "task.h"

template <class T>
struct Node {
  Node() { next_ = NULL; };
  ~Node() { delete next_; };
  Node(T* data) { data_ = data; next_ = NULL; };
  T* data_;
  Node<T>* next_;
};

template <class T>
class LinkedList {
 public:
  LinkedList();
  ~LinkedList();
  bool isEmpty(bool in);
  bool push_front(T* data);
  void detailed();
  void print(bool in);
  bool push_sorted(Task* data);
  bool remove(int n);
  Node<Task>* retreive(int n) const;
  Node<Task>* retreiveParent(int n) const;
  int getSize();
  int getIncomplete() const;
 private:
  Node<T>* head_;
  size_t size_;
};

#endif /*LIST_H*/