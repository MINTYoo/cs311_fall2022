/**********************************
Templated created by Kazumi Slott
CS311

Your name:Ruben Cerda
Your programmer number: 7
Hours spent: 1 hour and 20 min
Any difficulties?: Just tracing my recursion calls, other than that it wasn't so hard.
***********************************/
#include <iostream>
using namespace std;
#include "swap.h" // include your swap.h for mySwap().  If you didn't make it for our first homework or it didn't work, you could implement it down below within this program.

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

/*
//Implement mySwap() here if you didn't make mySwap() in swap.h for our first homework.
//It is good to have the swap function so partition() won't get crowded. 
void mySwap(?????????????)
{
}
*/

/****************************************** 
Explain what this function does: This function finds a parition by swapping the middle element to the last element. It looks for every value less than the pivot and swaps the counter that is in the beggining of the array and the pointer that itteriates the array. If a element is smaller than the pointer that is in the beggining of the array gets incremented by one.
Explain each parameter: The parameters is an array used to itteriate, a start variable to know the current index of the beggining, and a end variable to know the end of an array.
Explain what it returns: The function returns the current pivot position
*******************************************/ 
int partition(int arr[], int start, int end)
{

  int median = (start + end) / 2; //get middle element index
  mySwap(arr[median], arr[end]);   //swap so we can call pivot = end
  int pivot = end;
  int index = start;              //index is initilaiized to start of array
  for(int i = index; i<pivot; i++){  //loop through the array until it's reached the end of pivot
    if(arr[i]<=arr[pivot]){
      mySwap(arr[index], arr[i]);    //call swap function if we find a value less than the pivot
      index++;
    }
  }
  mySwap(arr[pivot], arr[index]); //store pivot back onto the the partially sorted array
  return index;
  //I have 3 variables: pivot, i and swap_index. You may have any local variables.

  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).

  //For implementation of this function, refer to my lecture notes "quick sort". 
  //If you used a different algorithm, I would assume you cheated and give you zero points.

  //This function returns the index where the pivot value went in. 
}

/****************************************** 
Explain what this function does: This function is used to be called recurisively to finding a pivot and sorting the left and right of the pivot array.
Explain each parameter: The parameters is an array used to itteriate, a start variable to know the current index of the beggining, and a end variable to know the end of an array.
Explain what it returns: This function returns the sorted array
*******************************************/ 
void quickSort(int ar[], int start, int end)
{
              
  if(start < end){ //if start is less than end we know their is one element left and no need do more recursion calls.
    int pivot = partition(ar,start, end);
    quickSort(ar, start, pivot-1);  // recursive QS call for left partition
    quickSort(ar, pivot+1, end);  // recursive QS call for right partition
  }
}
//If the partition has only one element or none, return.                                                                                                                                   
//In other words, if the partition has at least 2 elements, go inside the if                                                                                                               
//use start and end to figure out how many elements you have in the partition. 

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
