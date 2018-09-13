//
//  main.cpp
//  Skip_List
//
//  Created by Chase Clarke.
//  Copyright © 2018 Chase Clarke. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include "LinkeList.h"

int main(int argc, const char * argv[]) {

  LinkedList<char> *myLL = new LinkedList<char>();
  Node<char> *newNodeLoc;

  newNodeLoc = myLL->search(myLL->head, 'a');
  myLL->insert(newNodeLoc, 'a');

  newNodeLoc = myLL->search(myLL->head, 'c');
  myLL->insert(newNodeLoc, 'c');
 
  newNodeLoc = myLL->search(myLL->head, 'd');
  myLL->insert(newNodeLoc, 'd');

    
  newNodeLoc = myLL->search(myLL->head, 'f');
  myLL->insert(newNodeLoc, 'f');


  newNodeLoc = myLL->search(myLL->head, 'b');
  myLL->insert(newNodeLoc, 'b');
    
  newNodeLoc = myLL->search(myLL->head, 'e');
  myLL->insert(newNodeLoc, 'e');

  cout << "Linked list data: \n";
  myLL->printData();

  cout << "\n Linked List entire content: \n";
  myLL->print();

    return 0;
}
