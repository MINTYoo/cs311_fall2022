/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: Sort a linked list with type string by looking at the rightmost index to the leftmost index.
Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 2
Any difficulties?: Finding how to add to the array of linked list objects using the radixsort function.
************************************/

#include <iostream>
#include <fstream>

using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};

LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s); //the new node has NULL in the next field.

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at the end of this list
/****************************************** 
Explain what this function does: This function is to add to the bucket linked list array.
Explain each parameter: Theirs a pointer parameter to be able to do add before and after node operations.
Explain what it returns: It's void, only purpose it to insert a node.
*******************************************/ 
void LL::addRear(Node* p)
{
  if(empty())//You need a special case when the list is empty
    {
      front = rear = p;//set the front and rear to the pointed node
    }
  //you don't need to place NULL in the next field of the last node of this list
  else  //if there are nodes inside of the heap memory
    {
      rear->next = p;//set the rear's next to the pointer
      rear = rear->next;//have the rear be assigned after the previous rear's next
    }
  rear->next = NULL;
  num++;
  //don't forget to increment num
  //Don't make a new node.

  //You need a special case when the list is empty

  //Don't forget to place NULL in the next field of the rear node of this list.

  //don't forget to increment num

  //Note: this function should have complexity O(1). There is no loop required. 
      }

//Implement this function
//appending another linked list at the end of this linked list 

/****************************************** 
Explain what this function does: This function appends the current bucket position to the ALL linked list in the order it went in.
Explain each parameter: We use a const pass by refernce object to be able to reference the data members. 
Explain what it returns: It doesn't have a return, it only adds to the original liked list.
*******************************************/ 
void LL::append(const LL& other)
{
  if(empty()){                 //if empty then set front and rear equal to the object
    this->front = other.front;
    this->rear = other.rear;
  }
  else{                       //else link the bucket LL with the ALL linked list
    this->rear->next = other.front;
    this->rear = other.rear;
  }
  this->num += other.num; //Don't forget to update num of this list

  //Note: this function should have complexity O(1). There is no loop required. 
}

void radixSort(LL& all);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, LL b[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  radixSort(all);
  cout << "Final result ----" << endl;
  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
/****************************************** 
Explain what this function does: This functions uses two pointers that adds to the bucket LL array and traverses the all LL. For each pass we need to get the position that the last chracter has by finding it's correspondiong alphabet index and adding it while using combine as a helper function.
Explain each parameter: This function parameter is a LL pass by refrence object that we use to traverse and add using comnineLISTS().
Explain what it returns: This function is void, it's only purpose is to sort.
*******************************************/ 
void radixSort(LL& all)
{

  LL buckets[ALPHABET]; // bucket[0] is for 'a'. There are 26 buckets.
  int pos = LEN - 1;
  int i, j;
  Node *front;  //two pointers to add to the bucket list and traverse the all linked list
  Node *cur;
  for (i = pos; i >= 0; i--) { //number of passes to traverse each character right to left
    for (front = all.begin(), cur = all.begin(); front != NULL; front = cur) { 
      cur = all.goToNext(cur); //move current so the loop will eventually be false 
      int index = front->getElem()[i] - 'a'; //find position for bucket array
      buckets[index].addRear(front); //add to bucket array
    }
    combineLists(all, buckets); //combine and clear bucket array
  }
}
  //Each slot of the buckets array is a LL object.
  //??? buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.   

  //checking each place
  //To go through each string in all list, check printLL() to see how to iterate
  //go to the correct bucket depending on the letter at the current place and add the node from the all list at the end of the bucket 

 
//Implement this function
//combining all lists from buckets
/****************************************** 
Explain what this function does: this function goes through the buckets LL array and inserts it back to the ALL LL. But it firsts clears the ALL LL to be able to set the current pass we have of inserting to the buckets LL array. It then clears the bucket LL array to be used in the next pass.
Explain each parameter: This function uses a LL object and LL array object to refrence when clearing and adding to the new ALL LL.
Explain what it returns: This function is void, it's only purpose is to clear and add to the LL object.
*******************************************/ 
 void combineLists(LL& all, LL buckets[])
{

  all.clear();                      //clear the current ALL linked list
  for(int i=0; i < ALPHABET; i++){ // for loop to traverse 
    all.append(buckets[i]);       //append all nodes from the correspodning bucket position to ALL LL
    buckets[i].clear();           //clear the bucket and move on
  }
   //call clear() to reset the all list. All the nodes went to correct buckets already.
  //populate the all list by combining the lists from the buckets by calling append()
  //reset each list in b[i] by calling clear(). All the nodes were moved to the all list already.
}

//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  fstream fin;
  fin.open("radix.in");
  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      return; //quits the program if the input program doesn't exist.
    }

  fin >> s;
  while(fin)
    {
      all.addRear(s);
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  int i;
  Node* p;

  //iterate l from the first node to last node
  for (i = 0, p = l.begin(); i < l.size(); i++, p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

