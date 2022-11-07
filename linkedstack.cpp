#include <iostream>
using namespace std;
#include "stack_L_T.h"

void func(const Stack<int>& s); 
int main(){

Stack<int> s;

 if(s.empty()){ 
  cout << "Empty" << endl; //Empty
   } 
 
  try 
    { 
      s.pop(); 
    } 
  catch(Stack<int>::Underflow) 
    { 
      cout << "Illegal operation. - Stack is empty" << endl; 
    }
 
//recovered from the error - If we didn't use try-catch, the program would abort at pop() above. 
 
// cout << s.getSize() << endl; //0


  s.push(1); 
  s.push(2); 
  // cout << s.getSize() << endl; //2
  cout << s << endl;   

  s.getTop()++; //T& return type lets you change top element. Top is now 3 from 2. 
 
  int& r = s.getTop(); //r points to the top element 
  cout << "address of top->elem" << &r << endl; 
 
  r += 200; //adds 200 to top element 
  cout << r << endl; //203 
 
  int top = s.getTop(); //top gets 203 
  cout << top << endl; //203 
  top++; //top becomes 204 
  cout << s.getTop() << endl; //But the top element is still 203 
  cout << s << endl;   
  
    
  Stack<int> s2; 
  s2 = s; //operator= is called here.  
  //  cout << s.getSize() << endl; //2 
  
  cout << s2 << endl; 
   
  //  func(s); //testing const T& getTop() const 
 
   Stack<int> s3(s); //testing the copy constructor 
   cout << s3 << endl;  
 return 0;
}
void func(const Stack<int>& s) 
{ 
  cout << "Calling the const version of getTop()" << endl; 
  cout << s.getTop() << endl; 
  //s.getTop()++; ß will not compile 
} 
