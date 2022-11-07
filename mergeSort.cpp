/**********************************
Templated created by Kazumi Slott
CS311

Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 3
Any difficulties?: Was having trouble coming up with a solution to overwrrite my original array with the temp array
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

/******************************************
Explain what this function does: This function is to merge the array that was divided into a size of 1. We then use 2 pointers to keep track of the left and right smaller arrays,
and also a iteriator to keep track of the temp array created. At the end we overwrite the original array witht the sorted temp array.
Explain each parameter: This function used an array to merge, a iteriator for the left arraay, and a iteritior for the right array
Explain what it returns: This function is void, so it doesn't return anything other then to merge sorted sub-arrays.
*******************************************/ 

void merge(int arr[], int l, int r)
{
  int m = (l+r)/2; //middle index
  int left = l;       //start index for left array
  int right = m + 1;   //start index for right array
  int i = 0;       //itertor for new array

  int *temp = new int[(r-l)+1]; // create temp array

  while (left <= m && right <= r) {  //iteriate through left and right indicies of each array
    if (arr[left] <= arr[right]) { //store the less than value to temp array
      temp[i] = arr[left];
      left++;                  //increment left pointer since we need to check each left to right
      i++;                    //increment iteriator for temp array
    }
    else {
      temp[i] = arr[right]; //current right pointer is less than so we add to temp array
      right++;              //increment right pointer to check all elements
      i++;                  //increment iteriator for temp array
    }
  }
  // Copy the remaining elements of first half, if there are any
  while (left <= m) {
    temp[i] = arr[left];
    left++;
    i++;
  }

  // Copy the remaining elements of second half, if there are any
  while (right <= r) {
    temp[i] = arr[right];
    right++;
    i++;
  }

  /* Copy the temp array to original array */
  for(int i=l; i <=r; i++){
    arr[i] = temp [i-l];   //this is for when the left iteriator is in another location other then 0
    }
  delete []temp;
 
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you are using a different technique, I assume you cheated and will give you zero points.

  //Don't forget to destroy temp array, which is created dynamically
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
int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
