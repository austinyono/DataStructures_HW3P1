//CS311 Yoshii Linked List class

//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes

//EMACS HINT:
//  You can copy from a Word document to emacs (contrl-right click)
//  cntr-K cuts and cntr-Y pastes
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Austin Yono
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include"llist.h" 

llist::llist() { 
     
  cout << "... in llist constructor..." << endl; 
  
  Front = NULL;
  Rear = NULL;
  Count = 0;
}

llist::~llist() {
 
  cout << ".... in llist destructor..." << endl;
     
  el_t num;

  while (isEmpty() == false) {
    deleteFront(num);
  }
}

// PURPOSE: returns true if Front and Rear are pointing to NULL and Count = 0 
bool llist::isEmpty() {
     
  if (Front == NULL && Rear == NULL && Count == 0) {
    return true;
  } else {
    return false;
  }
} 

// PURPOSE: displays each element of the list starting from Front, enclosed in [ ]
void llist::displayAll() { 

  Node* P = Front;// local pointer P, points to front of list

  if (isEmpty()) {// call isEmpty(), print EMPTY if isEmpty() returns true
    cout << "[ EMPTY ]\n";
  } else {
    cout << "[ ";
    while (P != NULL) {// while P does not point to NULL, print elements from listi horizontally in [ ] with spaces between elements
      cout << P -> Elem << " ";
      P = P -> Next;
    }
    cout << "]\n";
  }

} 
  
// PURPOSE: adds a new node to the rear of the list and puts a new element in the new node
// PARAMETER provide the element (NewNum) to be added
void llist::addRear(el_t NewNum) {

  if (isEmpty()) {// if list is empty, create a new node with Front and Rear pointing to it. Put NewNum in the Elem field, update Count
    Front = new Node();
    Front -> Elem = NewNum;
    Rear = Front;
    Rear -> Next = NULL;
    Count++;
  } else {// add a new node at the rear, put NewNum in the Elem field, update Count
    Rear -> Next = new Node();
    Rear = Rear -> Next;
    Rear -> Elem = NewNum;
    Rear -> Next = NULL;
    Count++;
  }
}

// PURPOSE: adds a new node to the front of the list and puts a new element in the new node
// PARAMETER: provide the element (NewNum) to be added
void llist::addFront(el_t NewNum) { 
     
  if (isEmpty()) {// if list is empty, create a new node with Front and Rear pointing to it. Put NewNum in the Elem field, update Count
    Front = new Node();
    Front -> Elem = NewNum;
    Rear = Front;
    Rear -> Next = NULL;
    Count++;
  } else {// add a new node to the front, put NewNum in the Elem field, update Count
    Node* Temp = new Node();
    Temp -> Elem = NewNum;
    Temp -> Next = Front;
    Front = Temp;
    Count++;
  }
}

// PURPOSE: removes the front node and element from the list
// PARAMETER: provide a holder (OldNum) for the removed element (passed by ref)
void llist::deleteFront(el_t& OldNum) { 
     
  if (isEmpty()) {// if list is empty, throw underflow error
    throw Underflow();
  } else if (Count == 1) {// if list contains one element, pass the front node element to OldNum. remove the front node, Front & Rear = NULL, Count is updated
    OldNum = Front -> Elem;
    delete Front;
    Front = NULL;
    Rear = NULL;
    Count--;
  } else {// pass front node element to OldNum, create second node, point to fronts next element, delete Front, update Count
    OldNum = Front -> Elem;
    Node* Second;
    Second = Front -> Next;
    delete Front;
    Front = Second;
    Count--;
  }
} 

// PURPOSE: removes the rear node and element from the list
// PARAMETER: provide a holder (OldNum) for the removed element (passed by ref)
void llist::deleteRear(el_t& OldNum) {

  if (isEmpty()) {// if list is empty, throw underflow error
    throw Underflow();
  } else if (Count == 1) {// if list contains one element, pass rear node element to OldNum, remove rear node, Front & Rear = NULL, Count is updated
    OldNum = Rear -> Elem;
    delete Rear;
    Front = NULL;
    Rear = NULL;
    Count--; 
  } else {// pass rear node element to OldNum, create local pointer P, points to front of list, move P to one beforerear of list. Delete Rear and set Rear to P and Rear next to NULL, update Count
    OldNum = Rear -> Elem;
    Node* P;
    P = Front;
    while (P -> Next != Rear) {
      P = P -> Next;
    }
    delete Rear;
    Rear = P;
    Rear -> Next = NULL;
    Count--;
  }
} 

// Utility Function to move a local pointer to the Ith node
void llist::moveTo(int I, Node*& temp) { // moves temp I-1 times

  for (int j = 1; j <= I - 1; j++) {
    temp = temp -> Next;
  }
}

// PURPOSE: removes the Ith node and element from the list
// PARAMETER:provide the position (I) and a holder (OldNum) for the removed element (passed by ref)
void llist::deleteIth(int I, el_t& OldNum) { 

  Node* P = Front;// local pointer P, points to front of list

  if (I > Count || I < 1) {// if I is greater than current Count or less than 1, throw out of range error
    throw OutOfRange();
  } if (I == 1) {// if I = 1, call deleteFront function to remove front node and element
    deleteFront(OldNum);
  } else if (I == Count) {// if I = Count, call deleteRear function to remove rear node and element
    deleteRear(OldNum);
  } else {// normal case: calls moveTo function, passes I - 1 and pointer P. removes Ith node and element, Count is updated
    moveTo(I-1, P);  
    Node* Q = P -> Next;
    P -> Next = Q -> Next;
    delete Q;
    Count--;
  }

} 

// PURPOSE: adds a new node and element at the Ith position in the list
// PARAMETER: provide the position (I) and the element (NewNum) to be added
void llist::insertIth(int I, el_t newNum) { 

  Node* P = new Node;    // local pointer P, points to a new node
  P -> Elem = newNum;
  P -> Next = NULL;

  if (I > (Count + 1) || I < 1) {     // if I is greater than current Count + 1 or less than 1, throw out of range error
    throw OutOfRange();
  } if (I == 1) {// if I = 1, call addFront function to add front node and element
    addFront(newNum);      
  } else if (I == (Count + 1)) {// if I = Count + 1, call addRear function to add rear node and element
    addRear(newNum);
  } else {// normal case: create pointer Q, point to front of list, calls moveTo, passes I - 1 and pointer Q. Adds Ith node and element, Count is updated
    Node* Q = Front;
    moveTo(I-1, Q);
    P -> Next = Q -> Next;
    Q -> Next = P;
    Count++;
  }

} 

// PURPOSE: Copy Constructor to allow pass by value and return by value of a llist
// PARAMETER: provide a linked list (passed by ref)
llist::llist(const llist& Original) { 
     
  Front = NULL;
  Rear = NULL;
  Count = 0;
  Node* P;
  P = Original.Front;

  while (P != NULL) {
    this -> addRear(P -> Elem);
    P = P-> Next;
  }
}

// PURPOSE: Overloading of = (returns a reference to a llist)
// PARAMETER: provide a linked list (passed by ref)
llist& llist::operator=(const llist& OtherOne) { 

  el_t x;

  if (&OtherOne != this) {
    while (!this -> isEmpty()) {
      this -> deleteRear(x);
    }
    Node* P;
    P = OtherOne.Front;
    while (P != NULL) {
      this -> addRear(P -> Elem);
      P = P -> Next;
    }
  }
  return *this;
} 
