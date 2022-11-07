/**********************************
CS311 Kazumi Slott

Your name: Ruben Cerda
Your program number: 7
Hours spent: 5
Describe any difficulties here: Just finding a segmentation fault I had for algB for checking a subarray out of boun\
ds
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runtime complexity of this algorithm? O(N^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
#include <iostream>
using namespace std;
int algoA(const int a[], int sz)//Don't change the function headers
{
  int max=0;
  for(int i=0; i<sz; i++){ //itteriate through the array
    for(int j=i; j<sz;j++){//go through subarray size 1,2, and so on
      int sum=0;
      for(int k=i; k<=j; k++){ //handle the addition
        sum+=a[k];
        if(sum>max){ //check for the highest sum of each pass
          max=sum;
        }
      }
    }
  }
  return max;
}

//What is the runtime complexity of this algorithm? O(N^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
  int max=0;
  for(int i=0; i<sz; i++){ //iteriate through the array
    int sum=0;
    for(int j=1; j<=sz; j++){ //increase the subarray size
      if(i+j > sz){ // make sure the subarray pairs doesn't go out of bounds
        break;
      }
      sum+=a[i+j-1]; //for the last element of each subarray
      if(sum>max){ //get the max amount of a subarray
        max=sum;
      }
    }
  }
  return max;

}

//What is the runtime complexity of this algorithm? O(N)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{

  int max=0;
  int sum=0;
  for(int i=0; i<sz; i++){ //iteriate through the array
    sum+=a[i];
    if(sum<0){ //if the current subarray is less than 0 then move up a index and start checking for a new sum
      sum=0;
    }
    else if(sum>max){ //get the max amount of a subarray
      max=sum;
    }

  }
  return max;

}

