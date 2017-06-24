/***************************************************************
 * Title: README.txt
 * Author: Julian Tutuncu-Macias
 * Date Created: 3/30/2017
 * Course: Spring 2017, CSCI 235-03, Mon & Wed 5:35-6:50pm
 * Professor: Michael Garod
 * Purpose: "Assignment 2”
***************************************************************/

Build instructions for makefile: Using the Netbeans IDE, an automatically generated makefile compiles all of my code, distributed between these files:

	main.cpp
	list.cpp	list.h
	task.cpp	task.h
	date.cpp	date.h

Parts complete: All portions of my code are complete.

Parts incomplete: There are no incomplete parts.

Known bugs: There are no known bugs.

Overview:
————————————————————————————————————————————————————————————————————————————————
Date: The Date class stores the date value of the Task class. The month, day and year are stored separately in strings. The <<, >>, == and > operators have been overloaded to interact directly with a Date object, as well as some additional functions.

	Date default constructor: declares the month, day and year strings.

	Date overloaded constructor: takes a string in the format “MM/DD/YYYY” as a parameter and parses the month, day and year values of that string into the corresponding variables.

	Date toString: recombines the data values as they are stored in the string for the date to be printed in the “MM/DD/YYYY” format.

	Date operator >> overload: similar to overloaded constructor, but takes a file input stream rather than a string as a parameter, and uses getline to parse the month, day and year values into the corresponding variables.

	Date operator << overload: similar to toString, but takes a file output stream as a parameter, and recombines the data values as they are stored in the string for the date to be outputted in the “MM/DD/YYYY” format.

	Date operator == overload: takes a right-hand-side Date object as a parameter, and compares each the month, day and year to see whether the dates are equivalent in value.

	Date operator > overload: takes a right-hand-side Date object as a parameter, and compares each the year, month and day to see whether the left-hand-side Date is greater than the right-hand-side Date.

	toUpperString: takes a string as a parameter, and converts each character in that string to its uppercase version; returns that capitalized string. While this function is not a component of the Date class, it is used by other functions of other classes which all inherit ‘date.h’ directly or indirectly, so I found it most convenient to put the function here.

————————————————————————————————————————————————————————————————————————————————
Task: The Task class is an abstract parent class for the GTask, STask, ETask and HTask subclasses, which each represent the 4 possible Task types: Generic, Shopping, Event, and Homework. The functions basicList, detailedList and pipeList are all virtual in the abstract base class. The generic Task contains a Date object, a string description as private members, a boolean that determines whether a task has completed or not, and a string indicating the type of Task. in addition to these, the subclasses of Task have more private members that allow them to store category-specific data.

	Task default constructor: prompts the user to first give the date in MM/DD/YYYY format, which is then input streamed into the private Date member. Then, the user is prompted to enter a description of the event, which is grabbed from the input stream with getline. Finally, the boolean ‘comp_’, which indicates whether a Task is completed or not, is set to false.

	Task overloaded constructor: takes a description string and Date object as parameters, and sets private members to be equal to them directly.

	Task operator << overload: takes a file output stream as a parameter, and calls pipeList (defined below) and returns that to the stream.

	Task operator = overload: takes a right-hand-side Task as a parameter, and assigns each of the current Task object’s private members the corresponding values of the right-hand-side’s private members 

	Task setDesc: takes a string as a parameter, updates description to inputted string

	Task getDesc: returns the description of the current Task

	Task setDate: takes a Date as a parameter, updates event’s date to inputted Date

	Task getDate: returns the Date of the current Task

	Task isCompleted: returns whether the current Task has been completed or not

	Task complete: sets the ‘comp_’ value of the current Task to true, marking the task as ‘completed’ 

	Task setType: takes a string as a parameter, updates type to inputted string 

	Task getType: returns type of the current Task

———————————————————————————————————————
GTask: the simplest subclass of Task, the code specific to GTask is simply the definitions of the functions declared as abstract in the superclass.

	GTask default constructor: calls superclass constructor, and then setType with parameter “G”.

	GTask overloaded constructor: takes string description and Date object as parameters, calls superclass overloaded constructor with those parameters, and then setType with parameter “G”.

	GTask basicList: strings together the Date and description of the current Task

	GTask detailedList: as no additional data pertains to a GTask object, simply calls basicList 

	GTask pipeList: similar to basicList, however data is stored with ‘|’ delimiters, so as to optimize retrieval upon the call of the LOAD command in the User Interface.

