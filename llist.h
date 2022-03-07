//CS311 Yoshii
//INSTRUCTION:
//Llist class - header file template 
//You must complete the ** parts and then complete llist.cpp
//Don't forget PURPOSE and PARAMETERS 

// =======================================================
// HW#: HW3P1 llist
// Your name: Austin Yono
// Compiler:  g++ 
// File type: headher file  llist.h
//=======================================================

// alias el_t : element type definition
typedef int el_t;

//a list node is defined here as a struct Node for now
struct Node
{
  el_t Elem;   // elem is the element stored
  Node *Next;  // next is the pointer to the next node
};
//---------------------------------------------------------

class llist
{
  
 protected:
  Node *Front;       // pointer to the front node
  Node *Rear;        // pointer to the rear node
  int  Count;        // counter for the number of nodes

  // untility function to move to a specified node position
  void moveTo(int, Node*&);
  
 public:
  // Exception handling classes 
  class Underflow{};
  class OutOfRange{};  // thrown when the specified Node is out of range

  llist ();     // constructor to create a list object
  ~llist();     // destructor to destroy all nodes
  
  //**
  bool isEmpty();
    
  //**
  void displayAll();

  //**
  void addFront(el_t);
    
  //**
  void addRear(el_t);

  //**
  void deleteFront(el_t&);
    
  //**
  void deleteRear(el_t&);
    
  //**
  void deleteIth(int, el_t&);  // calls moveTo

  //**    
  void insertIth(int, el_t);   // calls moveTo

  //Copy Constructor to allow pass by value and return by value of a llist
  llist(const llist&);
  
  //Overloading of = (returns a reference to a llist)
  llist& operator=(const llist&); 

};
