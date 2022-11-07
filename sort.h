/**************************************
Template created by Kazumi Slott
CS311

Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 1
Any difficulties?: The assignment was straightforward.
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}


//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.

/****************************************** 
Explain what this function does: This function sorts an array by making a temp variable to compare a sorted and unsorted portion of the array.
Explain each parameter: The paramaters for this function is to use a pass by reference array and a integer variable as the size.
Explain what it returns: This functions only purpose it to sort, it doesn't have a specific return.
*******************************************/ 
void insertionSort(int ar[], int n)
{
  for(int i=1; i < n; i++){  //start at index 1 since we assume the left unsorted size is already sorted 
    int temp = ar[i]; //store that index element into temp so we don't lose it
    int j = i-1;     //We are comparing items to the left ajecent side of the array
    while( j>=0 && ar[j] > temp){ //these conditons are so we don't go out of the array bounds, and to check which element is greater 
      ar[j+1] = ar[j];           //we swap until we find a spot to insert temp
      j--;                      //decrement since we are going down the array
    }
    ar[j+1] = temp;  //we know found the correct spot to insert temp since all elements were shifted over
  }
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document

/****************************************** 
Explain what this function does: This function sorts an array by finding the smallest elemnent and placing it to the left each iterration.
Explain each parameter: The paraemnters are a pass by reference array and size of the array.
Explain what it returns: This function purpose is to sort, it doesn't have a specific return.
*******************************************/ 
void selectionSort(int array[], int N)
{
  int minIndx; //the index of the smallest value

  //first is the smallest index in unsorted part
  for(int first = 0; first < N-1; first++)
    {
      minIndx = first; //assume the first item is the smallest
      //find the lsmallest in unsorted part ([0..last])
      for(int i = first+1; i < N; i++)
	{
	  if(array[i] < array[minIndx]) //The current item is larger
	    minIndx = i;
	}

      //swap the largest with the last item in the unsorted part
      swap(array[minIndx],array[first]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 

/****************************************** 
Explain what this function does: This function is a optimized version of bubble sort where if no ajecent elements are swapped in a itteration then the array is sorted.
Explain each parameter: It contains a pass by refrence array, and size of the array.
Explain what it returns: Only purpose it to sort, doesn't have a specific return.
*******************************************/ 
void bubbleSort(int ar[], int s)
{
  
  bool swapped = false; //true if there was swapping in the current iteration, false otherwise                                   
  int last = s-2; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(!swapped) //swapping required in the previous iteration or the first iteration starts                        
    {
      swapped = true; //no swapping has happened yet when a new iteration starts.                                         

      for(int i=0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
	  if(ar[i+1] <= ar[i]) //the pair is out of order                                                          
	    {
	      swap(ar[i], ar[i+1]);
	      swapped = false; //swapping required - meaning we need to proceed to the next iteration.                            
	    }
        }
      last--; //the area to be checked shrinks down after each iteration                                         
    }//end of while                                                                                               
  
}

/******************************************                                                                                                                                                                
Explain what this function does: This function finds a parition by swapping the middle element to the last element. It looks for every value less than the pivot and swaps the counter that is in the beggi
ning of the array and the pointer that itteriates the array. If a element is smaller than the pointer that is in the beggining of the array gets incremented by one.                                       
Explain each parameter: The parameters is an array used to itteriate, a start variable to know the current index of the beggining, and a end variable to know the end of an array.                         
Explain what it returns: The function returns the current pivot position                                                                                                                                  
*******************************************/
int partition(int a[], int start, int end)
{
  int median = (start + end) / 2; //get middle element index
  swap(a[median], a[end]);   //swap so we can call pivot = end
  int pivot = end;
  int index = start;              //index is initilaiized to start of array
  for(int i = index; i<pivot; i++){  //loop through the array until it's reached the end of pivot
    if(a[i]<=a[pivot]){
      swap(a[index], a[i]);    //call swap function if we find a value less than the pivot
      index++;
    }
  }
  swap(a[pivot], a[index]); //store pivot back onto the the partially sorted array
  return index;

  //copy and paste partition() from your quickSort.cpp
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
  //copy and paste quickSort() from your quickSort.cpp 
}

/******************************************                                                                                                                                                                
Explain what this function does: This function is to merge the array that was divided into a size of 1. We then use 2 pointers to keep track of the left and right smaller arrays,                         
and also a iteriator to keep track of the temp array created. At the end we overwrite the original array witht the sorted temp array.                                                                      
Explain each parameter: This function used an array to merge, a iteriator for the left arraay, and a iteritior for the right array                                                                         
Explain what it returns: This function is void, so it doesn't return anything other then to merge sorted sub-arrays.                                                                                       
*******************************************/

void merge(int ar[], int l, int r)
{
  int m = (l+r)/2; //middle index
  int left = l;       //start index for left array
  int right = m + 1;   //start index for right array
  int i = 0;       //itertor for new array

  int *temp = new int[(r-l)+1]; // create temp array

  while (left <= m && right <= r) {  //iteriate through left and right indicies of each array
    if (ar[left] <= ar[right]) { //store the less than value to temp array
      temp[i] = ar[left];
      left++;                  //increment left pointer since we need to check each left to right
      i++;                    //increment iteriator for temp array
    }
    else {
      temp[i] = ar[right]; //current right pointer is less than so we add to temp array
      right++;              //increment right pointer to check all elements
      i++;                  //increment iteriator for temp array
    }
  }
  // Copy the remaining elements of first half, if there are any
  while (left <= m) {
    temp[i] = ar[left];
    left++;
    i++;
  }

  // Copy the remaining elements of second half, if there are any
  while (right <= r) {
    temp[i] = ar[right];
    right++;
    i++;
  }

  /* Copy the temp array to original array */
  for(int i=l; i <=r; i++){
    ar[i] = temp [i-l];   //this is for when the left iteriator is in another location other then 0
  }
  delete []temp;

  //copy and paste merge() from your mergeSort.cpp   
}


/******************************************                                                                                                                                                                
Explain what this function does: This function splits the array until their is one element left                                                                                                            
Explain each parameter: We use an array to be able to divide, a counter for the beginning, and a counter for last                                                                                          
Explain what it returns: This function is void so doesn't return anything                                                                                                                                  
*******************************************/
void mergeSort(int ar[], int first, int last)

{
  if (first < last){
    //divide the array at mid and sort independently using merge sort
    int mid=(first+last)/2;
    mergeSort(ar,first,mid);
    mergeSort(ar,mid+1,last);
    //merge or conquer sorted arrays
    merge(ar,first,last);
    //For implementation of this function, refer to my lecture notes "merge sort"
  }
}
/*
int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  print(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  print(ar1, 6); //1 3 4 5 7 9

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  print(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;

  //copy and paste mergeSort()from your mergeSort.cpp   
}
*/