———————————————————————————————————————
STask: the Shopping subclass of Task, this object contains a vector pointer of strings for the different items on the shopping list in the private members.

	STask default constructor: calls superclass constructor, and then prompts user to input data into their list of items from the store. Getline will be called on the user’s input, and until they input “DONE”, each value retrieved in the getline is added to the shopping list vector. Finally, it calls setType with parameter “S”.

	STask overloaded constructor: takes string description, Date object and vector pointer of strings as parameters, calls superclass overloaded constructor with the corresponding parameters, and then assigns the STask private member vector pointer of strings to be the parameter vector. Finally, it calls setType with parameter “S”.

	STask basicList: strings together the Date and description of the current Task plus a caption distinguishing the Task as a Shopping Task 

	STask detailedList: first calls basicList, then appends each item on the shopping list into a new line, indented once

	STask pipeList: data is stored with ‘|’ delimiters, but after the generic Date and description are saved, each word in the shopping list is saved, separated by ‘|’s.

———————————————————————————————————————
ETask: the Event subclass of Task, this object contains two strings, one that gives a location for the event, and another that gives a time of day.

	ETask default constructor: calls superclass constructor, and then prompts user to enter a location and a time of day, which are each taken from the input stream with getline. Finally, it calls setType with parameter “E”.

	ETask overloaded constructor: takes string description, Date object, string location and string time and calls superclass overloaded constructor with the corresponding parameters. It then assigns the ETask private member string location to be the parameter location, and same for the time. Finally, it calls setType with parameter “E”.

	ETask basicList: strings together the Date and description of the current Task plus a caption distinguishing the Task as an Event Task

	ETask detailedList: first calls basicList, then appends the location and time of day each onto a new line

	ETask pipeList: data is stored with ‘|’ delimiters, but after the generic Date and description are saved, the location and time are each saved, separated by a ‘|’.

———————————————————————————————————————
HTask: 

	HTask default constructor: calls superclass constructor, and then prompts user to enter a class, which are each taken from the input stream with getline. Finally, it calls setType with parameter “H”.

	HTask overloaded constructor: takes string description, Date object and string class and calls superclass overloaded constructor with the corresponding parameters. It then assigns the ETask private member string class to be the parameter class. Finally, it calls setType with parameter “H”.

	HTask basicList:strings together the Date and description of the current Task plus a caption distinguishing the Task as a Homework Task

	HTask detailedList: first calls basicList, then appends the location and time of day each onto a new line

	HTask pipeList: data is stored with ‘|’ delimiters, but after the generic Date and description are saved, the class is saved, separated by a ‘|’.

————————————————————————————————————————————————————————————————————————————————
Node: the Node structure provides the building blocks of the LinkedList class (described below). The Node structure is templated, and each Node contains a data point of some type T, as well as a Node pointer to the next Node in the LinkedList.

	Node default constructor: sets child Node pointer to NULL

	Node default destructor: deletes child Node pointer

	Node overloaded constructor: takes data of type T and sets private data member to it; also sets child Node pointer to NULL
	
