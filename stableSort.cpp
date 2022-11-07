/***************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons.                                            
                                                                                   
Your name: Ruben Cerda                                                                 
Your programmer number: 7                                                      
Hours spent: 40 minutes                                                                
Any difficulties?: The assignment was straightforward.                                                           
****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "swap.h"  //<=== include your swap.h if you made it so you can call your mySwap() in stableSort(). 
                      //     If you didn't make it, you can make a swap function in this file or call the library's swap(). 
using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("/cs/slott/cs311/stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()
/****************************************** 
Explain what this function does: This function checks if the object.grade is less than the object before
explain each parameter: This function takes two objects to reference their data type
Explain what it returns: This function returns either true or false bases on the outcome
*******************************************/ 
bool grades( person x, person y){ return x.grade < y.grade;}
/****************************************** 
Explain what this function does: This function checks if the object.first name is less than the object before
explain each parameter: This function takes two objects to reference their data type.  
Explain what it returns: This function takes two objects to reference their data type
*******************************************/ 
bool first_name(person x, person y){ return x.fN < y.fN;}
/****************************************** 
Explain what this function does: This function checks if the object.last name is less than the object before
Explain each parameter: This function takes two objects to reference their data type.
Explain what it returns: This function takes two objects to reference their data type.
*******************************************/ 
bool last_name(person x, person y){  return x.lN < y.lN;} 

/****************************************** 
Explain what this function does: This function is a stable sorting algorithem(insertion sort)to sort the array of objects
Explain each parameter: It takes an array of objects, size of the array of objects, and a pass by function to compare all 3 cases
Explain what it returns: This function return type is void, only purpose is to sort.
*******************************************/ 
void stableSort(person p[], int n,  bool (&func)(person, person))
{

  for(int i=1;i<n;i++){   //iteriate the array of objects
    int j = i;        
    while(func(p[j],p[j-1]) && j > 0 ){ //call the bool functions 
      swap(p[j],p[j-1]);
      j--;           
    }
  }
  //You can use a stable sort algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().                    
}


 int main()
 {
  person ar[SIZE];
  if(fillAr(ar))
  {
    cout << "--- original ---" << endl;
    printAr(ar);

    //You need to sort the array here
    //HINT: call stableSort multiple times.
    stableSort(ar, SIZE, first_name);
    stableSort(ar, SIZE, last_name);
    stableSort(ar, SIZE, grades);

    cout << "--- result ---" << endl;
    printAr(ar);
  }
}


