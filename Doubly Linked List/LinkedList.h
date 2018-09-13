//
//  SkipList.h
//  Skip_List
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

// Copyright © 2018 (Chase Clarke, Email: cfclarke@bu.edu)

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

template <class T>
class LinkedList;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList();                                   // constructor
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
    //  where new node should be inserted in the bottom-most list
    bool insert(T data);                            // insert node with data, return true if inserted, false if exists
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
};


/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
    this->up = NULL;
    this->down = NULL;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}

/****** Implementation of linked list ******/

// Constructor of linked list
template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
}

// destructor of linked list
template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* temp = head;
    while(temp != nullptr) {
        temp=head->next;
        delete head;
        head=temp;
    } delete head;
}

// LinkedList search function
template<class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data) {
    bool right = false;
    bool left = false;
    
    //checking if iteration should be to left to right or if already at correct location
    if(location == nullptr || location->data == data) {return location;}
    else if (data > location->data) {right = true;}
    else if (data < location->data) {left = true;}
    
    //executing neccessary code given a direction of iteration
    if(right) {
        
        while(data > location->data  && location->next != nullptr) {
            location = location->next; //iterates to next element of the list
        } return location;
        
    } else { //if !right & != then must be left
        
        while(data < location->data && location->prev != nullptr) {
            location = location->prev; //iterates to next element of the list
        } return location;
    }
}

// insert function
template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data) {
    Node<T>* temp = new Node<T>(data);
    temp->data = data;
    temp->next= NULL;
    temp->prev = NULL;
    
    if( location == NULL){ //checking if list is empty
        head = temp;
        head->prev = NULL;
        head->next = NULL;
        return location;
        
    } else if(location != NULL & location->prev != NULL) { //checking if in center of list
        
        if (location->next == NULL & location->data < data) { //if at tail of list diff code needed
            temp->prev = location;
            location->next = temp;
            return (temp);
            
        } else {
            temp->next = location;
            location->prev->next = temp;
            temp->prev = location->prev;
            location->prev = temp;
            return (location);
        }
    } else /*if (location != NULL && location->prev == NULL)*/ { //checking if at head of list
        
        if (location->data < data) { //if at head diff code needed
            temp->next = NULL;
            temp->prev = location;
            location->next = temp;
            return location;
            
        } else {
            temp->prev = NULL;
            temp->next = location;
            location->prev = temp;
            head = temp;
            return location;
        }
    }
}

// Print linked list data
template <class T>
void LinkedList<T>::printData()
{
    if (head == nullptr)
    {
        cout << "Linked list is empty" << endl;;
        return;
    }
    
    head->printData();
    
    if (head->next == nullptr)
    {
        cout << endl;
        return;
    }
    
    Node<T>* currNode = head->next;
    Node<T>* prevNode = head;
    
    
    while (currNode->next != nullptr)
    {
        currNode->printData();
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    currNode->printData();
    cout << endl;
}

// Prints linked list with all nodes pointers
template <class T>
void LinkedList<T>::print()
{
    if (head == nullptr)
    {
        cout << "Linked list is empty" << endl;;
        return;
    }
    
    head->print();
    
    if (head->next == nullptr)
    {
        cout << endl;
        return;
    }
    
    Node<T>* currNode = head->next;
    Node<T>* prevNode = head;
    
    while (currNode->next != nullptr)
    {
        currNode->print();
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    currNode->print();
    cout << endl;
}

#endif /* LinkedList_h */


