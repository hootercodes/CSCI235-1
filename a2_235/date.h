/*
 * Title: date.h
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: defines Date class and 'toUpperString' function
*/

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include <iomanip>
#include <vector>

class Date {
 public:
  Date();
  Date(std::string dateStr);
  std::string toString() const;
  friend std::istream& operator>>(std::istream& is, Date& d);
  friend std::ostream& operator<<(std::ostream& os, const Date& d);
  friend bool operator==(const Date& lhs, const Date& rhs);
  friend bool operator> (const Date& lhs, const Date& rhs);
 private:
  std::string m_;
  std::string d_;
  std::string y_;
};

std::string toUpperString(std::string in);

#endif /*DATE_H*/