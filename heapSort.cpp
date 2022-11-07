/*****************************************
Template written by Kazumi Slott
CS311

Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 2
Any difficulties?: I would say it was incorporating the recursion portiomn of max_heapify.
*******************************************/
#include <iostream>
using namespace std;

//print an integer array of size n
void print(int ar[], int n)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}
/****************************************** 
Explain what this function does: This function exchnages the values of an array without deleting it.
Explain each parameter": We use an array to refernce the elements, and two integer variables to perform the swapping.
Explain what it returns: This function doesn't return anything it only swaps values.
*******************************************/ 
//called from max_heapify and heapSort
void exchange(int ar[], int x, int y)
{
  int temp = ar[x];//set a variable for the largest element
  ar[x] = ar[y];//swap the highest element with the original root
  ar[y] = temp;
  //I have 3 lines of code here.
}

//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
/****************************************** 
Explain what this function does: This function checks for the children of the heap by checking if it's greater than, if so then we set the largest to that index. We do this recursively until the element that we are trying to fix is in it's corresponding index.
Explain each parameter: This function uses an array so we can use it to check values, a size of the array(n), and i is the value we want to fix.
Explain what it returns: This function's purpose is to bubble down the value to it's corresponding index if needed.
*******************************************/ 
void max_heapify(int ar[], int n, int i)
{

  int l = 2 * i + 1; //the index of the left child of i
  int r = 2 * i + 2; //the index of the right child of i
  int largest = i;//used to initialize the largest root in the heap


  if(l < n && ar[l] > ar[largest])//comparing if the left child is larger than the root. The first condition asks if 
    {
      largest = l;//the largest side would be set as the left child
    }
  if(r < n && ar[r] > ar[largest])//comparing if the right child is larger than the root. The first condition asks if 
    {
      largest = r;//the largest side would be set as the right child
    }
  if(largest != i)//if the largest is not a root
    {
      exchange(ar, i, largest);//exchange the 2 values -- swap the root with the largest value -- make sure to not pass 
      max_heapify(ar, n, largest);//There might be a violation at the position that was exchanged. Call max_heapify to 
    }
  /*
  int l = ?????; //the index of the left child of i
  int r = ?????; //the index of the right child of i
  int largest = ????; //the index of the largest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  ???????? //I have 4 lines of code here. You can have more or less.
  //The largest is either the right or left child. We need to exchange the parent with it.
  if(largest ?????)
    {
      //exchange the 2 values
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
    }
  */
}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
/****************************************** 
Explain what this function does: This function keeps the properties of a max heap by bubbling down all values that need to be shifted down.
Explain each parameter: This function takes an array to use in our max_heapify function, and the size of an array(n).
Explain what it returns: This function's only purpose is to keep the max heap property.
*******************************************/ 
void build_max_heap(int ar[], int n)
{
  
 for(int i = n/2; i >=0; i--){ //heapify each parent of leaf node
    max_heapify(ar,n,i);
  }

  //2 lines of code in this function
  /*
  for each non-leaf node
     call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
  */
}

//a is an unordered list to start with
//use max_heapify to sort a
//n is the number of elements in the array
/****************************************** 
Explain what this function does: This function first makes a max heap while at the same time exchnaging the root to the very end index so that that the highest value is at the bottom. We do this while the size is not >=0 since we are also decrementing the size.
Explain each parameter: This function takes an array to use for our functions, and the size of our array.
Explain what it returns: This function only purpose is to sort, it doesn't return anything specific.
*******************************************/ 
void heapSort(int a[], int n)
{
  build_max_heap(a, n);//call build_max_heap
  int size = n-1; //size of the unsorted portion of the array
  
  while(size >= 0) //repeat until heap is empty
    {  
      exchange(a, size, 0);//swap max element with last element - max element is at the end of the array
      max_heapify(a, size, 0);//calling this function to get the violations and read from the subroots
      size--;
    }
  //call build_max_heap
  //I have 6 lines of code in this function. You can have more or less.

  //build max heap from an unordered list
  //call build_max_heap
  //size of the unsorted portion of the array

  // while(??????) //repeat until heap is empty
      
      //swap max element with last element - max element is now the last element
     
      //discard the last element from the heap
     
      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.

    
}

//this function corrects a violiation at i by bubbling it up to the correct place                             
//a is a heap
/****************************************** 
Explain what this function does: This function checks if the parent node is less than the current index value, if so then we perform exchange, we set that index to be the parent.
Explain each parameter: We use an array to check values, and a index in the array to perform comparisons.
Explain what it returns: This function only buubles up any elements in the heap that break the rules. It doesn't return anything purpose.
*******************************************/                                                                                                 
void bubbleUp(int a[], int i)
{
  int parent = (i-1) / 2;
  while(i != 0 && a[i] > a[parent])//when used to exit the loop once the subroot is less than the parent 
  {
    exchange(a, parent, i);//swap the elements
    i = parent;//set to the parent once its been swapped -- index set to the location of parent
    parent = (i-1) / 2;//cycle this function once the new parent index has been set for i
   
  }
    
  //Write this function after you made insert() and while you are making remove().
}

