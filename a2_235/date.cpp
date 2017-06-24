/*
 * Title: date.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: implements all class and function definitions given in date.h
*/

#include "date.h"

//constructor: declares month, day and year strings
Date::Date(){
    std::string m_;
    std::string d_;
    std::string y_;
};

/* overloaded constructor: takes string in "MM/DD/YYYY" format
   sets m_, d_ & y_ correspondingly*/
Date::Date(std::string dateStr) {
    this->m_ = dateStr.substr(0,2);
    this->d_ = dateStr.substr(3,2);
    this->y_ = dateStr.substr(6,4);
};

//returns Date in MM/DD/YYYY format
std::string Date::toString() const {
    std::string s = m_ + "/" + d_ + "/" + y_;
    return s;
};

/* takes input stream as parameter in "MM/DD/YYYY" format
   sets m_, d_ & y_ correspondingly*/
std::istream& operator>>(std::istream& is, Date& d) {
  getline(is, d.m_, '/');
  getline(is, d.d_, '/');
  getline(is, d.y_);
  
  d.m_.erase(std::remove(d.m_.begin(), d.m_.end(), '\n'), d.m_.end());
    return is;
};

//returns Date in MM/DD/YYYY format to output stream
std::ostream& operator<<(std::ostream& os, const Date& d) {
  os << d.m_ << "/" << d.d_ << "/" << d.y_;
  return os;
};

//returns whether the date values of two Dates are equal
bool operator==(const Date& lhs, const Date& rhs){  
  return (lhs.y_ == rhs.y_) && (lhs.m_ == rhs.m_) && (lhs.d_ == rhs.d_);
};

/* returns whether the left-hand Date object is 'greater than' (occurs after) 
   the right-hand Date object*/
bool operator> (const Date& lhs, const Date& rhs){
    if(lhs==rhs){
      return false;
    } else if (lhs.y_ < rhs.y_) {
      return false;
    } else if (lhs.y_ == rhs.y_) {
        if (lhs.m_ < rhs.m_) { 
          return false;
        } 
        else if (lhs.m_ == rhs.m_) {
             if (lhs.d_ < rhs.d_) {
                return false;
             }
        }
    }
    return true;
};

//converts inputted string to uppercase for simplicity
std::string toUpperString(std::string in) {
  std::string out = "";
  std::locale loc;
  for (int i=0; i<in.length(); ++i)
    out += toupper(in[i], loc);
  return out;
};