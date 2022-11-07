/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class
Your name: Ruben Cerda
Your programmer number: 7
Hours spent making and testing your min heap class: 30 minutes
An y difficulties?: None
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c){this->capacity = c; this->ar = new T[this->capacity]; this->num = 0;}
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int i);
  void build_min_heap();
  void bubbleUp(int i);
  void insert(const T& el);
  int find(T& key) const;
  void remove(int i);
  void print();
  T getMin();

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

template <class T>
void minHeap<T>:: print(){
  for(int i=0; i<this->num; i++){
    cout << ar[i] << " " ;
  }
}
/******************************************                                     
Explain what this function does: This function checks for the children of the heap by checking if it's less than, if so then we set the smallest to that index.
 We do this recursively until the element that we are trying to fix is in it's corresponding index.                                                         
Explain each parameter: This function uses an array so we can use it to check values, the size of the array(n), and i is the value we want to fix.               
Explain what it returns: This function's purpose is to bubble down the value to its corresponding index if needed.                                            
*******************************************/

template <class T>
void minHeap<T>:: min_heapify(int i){

  int l = 2 * i + 1; //the index of the left child of i
  int r = 2 * i + 2; //the index of the right child of i
  int smallest = i;//we assume the index is the smallest


  if(l < num && ar[l] < ar[smallest])//comparing if the left child is smaller than the index we passed.
    {
      smallest = l;//the smallest side would be set as the left child
    }
  if(r < num && ar[r] < ar[smallest])//comparing if the right child is smaller than the index we passed. 
    {
      smallest = r;//the smallest side would be set as the right child
    }
  if(smallest != i)//if the smallest is not at the index we passed
    {
      swap(ar[i],ar[smallest]);//exchange the 2 values -- swap the root with the smallest value -- make sure to not pass
      min_heapify(smallest);//There might be a violation at the position that was exchanged. Call min_heapify to
    }

}

//We didn't need this function, but just added in case of future use
template <class T>
void minHeap<T>:: build_min_heap(){
  
  for(int i = num/2; i >=0; i--){ //heapify each parent of leaf node
    min_heapify(i);
  }

}

/******************************************                                     
Explain what this function does: This function checks if the parent node is less than the 
current index value, if so then we perform exchange, we set that index to be the parent.                                                            
Explain each parameter: We use an array to check values, and an index in the array to perform comparisons.                                                      
Explain what it returns: This function only bubbles up any elements in the heap that breaks the rules. 
It doesn't return anything.                      
*******************************************/ 
template <class T>
void minHeap<T>::bubbleUp(int i){
  
  int parent = (i-1)/2;
  while(i != 0 && ar[i] < ar[parent]){//when used to exit the loop once the subroot is less than the parent
      swap(ar[i],ar[parent]);
      i = parent;//set to the parent once its been swapped -- index set to the location of parent
      parent = (i-1) / 2;//cycle this function once the new parent index has been set for i

  }
}
/******************************************                                     
Explain what this function does: This function inserts a element into the min heap while keeping the min heap properties.                            
Explain each parameter: This function uses an array to reference any elements, a capacity that is the max size of the 
array, a counter(n) that we will increment when we insert, and an element that we wish to insert.                         
Explain what it returns: This function only inserts elements into the heap while maintaining the min heap property, it doesn't have a specific return.          
*******************************************/   
template <class T>
void minHeap<T>:: insert(const T& el){
  if(num >= capacity){         //if the current counter for elements is greater then the capacity we throw a error
    throw Overflow();
  }
  else{
    num++;             //prepare the next element to be inserted by increasing the size by 1
    ar[num-1] = el;     //treat it as a normal array and add it to the last index
    int i= num-1;  //know we need to check if the parent is less than the current index, call bubbleUp
    int parent = (i-1) / 2;
    bubbleUp(i);
  }

//insert()
//{
//  if(/* array is full */)
//    throw Overflow(); //"The array is full"; 
//}
}
template <class T>
int minHeap<T>::find(T& key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

/******************************************                                     
Explain what this function does: This function removes an element by swapping the index
 we choose with the the last index of the array, we then bubble up the value if it's less than 
it's parent. We also check if the children are less than than the current element, if so we call min_heapify.                           
Explain each parameter: This function uses an array to be able to compare and swap, the size of the array(n), and the index we wish to remove.                 
Explain what it returns: This function only purpose is to delete a element while maintaining a min heap property, it doesn't have a specific return value.        
*******************************************/

template <class T>
void minHeap<T>:: remove(int i){

  if( i >= num || i<0){                                  // Can't be a index bigger than the array itself
    throw BadIndex();
  }
  swap(ar[i], ar[num-1]);//swap the current index with the the last array index;
  num--;
  int  left = 2*i+1;    //helper variables
  int  right = 2*i+2;
  int parent = (i-2)/2;
  if(ar[i] >= ar[left] || ar[i] >= ar[right]){  //if the children satisfy this comparison then we call min_heapify to correct the max heap
    min_heapify(i);
  }
  else {             //else we know the the parent node is less than the children so we need to call bubbleUp to correct the min heap
    bubbleUp(i);
  }
}


//remove(int i)
//{
//  if(i is invalid)
//    throw BadIndex(); //"The element doesn't exist";                                                                       
//}

/******************************************  
Explain what this function does: This function returns the smallest element of the min heap that is in index 0(min heap properties). We then call remove to exclude it from the min heap.
Explain each parameter: This function uses no parameters.
Explain what it returns: This function returns the smallest element in out min heap array.
*******************************************/

template <class T>

T minHeap<T>::getMin()
{
  T min = ar[0]; // store into a temporary variable
  remove(0); //call remove for index 0
  return min;  //return so we can use in priorityQ.cpp
  //This function removes the top element and returns it.
  //You should be calling remove()
}

/******************************************  
Explain what this function does: This function is to show the outputs of the min heap array while still checking if it's size is less than 0 so we can cout a special message.
Explain each parameter: This function used the ostream operator and a const pass by refrence object so that we can reference it and cout it's content.
Explain what it returns: This function returns the ostream operator so we do cout << object in main.
*******************************************/

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h){
  
  if(h.num <= 0){
    o << "none";
  }
  for(int i=0; i<h.num; i++){ //for loop to go though our min heap
    o << h.ar[i] << " ";  
  }
  o << endl;
  return o;   //return 0
}

#endif
