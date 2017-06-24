/*
 * Title: list.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: implements all class, structure and function definitions given in list.h
*/

#include "list.h"

//constructor: sets head node to null and size to 0
template <>
LinkedList<Task>::LinkedList() {
    head_ = NULL;
    size_ = 0; 
}

//destructor: deletes root node of LinkedList
template <class T>
LinkedList<T>::~LinkedList() {
 delete head_;   
}

//returns actual size of LinkedList
template <class T>
int LinkedList<T>::getSize() {
    return size_;
};

//attaches a new task to the front of the LinkedList
template <class T>
bool LinkedList<T>::push_front(T* data) {
    Node<T>* node = new Node<T>(data);
    node->next_ = head_;
    head_ = node;
    ++size_;
    return true;
};

// returns whether there are any incomplete or complete tasks in LinkedList
template <>
bool LinkedList<Task>::isEmpty(bool in) {
    if (size_ == 0) {
        return true;
    } else {
        int counter = 0;
        for (Node<Task>* p = head_; p != NULL; p = p-> next_) {
            if(in == p->data_->isCompleted()) {
                counter++;
            }
        }
        return (counter == 0);
    }
};

//for each incomplete Task in LinkedList, prints detailed description of task
template<>
void LinkedList<Task>::detailed() {
    int counter = 1;
    for (Node<Task>* p = head_; p != NULL; p = p-> next_) {
      if(!p->data_->isCompleted()) {
	std::cout << counter << ". " << p->data_->detailedList() << std::endl;
	if(p->next_ != NULL) {
            counter++;
	}
      }
    }
};

/* prints basic description of all tasks marked either complete or incomplete, 
   boolean parameter 'in' indicates which (false = incomplete, true = complete)*/
template <>
void LinkedList<Task>::print(bool in) {
    int counter = 1;
    for (Node<Task>* p = head_; p != NULL; p = p-> next_) {
      if(in == p->data_->isCompleted()) {
	std::cout << counter << ". " << p->data_->basicList() << std::endl;
        counter++;
      }
    }
};

/* pushes a new Task into the sorted (by date) index in LinkedList
 * first checks if list is empty; if so, calls push_front
 * otherwise, loops through task list until the date of the Task being added 
   is less than the next Task in the LinkedList */
template <>
bool LinkedList<Task>::push_sorted(Task* data) {
    Node<Task>*p = new Node<Task>;
    p->next_ = NULL;
    p->data_ = data;

    if (head_ == NULL) {
        push_front(data);
      return true;
    } else {
        Node<Task>* q = head_;
        Node<Task>* r = NULL;
        for (; p->data_->getDate() > q->data_->getDate(); q = q->next_) {
            r = q;
            if(q->next_ == NULL){
                q->next_ = p;
                ++size_;
                return true;
            }
        }
        p->next_ = q;
        if (r == NULL) {
            head_ = p;
            ++size_;
            return true;
        }
        r->next_ = p;
        ++size_;
        std::cout << "Task added successfully" << std::endl;
        return true;
    }
};


//returns number of not complete tasks within LinkedList
template <>
int LinkedList<Task>::getIncomplete() const {
   int counter = 0;
    for (Node<Task>* p = head_; p != NULL; p = p-> next_) {
      if(!p->data_->isCompleted()) {
          counter++;
      }
    }
   return counter;
};

//gets the node at the nth index, taking into account completed tasks
template <>
Node<Task>* LinkedList<Task>::retreive(int n) const {
    if ((n > getIncomplete()) || (n <= 0)){
      throw std::invalid_argument("Cannot return value at non-existent index");
    }
    Node<Task>* p = head_;
    while(p->data_->isCompleted()){
            p = p->next_;
    }
    
    for (int i = 1; i < n; ++i) {
        p = p->next_;
        while(p->data_->isCompleted()){
            p = p->next_;
        }
    }
    return p;
};

/* gets the node immediately before the node at the nth index, 
   taking into account completed tasks */
template <>
Node<Task>* LinkedList<Task>::retreiveParent(int n) const {
    if ((n > getIncomplete()) || (n <= 0)){
      throw std::invalid_argument("Cannot return value at non-existent index");
    }
    Node<Task>* p = head_;
    Node<Task>* parent = NULL;
    
    while(p->data_->isCompleted()){
            parent = p;
            p = p->next_;
    }
    
    for (int i = 1; i < n; ++i) {
        parent = p;
        p = p->next_;
        while(p->data_->isCompleted()){
            parent = p;
            p = p->next_;
        }
    }
    return parent;
};

/* removes the indexed Task from LinkedList, taking into account completed tasks
 * first checks if list is empty; if so, returns false
 * otherwise, loops through task list, checking if each node is incomplete,
   until the nth incomplete task is reached; then, it is deleted */
template <>
bool LinkedList<Task>::remove(int n) {
    if (head_ == NULL) {
        return false;
    }
    else {
        if(n == 1) {
            Node<Task> *p = retreive(1);
            Node<Task> *q = retreiveParent(1);
            if(q == NULL){
                head_ = p->next_;
            }
            else {
                q->next_ = p->next_;
            }
            p->next_ = NULL;
            delete p;
        }
        else if(n+1 > getIncomplete()) {
            Node<Task>* p = retreive(n);
            Node<Task>* q = retreiveParent(n);
            delete p;
            q->next_ = NULL;
        }
        else {
            Node<Task>* q = retreive(n);
            Node<Task>* p = retreiveParent(n);
            Node<Task>* r = q->next_;
            p->next_ = r;
            q->next_ = NULL;
            delete q;
        }     
        --size_;
        return true;
    }
};
