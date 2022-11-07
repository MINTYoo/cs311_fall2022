/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Ruben Cerda
Your programmer number here: 7
Hours spent: 4
Any problems you had? Explain here: I was having trouble how to implement the deep copy but after drawing it carefully I was able to come up with a solution.
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template < class T >
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;
  Node<T> *next;
  //???? elem;
  //???? next;  //check how right and left pointers are declared in BST class --> /cs/slott/cs211/BST_T.h
 public:
  Node(){this->next = NULL;} //default constructor
  Node(const T& e){this->next = NULL;} //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

 private:
  Node<T>* top;
  //???? top;
 
 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() {this->top=NULL;} //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{ if(this->top == NULL){return true;} return false; } //implement a small function inside the class definition
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function
 
  class Underflow{

  };

  //Make an empty exception class here. Underflow or/and Overflow? - You need to figure out where to throw an exception - I am throwing in 3 functions.
  //??????????
};


//Complexity of this operation: O(1)
/******************************************
Explain what this function does: This function makes a new node and checks to see if the top Node is NULL if so then the new Node created is the top. Else we add the new created note to the memory address of the top and make the new Node the top
Explain each parameter: The parameter val is used to initialize the new Node 
Explain what it returns it's a void so it only implements adding a new node
*******************************************/ 
template <class T>
void Stack<T>::push(const T& val)
{ 
  Node<T> *ptr = new Node<T>; // create the node
  ptr->elem = val; //initialze the node
  if(this->top == NULL){ //if top is null then ptr is the start of top
    this->top = ptr;
  }
  else{
    ptr->next = this->top; //establish a link between the new node and top
    this->top = ptr;

  }
  //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h 
}



//Complexity of this operation: O(1)
/****************************************** 
Explain what this function does: This function popes the top element of the stack, but first needs to make a temp pointer to move the head. Also throw an exception if the top is null so we don't pop any Node that doesn't exist. 
Explain each parameter: Doesn't need any parameter.
Explain what it returns: it's void so it only purpose is to delete the top pointer.
*******************************************/ 
template <class T>
void Stack<T>::pop()
{
  if(empty()){ //top is NULL so no Node is present
    throw Underflow();
  }
  Node<T> *temp = this->top; // make a temp ptr to move the top to keep link established
  this->top = this->top->next;
  delete temp;
  //What do you do if the stack is empty?

}



//Complexity of this operation: O(1)
/****************************************** 
Explain what this function does: This function returns the top element while checking if the top is not NULL. 
Explain each parameter: No parameters
Explain what it returns This function returns the top element while being pase by refernce so we can change it in main.
*******************************************/ 
template <class T>
T& Stack<T>::getTop()
{ 
  if(empty()){ //throw exception if top is NULL
    throw Underflow();
  }
  //What do you do if the stack is empty?
  return this->top->elem; //return the top element. Since the return type is T&, the client can change the top.
}



//Complexity of this operation: O(1)
/****************************************** 
Explain what this function does: This function is to return the top element while not being able to change it due to being const.
Explain each parameter: no parameter
Explain what it returns: This function returns the value of a stack object. 
*******************************************/ 
template <class T>
const T& Stack<T>::getTop() const
{

  if(empty()){ // check if top is not NULL, if so throw an exception.
    throw Underflow();
  }
  //What do you do if the stack is empty?
  return this->top->elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}




//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(N)
/****************************************** 
Explain what this function does: This function is to display all values in the stack.
Explain each parameter: the ostream& o is to be able to cout the object in main, and the const stack<T>& s is to be able to call the current object to refernce the top Node 
Explain what it returns: This function returns o so you can cout the stack object in main.  
*******************************************/ 
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.
  
  Node <T> *ptr = s.top; //make a new pointer start at the top of the stack
  o << "--- Top ---" << endl;
  while( ptr  != NULL){ // keep iteriating while ptr is not null
    o << ptr->elem << endl;
    ptr = ptr->next;  // move ptr up one Node each time.
   
    
  }

  o << "--- Bottom ---" << endl;
  return o;
}


/****************************************** 
Explain what this function does: destructor to release all nodes created.
Explain each parameter: no parameter
Explain what it returns: this function doesn't return anything, only releases allocated memory.
*******************************************/ 
template <class T>
Stack<T>::~Stack()
{
  destroy(); //call the destory function that is already implemented.
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(N)
/****************************************** 
Explain what this function does: This function is to delete all nodes in the stack by first pointing to the top and tranfering the top each iteriation
Explain each parameter: No parameters for this function.
Explain what it returns: It's void, the only purpose is to release all the allocated memory.
*******************************************/ 
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  while(this->top != NULL){
    Node<T> *ptr = this->top;  //ptr starts at the top iteriation and moves top to the next to not lose a connection
    this->top = this->top->next;
    delete ptr;
  }
  //destroy all nodes
  //?????????????? 
}


//Complexity of this operation: O(1)
/****************************************** 
Explain what this function does: This function checks to see that the created object address is not the same as the RHS object, if so we can release any memory the "this" pointer has and be able to copy the stack over.
Explain each parameter: the const Stack& rhs is a object that we use to check if the address aren't the same. Also the reason it's const and pass by reference.
Explain what it returns: This function returns the object pointer being created 
*******************************************/ 
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&). 
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;


  //deep copy
  if(this->top != rhs.top) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      destroy();
      copy(rhs);
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
    }
  return *this; //return the "this" object (not the address of the "this" object). Notice the return type is not void. 
                  //By returning the this object, we can use multiple assignment operators. 
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2). 
}



//Complexity of this operation: O(n)
//helper fuction. called from operator= and copy constructor
/****************************************** 
Explain what this function does: This function is to make a deep copy of the object in the parameter by assigning a new pointer as the top and using an additional two pointers to itteriate both the current stack and the stack being created.
Explain each parameter: The const Stack& source is a object that is used to assign a ptr to the top to itteriate and copying each node over to the new stack. 
Explain what it returns: this function is void, it's purpose to copy each node and make a seperate stack that won't act as a shallow copy.
*******************************************/ 
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{

  if(source.top == NULL){ //check if the top is not NULL
    throw Underflow(); 
  }
  Node<T> *ptr = source.top; //first pointer to iteriate the RHS object
  Node<T> *iter = NULL;     //second pointer to itteriate the new object
  while(ptr != NULL){      //keep looping while ptr is not NULL
    Node<T>* newl = new Node<T>; //make a new Node with the value of the RHS
    newl->elem = ptr->elem; 
    if(iter == NULL){  //first case of checking if we have no top yet in the new stack
      this->top = newl;
      iter = newl;
    }
    else{
      iter->next = newl; //second case if we already have a Node so we do a push insturction
      iter = newl;
    }
    ptr = ptr->next; //move the ptr that is in the RHS
  }
  


  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty 
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().
}



//copy constructor
/****************************************** 
Explain what this function does: This function is a copy constructor that initializes the top to null and calls the copy function with it's argument being the parameter of this function "other".
Explain each parameter: The const Stack& other is to be able to reference the object we will use to do a deep copy on.
Explain what it returns: This function return is void, so it's purpose is just to call the constructor when a copy is being made.
*******************************************/ 
template <class T>
Stack<T>::Stack(const Stack& other)
{

  this->top = NULL; //initialize top
  this->copy(other); //call the copy function 
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data member, top.
  

  //Then you can call the copy function
}



#endif // end the definition 
