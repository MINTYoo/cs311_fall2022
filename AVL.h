/****************
Template created by Kazumi Slott
CS311

Your name: Ruben Cerda
Your programmer number: 7
Hours spent?: 9 
Any difficulties?: I was struggling with tracking down pointers in the rotation functions and how to propertly rotate when the root is the violation
*****************/
#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>//for the BFT -- Breadth First Traversal Print Function
//#include <stack>//for the DFT -- Depth First Traversal Print Function
using namespace std;

//Check your stack_L_T.h if you don't know what to put here.
template <class T>//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
class AVL;//used in order to access the private members

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>//???????????  //make it a templare class
class Node
{
  friend class AVL<T>; //AVL wants to access private members of Node
 private:
  T el;
  Node<T>* right;
  Node<T>* left;
  Node<T>* up;
  int BF;
 public:
Node() {right = left = up = NULL; BF = 0;}; //default constructor. set right and left to NULL
Node(const T& e){el = e; right = left = up = NULL; BF = 0;}; 
T getEl() const {return el;} //returns el
};

template <class T>//Make it a template class
class AVL
{
private:
Node<T>* root;//???? root; //check stack_L_T.h to see how declared top
//void insertNodeR(Node<T>*& p, const T& e);
void inOrderPrint(Node<T>* p);
void destroy(Node<T>* p);
int getMaxLength(Node<T>* p);
Node<T>* rightRotation(Node<T>* P);
Node<T>* leftRotation(Node<T>* P);
void balanceTree(Node<T>* newNode);
Node<T>* updateBF(Node<T>* Q);
public:
AVL() {root = NULL;} //implement constructor here --> set the root to be NULL
~AVL(); //destructor
void insertNodeI(const T& e);
void inOrderPrint();
void BFTprint();
int getMaxLength();
};

//implement the member functions in the header if you are making a template class

//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
AVL<T>::~AVL()
{
destroy(root);//traverses through the tree to delete the root
}

template <class T>//template class function
void AVL<T>::destroy(Node<T>* p) //private function. WHY?
{
if(p == NULL)//if there are no roots to be checked
  return;
destroy(p->left);//goes to the left side of the tree and deletes that side
destroy(p->right);//goes to the right side of the tree and deletes that side
delete p;//delete the pointer so it removes the element and the root/subroot inside the tree
//destroy all nodes
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.

template <class T>
void AVL<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>;//make a new node.  Check stack_L_T.h to see how you made a new node.
 newNode->el = e;//set the passed element with the newNode el
 Node<T>* p = root;//set the pointer to the root
 Node<T>* parent = NULL; //points to the parent of p. 
 while(p != NULL)
  {
//parent points to the parent node while p points to the left or right child.
parent = p; 
 if(e < p->el)//if the element passed is less than the element inside of the tree
   p = p->left;//goes to the left side of the tree
 else //p->el <= e -- if the element in the tree is less than or equal to the element passed
   p = p->right;//goes to the right side of the tree
  }

 if(parent == NULL) //tree is empty
  {
    root = newNode;//set the root with the added new node with an element & no need to balance 1 node
  }
 else if(e < parent->el) //insert a child as the parent's left child
   {
     parent->left = newNode;//set the parent's left with an added node
     newNode->up = parent;//point the new node's up with the parent since it is new
     balanceTree(newNode);//set that part of the tree with new node added
   }
 else //parent->el <= e //insert a child as the parent's right child
   {
     parent->right = newNode;//set the parent's right child as the added node
     newNode->up = parent;//point the new node's up with the parent
     balanceTree(newNode);//set that part of the tree with new node added
   }
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void AVL<T>::inOrderPrint(Node<T>* p)
{
  if(p == NULL)//if there are no more elements to check
    return;
  inOrderPrint(p->left);//get the elements from the left
  cout << p->el << " " << p->BF << "-->";
  inOrderPrint(p->right);//get the elements from the right
}

template <class T>
void AVL<T>::BFTprint()//this function is used for printing out nodes based on its respective level or depth.
{
  //Use the library's queue.
  //Make sure to include <queue> at the top
  Node<T>* temp = root;//set the root to a p pointer
  queue<Node<T>*> q;//create a queue obj of pointers to Nodes
  //if(root == NULL)//if the BST is empty
  //return;
  if(temp != NULL)//if the tree is not empty
    //{
    q.push(temp);//push root in the queue
  //NOTICE
  while(!q.empty())//if the AVL is not empty
    {
      temp = q.front();//front() gives you the front element but it doesn't remove it from the queue
      if(temp != NULL)//if the tree is not empty
	{
	  if(temp->up == NULL)//if the up pointer is empty
	    cout << temp->el << " " << temp->BF << " -->";//outputs the element and the balance factor that is in the tree
	  else// not empty 
	    cout << temp->el << " " << temp->BF << " " << temp->up->el << "-->";//used to output the elements that are from the root and upper to check the balance factor within the avl tree
	  q.pop();//pops the top element of the tree
	    
	  if(temp->left != NULL)//if the root's left child has any pointers open
	    q.push(temp->left);//push to the left side
	  if(temp->right != NULL)//if the root's right has any nodes nodes available
	    q.push(temp->right);//push to the right side
	}
    }
}

template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)//NEW FUNC -- newNode points to the newly added node
{
  Node<T>* ptr = updateBF(newNode);//call updateBF()
  if(ptr == NULL)//if updateBF() returns NULL, no need to balance the tree
    {
      return;//if the tree is already balanced
    }
  else if(ptr != NULL) //not balanced
    {
      Node<T>* parent = ptr->up;//set the parent of the ptr's up pointer
      Node<T>* temp;//needed when having two rotations on the violations
        if(ptr->BF == 2 && ptr->left != NULL && ptr->left->BF == 1)
	{
	  //right rotation must be made when it is this violation
	  ptr = rightRotation(ptr);
	}
      else if(ptr->BF == 2 && ptr->left != NULL && ptr->left->BF == -1)//LR violation
	{
	  //makes a left then right rotation for this violation
	  temp = leftRotation(ptr->left);//have  ptr point to the left to make the rotation
	  temp->up = ptr;//have that node's up be the violation
	  ptr->left = temp;//let the violation node point directly to the temp
	  ptr = rightRotation(ptr);
	}
      else if(ptr->BF == -2 && ptr->right != NULL && ptr->right->BF == 1)//RL
	{
	  //makes a right then left rotation
	  temp = rightRotation(ptr->right);
	  temp->up = ptr;
	  ptr->right = temp;
	  ptr = leftRotation(ptr);
	}
      else if(ptr->BF == -2 && ptr->right != NULL && ptr->right->BF == -1)//RR
	{
	  //make a left rotation when its this violation
	  ptr = leftRotation(ptr);
	}

      if(parent == NULL)//if the root was the violation 
	{
	  ptr->up = NULL;//set this to be empty
	  root = ptr;//since it was at the root, this will be the new root 
	}
      else
	{
	  if(parent != NULL){
	    if(parent->right == ptr)//if the ptr root points to a new child
	      parent->right = ptr;
	    else
	      parent->left = ptr;
	  }
	  //update the up pointer once it has been made
	  ptr->up = parent;
	}      
    }
}

