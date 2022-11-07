/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: This program is to test a real life application. We can multiply the total cost of a house including it's features by the cost of a area.

Your name: Ruben Cerda 
Your programmer number: 7
Number of hours you spent: 15 min
Any difficulties?: none
*******************************************/
//What do you need to include? HINT: What are you using in main()?
//include your matrix.h
#include <iostream>
#include "matrix.h"
using namespace std;

int main()
{
  /*
  ?????
  Your matrices need to be of the same data type.  When you do multiplication, the data types of the 2 matrices need to be the same.
 

  create fin
  fin.open("/cs/slott/cs311/house_info.in");
  load the data into the first matrix
  fin.close();

  fin.open("/cs/slott/cs311/house_function.in");
  load the data into the second matrix
  fin.close();

  ?????
  use try and catch
  In catch, show the following message.
  cout << "SIZE ERROR" << endl;


  */
  Matrix<double> m1(4,4);
  Matrix<double> m2(4,3);
  ifstream fin; 

  fin.open("/cs/slott/cs311/house_info.in");
  fin >> m1;
  fin.close();
  fin.open("/cs/slott/cs311/house_function.in");
  fin >> m2;
  fin.close();

    try{
      Matrix<double> result = m1 * m2;
      cout << result << endl;
    }  
    catch(Matrix<double>::size_error){
      cout << "size error " << endl;
    }
  return 0;
}
