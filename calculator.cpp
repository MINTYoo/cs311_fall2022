#include <iostream>
using namespace std;
#include "stack_L_T.h"
/*
Name:Ruben Cerda
progrmming ID: 7
Hours spent: 4
*/
  bool valid_operand(const char& op);
  int presidence(const char& c);
  bool valid_operator(const char& op);
  string infix_to_postfix( string& str);
  double postfix_answer(string& str);


  int main() {
    
        string infix;
    // string infix[9] = {")5*2)+5", "(5+8))*6", "5%8", "(+5)/2", "(55+3)/4" ,"5+*2","(5+2*3-1)-8/(3+1)","1253*/+7+","((5+6-2)*2/5)/3"}; 
       string postfix;
       double result;
       cin >> infix;

       
      try{
	postfix= infix_to_postfix(infix);
	cout << postfix << endl;
	result = postfix_answer(postfix);
	cout << result <<endl;
 
      }
    catch(Stack<char>::Underflow){
      cout << "The expression is in a wrong format" <<endl;
    }
    catch(Stack<double>::Underflow){
      cout << "The expression is in a wrong format" << endl;
    }
    catch(const char* msg){
      cout << msg << endl;
    }
    
  }
/******************************************
Explain what this function does: This function checks the presidence of a operator
Explain each parameter: The parameter is a pass by refernece const char used for checking the operator
Explain what it returns: Returns the presidence level
*******************************************/ 

int presidence(const char& c){

  int presidence;            //Give a level to a presidence operator
  
  if(c == '+' || c == '-'){
    presidence = 1;
  }
  else if(c == '*' || c == '/'){
    presidence = 2;
  }
  else{
    return -1; 
  }

  return presidence;
}
/******************************************                                                                                                                                                                 
Explain what this function does: This function is a boolian type that returns a valid operator                                                                                                                                                                            
Explain each parameter: The parameter is a pass by refernece const char used for checking the operator                                                                                                                                                                                     
Explain what it returns: The boolian type                                                                                                                                                                                    
*******************************************/
bool valid_operator(const char& op){

  if(op == '*' || op == '+' || op == '-' || op == '/' ){ //If a operator return true or false
    return true;
  }
  else{
    return false;
  }
}
                                                                                                                                                                
/****************************************** 
Explain what this function does: This function is to provide the boolian type of the operand given 
Explain each parameter: it's a pass by reference const char that is used for determing if a operand is valid or not
Explain what it returns Returns the boolian type
*******************************************/                                                                                                     
                                                                                                                                                                               
                                                                                                                                                                                                                                                                                             
                                                                                                                                                                             
bool valid_operand(const char& op){
  if(isdigit(op)){  //if a operand return true or false
    return true;
  }
  else{
    return false;
  }

}
/****************************************** 
Explain what this function does: This function goes through a string to check if it's suitable to be converted to postfix
Explain each parameter: It's a string type that is used for indexing
Explain what it returns: Returns the new string once the infix is turned to postfix.
*******************************************/ 

string infix_to_postfix( string& str){
  Stack<char> s;
  string postfix="";
  
  for(int i=0; i < str.size(); i++ ){ //loop through string 
    if(valid_operand(str[i])){       //append postfix string to given operands
      postfix += str[i];
    }  
    else if(str[i] == '('){  //first case of '(', push
      s.push(str[i]);
    }
    else if(str[i] == ')'){ //second case of ')'
      while(!s.empty() && s.getTop() != '('){ //loop while the stack is not empty and has not found '('
        postfix += s.getTop();  //append all operator to the string 
        s.pop();               //pop all elements to give parenthesis it's higher order
      }
      if(s.getTop() == '('){  //'(' is still in stack pop
        s.pop();
      }
      else if(s.getTop() != '('){  //if not found the matching brace throw exception
        throw Stack<char>:: Underflow();
      }
    }
    else if(valid_operator(str[i])){ //check if operator is valid
      if(s.empty()){ //if stack is empty simply push
        s.push(str[i]); 
      }
      else if(presidence(str[i]) > presidence(s.getTop())){ //if current char in string is greather than top then push
        s.push(str[i]);
      }
      else{
        while(!s.empty() && presidence(str[i]) <= presidence(s.getTop())){ //if current char is less than or equal to top append to string and pop
          postfix += s.getTop();
          s.pop();
        }
        s.push(str[i]);  //push the current char after all elements in stack were appended to the string
      }
    }
    else{
      throw "The expression is in a wrong format"; //else not a valid operator & operand
    }
  }

  while(!s.empty()){    //while stack is not empty loop and append anything that is left over in the stack
    postfix+=s.getTop();
    s.pop();
  }
  return postfix;
}

/****************************************** 
Explain what this function does: This function converts the postfix to a answer using a double type stack
Explain each parameter: The parameter is a string that is know a postfix expressiom
Explain what it returns: It returns the result of calculating the postfix expression
*******************************************/ 
  double postfix_answer(string& str){
    Stack<double> s;
    char temp;
    double x, y,result;
  
    for(int i=0; i<str[i]; i++){ //loop through string 
      temp = str[i];
      if(valid_operand(str[i])){ //check if a number is valid
        double convert_result = temp - '0'; //convert char to double
        s.push(convert_result);
      }
      else if(valid_operator(str[i])){ //check if a valid operator
        y = s.getTop();  //pop each top and asisgn it to a variable twice
        s.pop();
        x = s.getTop();
        s.pop();
        switch(str[i]){
	case '+': result = x + y; break;
	case '-': result = x - y; break;
	case '*': result = x * y; break;
	case '/': result = x / y; break;
	default: throw Stack<char>::Underflow(); //not a valid operator
        };
        s.push(result);
      }
      else{
	throw Stack<double>::Underflow(); //not a valid operator or operand
      }
    }
    result = s.getTop(); //assign result to top and clear stack
    s.pop(); 
  
    if(s.empty()){    //if empty we know it's a valid postfix expression
      return result;
    }
    else{
      throw Stack<double>:: Underflow(); //else their are still elements in the stack, so unvalid
    }      
  }
 
