# Node.cpp
## Node Object
* template data type
* doubly linked: prev, next
## Insertion Functions
Allocate and link new Node object to the head node 
### insertAtBeginning()
* Add a new node of data type T before the current node
### insertAtEnd()
* Traverse all nodes before adding new node
* Add a new node of data type T after the current node
### insertAtPosition()
* Traverse a specified number of nodes (int position) before adding new node
* Position is 1-based, the first node is at position 1, entering a position lesser than 1 is invalid
* Add a new node of data type T after the current node
## Deletion Functions
### deleteFirst()
* delete the first node and set the node after it as the first node.
### deleteLast()
* Traverse all nodes before deleting the last node
### deleteList()
* Delete the whole list
## Arithmetic Functions
### size()
* traverse to the end of the list, return how many nodes have traversed
## Data Transfer Functions