//a is a max heap                                                                                            
//cap is the capacity of the heap                                                                            
//n is the number of elements the heap currently has before insertion                                        
//el is the new element to be inserted
/****************************************** 
Explain what this function does: This function inserts a element into the max heap while keeping the max heap with it's proporties.
Explain each parameter: This function uses an array to refrence any elements, a capacity that is the max size of the array, a counter(n) that we will increment when we insert, and a element that we wish to insert.
Explain what it returns: This function only inserts elements into the heap while maintaining the max heap property, it doesn't have a specifc return. 
*******************************************/                                                                        
void insert(int a[], int cap, int& n, int el)
{
  if(n >= cap){         //if the current counter for elements is greater then the capacity we throw a error

    throw "The array is full";
  }
  else{
    n++;             //prepare the next element to be inserted by increasing the size by 1
    a[n-1] = el;     //treat it as a normal array and add it to the last index
    int i= n-1;     //know we need to check if the parent is less than the current index, call bubbleUp 
    bubbleUp(a,i); 
  }
  
  //refer to lecture notes
  //throw "The array is full" if the array is full.
  //write this function without calling bubbleUp() first. When you work on remove(), you will notice you will
  //have to have the same code there. Move the code into bubbleUp() and call it to avoid redundancy.
}

//This function returns the index where key was found or throws an exception if key is not found.                                   
//a is a max heap.                                                                                 
//n is the number of elements in the heap.                                                                                
//key is the element we are looking for.                                                                                             
int find(const int a[], int n, int key)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)                                                                                            
    if(a[i] == key)
      return i;

  throw "The element doesn't exist";
}

//a is a max heap                                                                                            
//n is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//i is the index of the element to be removed.
/****************************************** 
Explain what this function does: This function removes an element by swapping the index we choose with the the last index of the array, we then bubble up the value if it's bigger than it's parent. We also check if the childen are greater than the current element, if so we call max_heapify.
Explain each parameter: This function uses an array to be able to compare and swap, the size of the array(n), and the index we wish to remove.
Explain what it returns: This function only purpose is to delete a element while mainting a max heap property, it doesn't have a specific return value.
*******************************************/                                              
void remove(int a[], int& n, int i)
{
  if( i >= n){                                  // Can't be a index bigger than the array itself
    throw "The index to be removed is invalid";
  }
  exchange(a,i,n-1);    //swap the current index with the the last array index;
  n--;
  int  left = 2*i+1;    //helper variables
  int  right = 2*i+2;
  int parent = (i-2)/2;
  if(a[i] <= a[left] || a[i] <= a[right]){  //if the children satisfy this comparison then we call max_heapify to correct the max heap 
    max_heapify(a,n,i);
    }
  else {             //else we know the the parent node is less than the children so we need to call bubbleUp to correct the max heap
    bubbleUp(a,i);
    }	
    
 
  

  //refer to lecture notes
  //throw "The index to be removed is invalid" if i is an invalid index.
  //Call bubbleUp or max_heapify (the lecture notes show 2 possibilities).
  //FYI, I have a total of 8 lines of code in this function. You can have more or less.
}

int main()
{
  int ar[10] = {11, 3, 4, 5, 7, 19, 20, 2, 8, 1};
  int ar2[10] = {5, 3, 10, 4, 7, 9, 11, 2, 8, 1};
  int ar3[2] = {2,1};
  int n;

  cout << "testing max_heap rooted at index 3" << endl;
  max_heapify(ar, 10, 3); //max-heapify rooted at index 3
  print(ar, 10);//11 3 4 8 7 19 20 2 5 1  --> the tree rooted at 3 is now a max-heap (8 is at root. 2 and 5 are its children)

  cout << endl << "testing max_heap rooted at index 1" << endl;
  max_heapify(ar, 10, 1); //max-heapify rooted at index 1
  print(ar, 10);//11 8 4 5 7 19 20 2 3 1  --> the tree rooted at 1 is now a max-heap (8 is at root. 5 and 7 are its children. 5's children are 2 and 3)

  cout << endl << "testing build_max_heap" << endl;
  build_max_heap(ar, 10);
  print(ar, 10);//20 8 19 5 7 11 4 2 3 1

  cout << endl << "testing heapSort" << endl;
  heapSort(ar2, 10);
  print(ar2, 10);//1 2 3 4 5 7 8 9 10 11

  cout << endl << "testing heapSort" << endl;
  heapSort(ar3, 2);
  print(ar3, 2);//1 2

  try
    {
      cout << "\ntesting insert" << endl;
      int ar4[15] = {20, 8, 19, 9, 5, 11, 4, 2, 3, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already
      n = 10; //n is the number of elements in the heap
      insert(ar4, 15, n, 15); //trying to insert 15
      print(ar4, n); //20 15 19 9 8 11 4 2 3 1 5

      n = 2;
      cout << "\ntesting exception from insert() - The array is full" << endl;
      insert(ar3, 2, n, 100); //throws "The array is full"
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  try
    {
      cout << "\ntesting remove - bubble down" << endl;
      int ar5[15] = {16, 14, 12, 8, 7, 10, 2, 3, 4, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already
      n = 10; //n is the number of elements in the heap
      remove(ar5, n, find(ar5, n, 14)); //trying to remove 14
      print(ar5, n); //16 8 12 4 7 10 2 3 1

      cout << "\ntesting remove - bubble up" << endl;
      int ar6[15] = {100, 15, 80, 13, 14, 60, 20, 12, 5, 10, 9, 50, -1, -1, -1}; //max heap with 12 elements already
      n = 12; //n is the number of elements in the heap
      remove(ar6, n, find(ar6, n, 12)); //trying to remove 12
      print(ar6, n); //100 50 80 15 14 60 20 13 5 10 9

      cout << "\ntesting exception from find() - The element doesn't exist" << endl;
      remove(ar6, n, find(ar6, n, 999)); //throws an exception
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  try
    {
      int ar7[3] = {7, 8, 9};
      n = 3;
      cout << "\ntesting exception from remove() - The index to be removed is invalid" << endl;
      remove(ar7, n, n); //throws exception. The index, n, is invalid when there are n elements in the heap (the index goes [0..n-1]).
    }
  catch(const char* msg)
    {
      cout << msg << endl;
    }

  return 0;
}