template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* P)//NEW
{
  Node<T> *temp = P->left;   //Hold pointer to temp
  P->left = temp->right;      // Move temp's right child to left child 
  if(temp->right != NULL)      // If the right child does exist
    temp->right->up = P;// Reset right child's parent
  if(P->up == NULL)       // If p was root
    {
      root = temp;      // Make temp the root
      temp->up = NULL;   // Root has no parent
    }
  else if(P->up->left == P) // If was the left child of its' parent
    P->up->left = temp;   // Make temp the new left child
  else               // If p was the right child of its' parent
    P->up->right = temp;// Make temp the new right child

  temp->right = P;         // Move n to right child of temp
  P->up = temp;         // Reset p parent

  P->BF = getMaxLength(P->left) - getMaxLength(P->right);
  temp->BF = getMaxLength(temp->left) - getMaxLength(temp->right);

  return temp;//returns the rotation of the right
}

template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* P)//NEW
{
  Node<T> *temp = P->right;   //Hold pointer to p's right child
  P->right = temp->left;      // Move temp 's left child to right child of p
  if(temp->left != NULL)      // If the left child does exist
    temp ->left->up = P;// Reset the left child's parent
  if(P->up == NULL)       // If p was the root
    {
      root = temp;      // Make temp the new root
      temp->up = NULL;   // Root has no parent
    }
  else if(P->up->left == P) // If p was the left child of its' parent
    P->up->left = temp;   // Make temp the new left child
  else               // If p was the right child of its' parent
    P->up->right = temp;// Make temp the new right child

  temp->left = P;         // Move p to left child of temp
  P->up = temp;         // Reset p's parent

  temp->BF = getMaxLength(temp->left) - getMaxLength(temp->right);
  P->BF = getMaxLength(P->left) - getMaxLength(P->right);

  return temp;
}

template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)//NEW
{
  Node<T>* ptr = NULL;
  Node<T>* parent = NULL;//parent of Q

  if(Q->up != NULL)//if the passed in node is not empty
    parent = Q->up;
    
  if(Q == parent->left)//if the passed in root is equal to the left child
    {
      parent->BF++;//increment the balance factor by one
    }
  else//if the passed in root is equal to the right child
    {
      parent->BF--;//decrement the balance factor by one
    }

  while(parent != root && (parent->BF > -2 && parent->BF < 2))
    {
      Q = parent;
      parent = parent->up;
  
      if(Q->BF == 0)
	return ptr;

      if(Q->el < parent->el && Q == parent->left)
	parent->BF++;
      else
	parent->BF--;
    }
      
  if(parent->BF == 2 || parent->BF == -2)
    ptr = parent;
  return ptr;
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int AVL<T>::getMaxLength()
{
  return getMaxLength(root);//used in order to access root
}

template <class T>
int AVL<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p == NULL)//if the tree is empty
    return 0;
  else// there are nodes inside of the tree
    {
      int left, right;
      left = getMaxLength(p->left) + 1;//includes the elements from the left side of the tree and in the root
      right = getMaxLength(p->right) + 1;//includes the elements from the right side of the tree and in the root
      if(left >= right)//if the left side has the greatest number of elements than the right side
	return left;//returns the left side of the tree
      if(right > left)//if the right side has the greatest number of elements than the left side
	return right;//returns the right side of the tree
    }
}
#endif
