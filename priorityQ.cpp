/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: This program is to insert a patient in a severity level that fits our min heap propertiess. We can then remove the smallest heap element by it's properties to be able to treat the patient.
Your name: Ruben Cerda
Your programmer number: 7
Hours spent making this application: 1
Are you rejecting invalid inputs?: yes
Any difficulties: The program was straight forward
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std;
#include "minHeap.h"
#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
int getNum();
void que(minHeap<int>& que);
void deque(minHeap <int>& que);

const int START = 1000; //assuming this number will not go over 9
int COUNTER = 0; //counter to append 1 number to each patient
int main()
{
  minHeap<int> queue(START);
  int choice;
  do{
    showMenu();
   choice= getNum();
  if(choice == 1){
    que(queue);
  }
  else if(choice == 2){
    deque(queue);
  }
  }while(choice !=3);
  cout <<"The queue has " << queue;
    
  //call showMenu() to show the menu

  //You need to have the following prompt somewhere. You can move it to a different function.
  //cout << "Enter a severity, 1 most severe, .. 5 least severe: ";

  return 0;
}

//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer on
int getNum()
{
   string choice; //For example, when asking for 10, the user enters ab 
   bool bad;
   int num;

   do
     {
       bad = false;
       cout << "Enter a number: ";
       cin >> choice; 

       try
	 {
	   num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
	   if(num < 0 || num >3) // invalid choice it has to be in between 0-3
	     {
	       cout << "Invalid choice. The choice should be 1, 2, or 3. ";
	       bad = true;
	     }
	 }
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. ";
	   bad = true;
	 }
       // if(num < 0 || num >3)
       // {
       //  cout << "Invalid choice. The choice should be 1, 2, or 3. ";
       //  bad = true;
       // }
     }while(bad == true);

   return num;
}

/****************************************** 
Explain what this function does: This function takes in a severity level for the patient.
Explain each parameter: This function uses an object for our class minHeap to access it's function.
Explain what it returns: This function is type void, it's only purpose is to add to our min heap.
*******************************************/ 

void que(minHeap <int>& que){
  try{
    int option;
    cout <<"Enter a severity, 1 most severe, .. 5 least severe: "; //prompt to enter a severity
    cin >> option;
    if(option >=1 && option <=5){          //the option needs to be in between 1 and 5
      que.insert(10000*option+COUNTER+1000); //use calculations to insert the correct format for a patient queue
      COUNTER++; //increment our counter by 1
      cout << "The queue has " << que;
    }
  }
  catch(minHeap<int>::Overflow){  //catch if we have an overflow in the maximum amount of data
  }
  
}
/****************************************** 
Explain what this function does: This function removes the first element of our min heap and returns it in a cout statement.
Explain each parameter: This function uses a pass by reference object to access the getMin() function
Explain what it returns: This function is type void, it only returns the most severe patient if it exists.
*******************************************/ 
void deque(minHeap <int>& que){
  try{
    int num = que.getMin(); //varible to store the first element of our min heap
    cout << num << " is going to be treated now " << endl;
    cout << "The queue has " << que;
  }
  catch(minHeap<int>::BadIndex){ //catch if it's a bad index
    cout << "There are no patients waiting" << endl;
    cout << "The queue has none" << endl;
  }
}  




