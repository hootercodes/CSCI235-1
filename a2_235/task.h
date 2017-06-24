/*
 * Title: task.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: defines abstract superclass Task, and GTask, STask, ETask, and HTask subclasses
*/

#ifndef TASK_H
#define TASK_H

#include "date.h"

class Task {
 public:
    Task();
    Task(std::string desc, Date date);
    friend std::ostream& operator<<(std::ostream& os, Task& t);
    Task& operator=(const Task& rhs);
    virtual std::string basicList() const = 0;
    virtual std::string detailedList() = 0;
    virtual std::string pipeList() = 0;
    void setDesc(std::string desc);
    std::string getDesc() const;
    void setDate(Date d);
    Date getDate() const;
    const bool isCompleted() const;
    void complete();
    void setType(std::string c);
    std::string getType();
 private:
    std::string desc_;
    Date date_;
    bool comp_;
    std::string type_;
};

class GTask : public Task {
public:
    GTask();
    GTask(std::string desc, Date date);
    std::string basicList() const;
    std::string detailedList();
    std::string pipeList();
};

class STask : public Task {
 public:
  STask();
  STask(std::string desc, Date date, std::vector<std::string> items);
  std::string basicList() const;
  std::string detailedList();
  std::string pipeList();
 private:
  std::vector<std::string> items_;
};

class ETask : public Task {
 public:
  ETask();
  ETask(std::string desc, Date date, std::string loc, std::string time);
  std::string basicList() const;
  std::string detailedList();
  std::string pipeList();
 private:
  std::string loc_;
  std::string time_;
};

class HTask : public Task {
 public:
  HTask();
  HTask(std::string desc, Date date, std::string className);
  std::string basicList() const;
  std::string detailedList();
  std::string pipeList();
 private:
  std::string class_;
};

#endif /*TASK_H*/