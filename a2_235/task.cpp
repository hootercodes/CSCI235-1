/*
 * Title: task.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: implements all class and function definitions given in task.h
*/

#include "task.h"

//constructor: prompts user to input date and desc, sets Task to "not complete"
Task::Task() {
    std::cout << "When is this task due?" << std::endl;
    std::cin >> date_;
    std::cout << "How would you describe this task?" << std::endl;
    getline(std::cin, desc_);
    comp_ = false;
};
//constructor overload: takes date and desc as params, sets Task to "not complete"
Task::Task(std::string desc, Date date) {
    setDesc(desc);
    setDate(date);
    comp_ = false;
};

//output stream gives task description as defined in pipeList
std::ostream& operator<<(std::ostream& os, Task& t) {
      os << t.pipeList();
      return os;
};

//assignment operator copies each private member from rhs into current Task
Task& Task::operator=(const Task& rhs) {
    if (this != &rhs) {
      this->desc_ = rhs.getDesc();
      this->date_ = rhs.getDate();
      this->comp_ = rhs.isCompleted();
    }
    return *this;
};

//sets the description of the task
void Task::setDesc(std::string desc) {
  desc_ = desc;    
};

//gets the description of the task
std::string Task::getDesc() const {
    return desc_;
};

//sets the date of the task
void Task::setDate(Date d) {
    date_ = d;  
};

//gets the date of the task
Date Task::getDate() const {
    return date_;
};

//returns whether task is completed or not
const bool Task::isCompleted() const {
    return comp_;
};

//sets the task to 'completed'
void Task::complete() {
    comp_ = true;
};

//sets the type of the task
void Task::setType(std::string c) {
    type_ = c;
};

//gets the type of the task
std::string Task::getType() {
    return type_;
};

//constructor: inherits superclass constructor, then sets type to 'G' (general)
GTask::GTask() : Task(){
    setType("G");
};

/* constructor overload: inherits superclass constructor overload
 * then sets type to 'G' (general) */
GTask::GTask(std::string desc, Date date) : Task(desc, date) {
    setType("G");
};

//returns basic form of Task to be printed for "PRINT" command
std::string GTask::basicList() const {
    std::string s = this->getDate().toString() +  " - " + this->getDesc(); 
    return s;
};

//returns basicList
std::string GTask::detailedList() {
    return basicList();
};

//returns Task as it is to be stored in a file by "SAVE"
std::string GTask::pipeList() {
  std::string s = this->getType() + "|" + this->getDate().toString() + "|" + this->getDesc();
  return s;
};

/* constructor: inherits superclass constructor, then prompts user to input
   items into shopping list
 * finally, sets type to 'S' (shopping) */
STask::STask() : Task() {
    std::cout << "What items do you need to buy? [Type your item and ENTER to add another item. Type DONE to complete the list.]" << std::endl;
    std::string in;
    int index = 0;
    while (toUpperString(in) != "DONE") {
      getline (std::cin, in);
      if (toUpperString(in) != "DONE"){
        items_.push_back(in);
      }
      ++index;
    }
    setType("S");
};

/* constructor overload: inherits superclass constructor overload
 * copies over string vector, then sets type to 'S' (shopping) */
STask::STask(std::string desc, Date date, std::vector<std::string> items) : Task(desc, date) {
    items_ = items;
    setType("S");
};

//returns basic form of Task to be printed for "PRINT" command
std::string STask::basicList() const {
    std::string s = this->getDate().toString() + " - " + "[Shopping] " + this->getDesc();
    return s;
};

//returns detailed form of Task to be printed for "DETAILED" command
std::string STask::detailedList() {
    std::string s = basicList();
    s += '\n';
    s += '\t';
    s += "ITEMS TO PURCHASE:";
    for(int i = 0; i < items_.size(); i++) {
        s += '\n';
        std::string t = items_[i];
        s += '\t';
        s += t;
    }
    return s;
};

//returns Task as it is to be stored in a file by "SAVE"
std::string STask::pipeList() {
  std::string s = this->getType() + "|" + this->getDate().toString() + "|" + this->getDesc();
  for(int i = 0; i < items_.size(); i++) {
        s += "|" + items_[i];
    }
  return s;
};

/* constructor: inherits superclass constructor, then prompts user to input
   location and time of event
 * finally, sets type to 'E' (event) */
ETask::ETask() : Task() {
    std::cout << "Where is this event taking place?" << std::endl;
    getline(std::cin, loc_);
    std::cout << "When is this event taking place?" << std::endl;
    getline(std::cin, time_);
    
    setType("E");
};

/* constructor overload: inherits superclass constructor overload
 * copies over location and time, then sets type to 'E' (event) */
ETask::ETask(std::string desc, Date date, std::string loc, std::string time) : Task(desc, date) {
    loc_ = loc;
    time_ = time;
    setType("E");
};

//returns basic form of Task to be printed for "PRINT" command
std::string ETask::basicList() const {
    std::string s = this->getDate().toString() + " - " + "[Event] " + this->getDesc();
    return s;
};

//returns detailed form of Task to be printed for "DETAILED" command
std::string ETask::detailedList()  {
    std::string s = basicList() + '\n';
    s+='\t';
    s+= "WHERE: " + loc_ + '\n';
    s+= '\t';
    s+= "WHEN: " + time_;
    return s;
};

//returns Task as it is to be stored in a file by "SAVE"
std::string ETask::pipeList() {
    std::string s = this->getType() + "|" + this->getDate().toString() + "|" + this->getDesc() + "|" + loc_ + "|" + time_;
    return s;
};

//
HTask::HTask() : Task() {
  std::cout << "What subject is this homework task for?" << std::endl;
  getline (std::cin, class_);
  setType("H");
};

HTask::HTask(std::string desc, Date date, std::string className) : Task(desc, date) {
    class_ = className;
    setType("H");
};

//returns basic form of Task to be printed for "PRINT" command
std::string HTask::basicList() const {
    std::string s = this->getDate().toString() + " - " + "[Homework] " + this->getDesc();
    return s;
};


//returns detailed form of Task to be printed for "DETAILED" command
std::string HTask::detailedList() {
    std::string s = basicList() + '\n';
    s+= '\t';
    s+= "SUBJECT: " + class_;
    return s;
};

//returns Task as it is to be stored in a file by "SAVE"
std::string HTask::pipeList() {
    std::string s  = this->getType() + "|" + this->getDate().toString() + "|" + this->getDesc() + "|" + class_;
    return s;
};