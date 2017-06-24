/*
 * Title: main.cpp
 * Author: Julian Tutuncu-Macias
 * Date Created: 4/4/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2"
 * Description: provides the user interface for the to-do application
*/

#include "list.h"

void invalidInput();

//loops infinitely, allowing user to execute different commands, until user EXITs
int main() {
  
  std::string input;
  LinkedList<Task>* toDo = new LinkedList<Task>();
  
  std::cout << "Welcome to To-Do List!" << std::endl;
  do {
    std::cout << "Please enter a command: [ADD, PRINT, DETAILED, REMOVE, COMPLETE, COMPLETED, SAVE, LOAD, EXIT]" << std::endl;
    std::cin >> input;

    input = toUpperString(input);
    
    if (input == "ADD") {
      std::string type;
      do {
	std::cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H:Homework]" << std::endl;
	std::cin >> type;

	type = toUpperString(type);
	
	if (type == "G") {
	  GTask* newTask = new GTask;
	  toDo->push_sorted(newTask);
	}
	else if (type == "S") {
	  STask* newTask = new STask;
	  toDo->push_sorted(newTask);
	}
	else if (type == "E") {
	  ETask* newTask = new ETask;
	  toDo->push_sorted(newTask);
	}
	else if (type == "H") {
	  HTask* newTask = new HTask;
	  toDo->push_sorted(newTask);
	}
	else {
	  invalidInput();
	  type = "error";
	}
      } while (type == "error");
    }
    else if (input == "PRINT") {
        if ( toDo->isEmpty(false) ) {
            std::cout << "You have no outstanding tasks!" << std::endl;
        }
        else {
            toDo->print(false);
        }
    }
    else if (input == "DETAILED") {
        if ( toDo->isEmpty(false) ) {
            std::cout << "You have no outstanding tasks!" << std::endl;
        }
        else {
            toDo->detailed();
        }
    }
    else if (input == "REMOVE") {
        if ( toDo->isEmpty(false) ) {
            std::cout << "You have no outstanding tasks!" << std::endl;
        }
        else {
            int taskN;
            do {
                std::cout << "Which task would you like to remove?" << std::endl;
                std::string taskNumString;
                std::cin >> taskNumString;
                
                std::string::const_iterator it = taskNumString.begin();
                while (it != taskNumString.end() && std::isdigit(*it)) ++it;
                if(!(!taskNumString.empty() && it == taskNumString.end())) {
                    invalidInput();
                    continue;
                }
                taskN = stoi(taskNumString);
                
                if (taskN <= 0 || toDo->getIncomplete() < taskN) {
                    invalidInput();
                }
            } while(taskN <= 0 || toDo->getIncomplete() < taskN);
            
            toDo->remove(taskN);
            
            std::cout << "Task removed successfully." << std::endl;
        }
    }
    else if (input == "COMPLETE") {
        if ( toDo->isEmpty(false) ) {
            std::cout << "You have no outstanding tasks!" << std::endl;
        }
        else {
            int taskN;
            do {
                std::cout << "Which task would you like to complete?" << std::endl;
                std::string taskNumString;
                std::cin >> taskNumString;
                
                std::string::const_iterator it = taskNumString.begin();
                while (it != taskNumString.end() && std::isdigit(*it)) ++it;
                if(!(!taskNumString.empty() && it == taskNumString.end())) {
                    invalidInput();
                    continue;
                }
                
                taskN = stoi(taskNumString);
                if (taskN <= 0 || toDo->getIncomplete() < taskN) {
                    invalidInput();
                }
            } while(taskN <= 0 || toDo->getIncomplete() < taskN);
            Node<Task>* temp = toDo->retreive(taskN);
            temp->data_->complete();
            
            std::cout << "Task marked complete successfully." << std::endl;
        }
    }
    else if (input == "COMPLETED") {
        if ( toDo->isEmpty(true) ) {
            std::cout << "You have no completed tasks!" << std::endl;
        }
        else {
            toDo->print(true);
        }
    }
    else if (input == "SAVE") {
      if ( toDo->isEmpty(false) ) {
            std::cout << "You have no outstanding tasks!" << std::endl;
        }
        else {
            std::string loc;
            std::string filetype;
            do {
                std::cout << "Where would you like to save your outstanding tasks?" << std::endl;
                std::cin >> loc;
            
                int x = loc.find('.');
                if (x == -1) {
                    std::cout << "That was an invalid file, no data was saved. Please enter a valid output filename ending with \".txt\"." << std::endl;
                    continue;
                }
                filetype = loc.substr(x);
                if (filetype != ".txt") {
                    std::cout << "That was an invalid file, no data was saved. Please enter a valid output filename ending with \".txt\"." << std::endl;
                }
            } while(filetype != ".txt");
            
            std::ofstream file;
            file.open(loc);
            
            for(int i = 1; i <= toDo->getIncomplete(); i++){
                Node<Task>* temp = toDo->retreive(i);
                if(!(temp->data_->isCompleted())) {
                    file << *(temp->data_) << std::endl;
                }
            }
            
            file.close();
            std::cout << "Tasks saved successfully!" << std::endl;
        }
    }
    else if (input == "LOAD") {

        std::string loc;
        std::string filetype;
        toDo = new LinkedList<Task>();
        while(toDo->isEmpty(false)) {
            
            std::cout << "What file would you like to load outstanding tasks from? (Note: All existing tasks will be deleted)" << std::endl;
            std::cin >> loc;
            
            int x = loc.find('.');
            if (x == -1) {
                std::cout << "That was an invalid file, no data was loaded. Please enter a valid input filename ending with \".txt\"." << std::endl;
                continue;
            }
            filetype = loc.substr(x);
            if (filetype != ".txt") {
                std::cout << "That was an invalid file, no data was loaded. Please enter a valid input filename ending with \".txt\"." << std::endl;
                continue;
            }

            std::ifstream file;
            file.open(loc);

            std::string type;
            std::string dateStr;
            std::string desc;

            while(getline(file, type, '|')){
                getline(file, dateStr, '|');
                Date date;
                date = Date(dateStr);
                if (type == "G") {
                    getline(file, desc);
                    GTask* temp = new GTask(desc, date);
                    toDo->push_sorted(temp);
                }
                else if (type == "S") {
                    getline(file, desc, '|');
                    std::vector<std::string> items;
                    std::string line;
                    getline(file, line);
                    std::stringstream ss(line);
                    std::string item;
                    while(getline(ss, item, '|')) {
                        item.erase(std::remove(item.begin(), item.end(), '\n'), item.end());
                        items.push_back(item);
                    }
                    STask* temp = new STask(desc, date, items);
                    toDo->push_sorted(temp);         
                }
                else if (type == "E") {
                    getline(file, desc, '|');
                    std::string loc, time;
                    getline(file, loc, '|');
                    getline(file, time);
                    ETask* temp = new ETask(desc, date, loc, time);
                    toDo->push_sorted(temp);
                }
                else if (type == "H") {
                    getline(file, desc, '|');
                    std::string className;
                    getline(file, className);
                    HTask* temp = new HTask(desc, date, className);
                    toDo->push_sorted(temp);
                }
            }
            file.close();
            if(toDo->isEmpty(false)) {
                std::cout << "That was an invalid file, no data was loaded. Please enter a valid input filename ending with \".txt\"." << std::endl;
            }
        }
  
        std::cout << "Tasks loaded successfully!" << std::endl;
    }
    else if (input == "EXIT") {
      std::cout << "Thank you for using To-Do List!" << std::endl;
    }
    else {
      invalidInput();
    }    
  }
  while (input != "EXIT");
  return 0;
};

void invalidInput() {
  std::cout << "I'm sorry. That was not a valid command. Please enter a valid command." << std::endl;
};