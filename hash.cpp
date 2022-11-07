/************************
Templated created by Kazumi Slott
CS311

Your name: Ruben Cerda
Your programmer number: 7
Hours spent: 2
Any difficulties?: Was having difficulty manipulating pointers in the delete function
*********************/
#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <cstdlib>  
using namespace std;

//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

class entry //this is basically a node
{
  //What do you do if hashTbl needs to access the private members of entry?
  //If you don't say private or public, it is private by default.
  // friend class hashTbl;
  friend class hashTbl;
  string ID;
  string name;
  int age;
  double GPA;
  entry* next;
  //????? next; //points to the next entry

public:
  entry() { ID = name = "", age = -999, GPA = -999.0, next = NULL; }
  entry(const string& ID, const string& name, int age, double GPA ) { this->ID = ID, this->name = name, this->age = age, this->GPA = GPA, next = NULL; }
  string getID() const { return ID; }  
  string getName() const { return name; } 
  int getAge() const { return age; } 
  double getGPA() const { return GPA; } 
  entry* getNext() const { return next; } 
};

class hashTbl
{
  entry** table; //????? table;   //table points to a dynamic array. Each slot points to an entry, which points to the next entry, ...
  int size; //size of the array
public:
  hashTbl(int size);
  ~hashTbl();
  void put(entry* e); //add a new entry to the table
  entry* get(const string& key) const; //look up a key   
  entry remove(const string& key); //remove an entry
  entry** getTbl()const {return table;} //Return The Pointer To The Table  
  class underflow //exception class - used when key wasn't found
  {
    string message;
  public:
    underflow(const string& mes) { message = mes; }
    string getMessage() { return message; }
  };
};

//constructor
//s is the size of the table

/****************************************** 
Explain what this function does: This function creates a dynamic array that each slot holds a LL
Explain each parameter: This function takes in the size of the paramater that we choose to give.
Explain what it returns: this is a constructor, so it only initializes all elements to NULL.
*******************************************/ 
hashTbl::hashTbl(int s)
{
  size = s; //initialize size with s
  table = new entry*[s]; // make a dynamic array
  for(int i=0; i< s; i++){ //initiiaize each slot to NULL
      table[i] = NULL;
    }
  //set private member size
  //make a dynamic array that has s slots
  //put NULL in each slot of the array. Remember Each slot contains a pointer to an entry.
}

//destructor
/****************************************** 
Explain what this function does: This function deletes every entrie that has a linked list, it then destroys the dynamic array itself.
Explain each parameter: No parameters. 
Explain what it returns: This function purpose is to release all alocated memory
*******************************************/ 
hashTbl::~hashTbl()
{
  entry*slot; //loop through each slott
  entry*nex;  //to access the LL for each array slott
  for(int i=0 ; i<size; i++){ //loop through each slott
      slot = table[i];
      while(slot!=NULL){ //loop through the LL inside each slott
	  nex = slot->getNext();
	  delete slot;         //release nodes
	  slot = nex;
	}
    }
  delete [] table;  //delete the hashtable itself
  //you need to destroy everything created using new.
  //destroy all the entries belong to each slot of the table
  //don't forget to destroy the dynamic array
}

//insert an entry to the table
//e is a pointer to an entry
/****************************************** 
Explain what this function does: This function adds before to any node to the specific index we get when hashing
Explain each parameter: We use a pointer to a node object to add it to the entries
Explain what it returns: it's void it's only purpose is to add to the linked list slott.
*******************************************/ 
void hashTbl::put(entry* e)
{

  string key = e->getID(); //recive
  int index = hashNum(key) % this->size; //find index
  entry* cur = table[index]; //cur points to the index we calculated
  e->next = cur; //set e to point before current 
  table[index]= e; //set the entry to the begginning
  
  //This function is like LL::addFront() from CS211

  //string key = use ID for key 
  //int index = (call hashNum with key) % (table size); 
  //entry* cur = make cur point to the first entry

  //add the entry at the beginning of the list coming out of index	
}

//look up key and return the pointer to it. Assume keys are unique.
/****************************************** 
Explain what this function does: This function finds a node were looking for by using the index we used when hashing.
Explain each parameter: We use a const string& key to find the index were looking for in the array. 
Explain what it returns: it returns the current slott it was found.
*******************************************/ 
entry* hashTbl::get(const string& key) const
{

  int index = hashNum(key) % this->size; //find index
  entry* slot = table[index]; //make a node that points to the current slott that was found from index
  if(slot == NULL){ //first case when the first slott is NULL
    throw underflow(key);
  }
  while(slot !=NULL){ //loop through LL till we are able to find the key
    if(slot->getID() == key){ //found
      return slot; 
    }
    slot = slot->getNext();

  }
  if(slot == NULL){  //not found
    throw underflow(key);
  }
  return slot;
  
  //This function is like LL::search() from CS211

  /*
  if (the slot is empty )
      throw underflow(key);
  */

  //look for key in the linked list. Return the pointer to the entry with key.

  //After traversed the list, if key wan't found, throw exception just like above where the slot was empty. 
}