————————————————————————————————————————————————————————————————————————————————
LinkedList: this class provides the overall data structure for our to-do list, and is built by stringing along Nodes. The private members of the LinkedList class are the head Node pointer, and the size_t size of the LinkedList. The LinkedList class uses the templated class T, but some of the functions are specialized to use the Task class, as there are specific functions that must take into account characteristics of the Task objects, such as the “isCompleted” status, while operating.

	LinkedList default constructor: sets head Node pointer to null, sets size to 0.

	LinkedList default destructor: deletes head Node pointer.

	LinkedList getSize: returns size.

	LinkedList push_front: takes a data point as the parameter, and creates a new Node to contain it. The pointer of that node is set to the current head Node, and the newly created Node becomes the new head Node.

	LinkedList isEmpty: The function takes a boolean as a parameter, which dictates its functionality: if the input is ‘false’, it will return whether there are no Nodes which contain incomplete Tasks; if the input is ‘true’, it will return whether there are no Nodes which contain complete Tasks.

	LinkedList detailed: for each Node in the LinkedList, if the Task it contains is incomplete, it prints its detailed description.

	LinkedList print: takes a boolean parameter that, similar to isEmpty, dictates its functionality: if the input is ‘false’, for each Node in the LinkedList, if the Task it contains is INCOMPLETE, it prints its basic description. If the input is ‘true’, it prints the basic description of each task if it is COMPLETE.

	LinkedList push_sorted: taking a Task object pointer as a parameter, this function first checks if the list is empty, and if it is, calls push_front. Otherwise, it creates some helper Nodes to help loop through the LinkedList, comparing the Date values of the Tasks in each Node of the LinkedList with the Date value of the newly created Task, until the correct location in the list has been found. Then, the Node is inserted into the LinkedList, and size is incremented by one.

	LinkedList getIncomplete: looping through the LinkedList, this function tallies the number of Nodes that have not yet been marked as complete.

	LinkedList retrieve: Given a parameter int n, this function returns the nth INCOMPLETE Task in the list. It first checks if the inputted n is valid, and if it is, it creates a temporary Node that first loops through any completed Nodes at the start of the LinkedList, and then uses a counter to loop through the remaining Nodes, checking to see whether they are already completed and therefore do not factor into the index ’n’ the user has given. Once the nth Node that has not been completed is reached, that Node pointer is returned to the user.

	LinkedList retrieveParent: Given a parameter int n, this function returns the parent of the nth INCOMPLETE Task in the list. It first checks if the inputted n is valid, and if it is, it creates two temporary Nodes: one that acts the same way as the temporary Node in the ‘retrieve’ function, and one that stores a pointer to the parent of the first Node. Once the nth Node that has not been completed is reached by the first Node, the parent Node pointer of that Node pointer is returned to the user.

	LinkedList remove: first checks if the LinkedList is empty, and returns false if so. Otherwise, if the user is trying to remove the first incomplete Node, that Node and its parent Node are retrieved. If the parent Node is null, then the head Node is simply set to the child of the first incomplete Node. Otherwise, the child Node of the parent Node is set to the child of the current Node, the child Node of the current node is set to null, and the current Node is erased. Then, for the case where the last Node is being removed, the desired Node and it’s parent are retrieved, and the child of the parent Node is set to the child of the current Node. Finally, the child of the current Node is set to NULL, and the current Node is deleted. After 1 of these 3 options is completed, then the size of the list is decremented by 1 and true is returned.

————————————————————————————————————————————————————————————————————————————————
Main: the main.cpp file holds the User Interface, which is limited to a while loop that takes in user input and processes it as either ADD, PRINT, DETAILED, REMOVE, COMPLETE, COMPLETED, SAVE, LOAD, or EXIT.

	ADD: the user is prompted to give the type of the new Task that will be added: (G)generic, (S)hopping, (E)vent, or (H)homework. Then, the new Task subclass is created based on that answer, and the user is prompted for more information by the constructor of whichever Task subclass gets created. Finally, once the Task is created, the new Task is push_sorted into the LinkedList.

	PRINT: first checking if the list is empty and giving an alert if so, this function calls ‘print’ on the LinkedList with a parameter of false, having the function print only the Tasks that are marked INCOMPLETE.

	DETAILED: first checking if the list is empty and giving an alert if so, this function calls ‘detailed’ on the LinkedList.

	REMOVE: first checking if the list is empty and giving an alert if so, this function prompts the user to enter the index of the Task that is to be removed, and checks first that the user entered a numerical value, and then checks whether said value is legal considering the size of the LinkedList. Once the index is cleared to be processed, ‘remove’ is called on the LinkedList, with the user-entered index as the parameter.

	COMPLETE: first checking if the list is empty and giving an alert if so, this function prompts the user to enter the index of the Task that is to be completed, and checks first that the user entered a numerical value, and then checks whether said value is legal considering the size of the LinkedList. Once the index is cleared to be processed, ‘complete’ is called on the LinkedList, with the user-entered index as the parameter.

	COMPLETED: first checking if the list is empty and giving an alert if so, this function calls ‘print’ on the LinkedList with a parameter of true, having the function print only the Tasks that are marked COMPLETE.

	SAVE: first checking if the list is empty and giving an alert if so, this function prompts the user to enter a file to store the outputted data in (must be a .txt file). Then, a file output stream is opened for the user-inputted directory, and the Task data is piped into the file.

	LOAD: first checking if the list is empty and giving an alert if so, this function prompts the user to enter a file to pull the data from (must be a .txt file). Then, a file input stream is opened for the user-inputted directory, and each line is parsed through a series of getline calls which consider the type of each Task being added. Each Task type has its own case and process of parsing the text into a Task subclass object.

	EXIT: bids the user farewell and exits the while loop