//remove the entry with key. Assume keys are unique.
/****************************************** 
Explain what this function does: This function removes a node in the LL by checking it's corresponing index and checking if the element even exists.
Explain each parameter: This function takes in a const string& key to use to find the index of the node we wish to delete.
Explain what it returns: It returns the object that we may have found and used for destructor to delete.
*******************************************/ 
entry hashTbl::remove(const string& key)
{
 
  
  //This function is like LL::remove() from CS211
  //Don't forget to return the entry that has been found
  int index = hashNum(key) % size;
  entry* slot = table[index];
  //No entry in hashtable location
  if(slot == NULL){
    throw underflow(key);
  }
  entry remove;
  entry* prev = NULL;
  while(slot != NULL)//if the slot is not empty
    {
      //if there is a match to remove
      if(slot == get(key))
	{
	  remove = *slot; //remove is a object that will hold the key that needs to be deleted by the destructor.
	  
	  //if only one entry
	  if(slot->next == NULL)//no need to worry about messing up the linked list
	    {
	       slot = NULL;//set the slot pointer to NULL
	    }
	  else//more than one entry
	    {
	      prev->next = slot->next;//set the previous of the slot to the next slot
	      slot = NULL;//set the slot pointer to NULL
	    }
	  return remove;
	}
      //no matching key found,so we need to increment 
      prev = slot;
      slot = slot->getNext();
    }
  //gets a no match founded in the list
  if(slot->getID() != key)
    {
      throw underflow(key);
    }
  
	   
  //This function is like LL::remove() from CS211

 //Don't forget to return the entry found

  /*
 if (the slot is empty)
   throw underflow(key);

 if (//traversed the list, but didn't find key)
   throw underflow();
  */
}

//well known hash function called djb2
//http://www.cse.yorku.ca/~oz/hash.html
//For explanation of bit shifting, http://www.cplusplus.com/forum/beginner/95670/
//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key)
{
  const char* cstr = key.c_str(); //converting C++ string to c-string. A c-string is a character array that is terminated by a '\0' (NULL terminator).
  
  unsigned long hash = 5381;
  int c;
  while (c = *cstr++) //checking each character until it reaches '\0'. When it reaches '\0', c gets the ascii number of '\0', which is 0. 0 means false -> getting out of while.
    {
      hash = ((hash << 5) + hash) + c;//hash * 33 + c;
    }
  return hash;
}

void showInfo(const entry& e);
void showTable(const int count[], const hashTbl& students);

const int SIZE =1009; //For closed addressing, you don't need to worry about load factor.                                                                    
                       //The table size still should be at least the number of items and also a prime number.                                                 
                       //There are 1000 people in the input file.
int main()
{
  //make a hash table object called students with SIZE slots 
  hashTbl students(SIZE);

  int count[SIZE] = {0}; //set all slots to 0. Used to see count in each index                                                                      

  ifstream fin;
  fin.open("hash.in");
  string id;
  string name;
  int age;
  double gpa;

  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      return 0;
    }

  //adding entries from the input file
  fin >> id >> name >> age >> gpa;
  while(fin)
    {
      count[hashNum(id)%SIZE]++;//trying to see how many entries go into each slot
      students.put(new entry(id, name, age, gpa));
      fin >> id >> name >> age >> gpa;
    }

  //show the statistic about the table
  showTable(count, students);

  //put entries into the table
  students.put(new entry("T1234567891", "Tom", 23, 4.0));
  students.put(new entry("F5432112345", "Fred", 45, 3.5));
  students.put(new entry("L1357915987", "Linsey", 48, 2.0));

  //searches and returns students in table without removing                                                                     
  try
    {
      cout << "trying to search" << endl;
      showInfo(*(students.get("P1429911332")));//middle at index 377                                                            
      showInfo(*(students.get("Y1098431884"))); //first entry at index 377                                                      
      showInfo(*(students.get("V1025438181"))); //last entry at index 377                                                       
      showInfo(*(students.get("A1234567891"))); //probably doesn't exist                                                        
      //search for key and show their info                                                                                      
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be found" << endl;
    }

  //Try to remove a student from table                                                                                         
  try                                                                                                                           
    {
      cout << "trying to remove" << endl;
      showInfo((students.remove("P1429911332"))); //3rd entry at index 377                                                      
      showInfo((students.remove("V1025438181"))); //last entry(now 4th) at index 377                                            
      showInfo((students.remove("Y1098431884"))); //first entry at index 377                                                    
      showInfo((students.remove("A1234567891"))); //probably it doesn't exist                                                   
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be removed" << endl;
    }

  return 0;
}

//Show the information about an entry
void showInfo(const entry& e)
{
  cout << e.getID() << " " << e.getName() << " " << e.getAge() << " " << e.getGPA() <<  endl;
}

//Show the statistic about the hash table
void showTable(const int count[], const hashTbl& students)
{
  //we want to know the highest, lowest and empty counts
  int lowest = 1001;
  int highest = -1;
  int empty = 0;
  int hi_i; //index of the highest count

  cout << "print table" << endl;
  for(int i = 0; i < SIZE; i++)
    {
      if(count[i] < lowest)
        lowest = count[i];
      if(count[i] > highest)
	{
	  highest = count[i];
	  hi_i = i;
	}
      if(count[i] == 0)
        empty++;

      cout << setw(3) << count[i];
      if((i+1)%50 == 0)//Show 50 numbers per line
        cout << endl;
    }
  cout << endl << endl << "lowest is " << lowest << " highest is " << highest << " empty is " << empty << endl;

  cout << "highest count is at " << hi_i << endl;
  //Show the entries at the index that has the highest count
  entry* p = students.getTbl()[hi_i];
  while(p != NULL)
    {
      showInfo(*p);
      p = p->getNext();
    }
  cout << endl;

}

