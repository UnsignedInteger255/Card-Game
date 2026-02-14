#include <iostream>
using namespace std;

template <typename T> class Node {
    public:
        T data;
        Node<T>* next;
        Node<T>* prev;

        // Constructor
        Node(T data) {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
        
        void push(T data) {
            Node<T>* new_node = new Node<T>(data);
            
            new_node->next = this->next;
            new_node->prev = this;
        
            if (this->next != nullptr)
                this->next->prev = new_node;
            
            this->next = new_node;
        }

        void display() {
            Node<T>* current = this;
            while(current != nullptr) {
                cout << current->data;
                if (current->next != nullptr)
                    cout << "<->";
                current = current->next;
            }
            cout << endl;
        }
};

/*  Series of nodes connected by two-way pointers. 
    Operations: 
    - insertion, deletion at beginning/end/specific position
    - traversal/reverse */

/* Insertions functions */
template <typename T> void insertAtBeginning(Node<T>*& head, T data) {
            // Create a new node with the given data.
            Node<T>* newNode = new Node<T>(data);
            // Check if the doubly linked list is empty.
            if (head == nullptr) {
                head = newNode;
                return;
            }

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

template <typename T> void insertAtEnd(Node<T>*& head, T data) {
            Node<T>* newNode = new Node<T>(data);

            if (head == nullptr) {
                head = newNode;
                return;
            }

            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }

template <typename T> void insertAtPosition(Node<T>*& head, T data, int position) {            
            if (position < 1) {
                cout << "Invalid position (< 1)." << endl;
                return;
            }

            // Position 1 is the head
            if (position == 1) {
                insertAtBeginning(head, data);
                return;
            }

            // Create a new node
            Node<T>* newNode = new Node<T>(data);
            Node<T>* temp = head;

            for (int i = 1; i < position - 1 && temp != nullptr; i++) {
                temp = temp->next;
            }

            if (temp == nullptr) {
                cout << "Position greater than number of nodes." << endl;
                return;
            }

            // Update the next and previous pointers to insert the new node at the specified position.
            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != nullptr) {
                temp->next->prev = newNode;
            }
            temp->next = newNode;
}

/* Deletion functions */
template <typename T> void deleteFirst(Node<T>*& head) {
    // Check if the doubly linked list is empty
    if (head == nullptr) {
        cout << "The list is already empty." << endl;
        return;
    }

    // Update the head pointer and delete the first node
    Node<T>* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

template <typename T> void deleteLast(Node<T>*& head) {
    // Check if the doubly linked list is empty
    if (head == nullptr) {
        cout << "The list is already empty." << endl;
        return;
    }

    Node<T>* temp = head;
    // If there is only one node in the list
    if (temp->next == nullptr) {
        head = nullptr;
        delete temp;
        return;
    }

    // Update the head pointer and delete the first node
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    /*  Update the previous pointer of the second 
        last node and delete the last node*/
    temp->prev->next = nullptr;
    delete temp;
}

template <typename T> void deleteList(Node<T>*& head) {
    Node<T>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        if (temp != nullptr)
            delete temp;
    }
}

/* Print functions */
template <typename T> void printListForward(Node<T>*& head) {
    Node<T>* temp = head;
    cout << "Forward List: ";
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) {
            cout << " <-> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

template <typename T> void printListBackward(Node<T>*& head) {
    Node<T>* temp = head;
    cout << "Backward List: ";
    
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->prev != nullptr) {
            cout << " <-> ";
        }
        temp = temp->prev;
    }
    cout << endl;
}

/* Arithmetic functions */
template <typename T> int size(Node<T>*& head) {
    Node<T>* temp = head;

    int count = 0;
    while (temp->next != nullptr) {
        temp = temp->next;
        count++;
    }

    return count;
}

/* Data transfer functions */
/*  These functions will first traverse the list to the beginning 
    position and copy x nodes where x is the legnth */

template <typename T> 
Node<T>* copyPaste(Node<T>* head, int beginning = 1) {
    if (head == nullptr) {
        cout << "This list is empty." << endl;
        return nullptr;
    }

    if (beginning < 1) {
        cout << "Position outside of list" << endl;
        return nullptr;
    }

    // Move to beginning position
    Node<T>* temp = head;
    for (int i = 1; i < beginning && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position is outside of list" << endl;
        return nullptr;
    }

    // Create the first node of the copy
    Node<T>* copy = new Node<T>(temp->data);

    // Declare nextNode before using it
    Node<T>* nextNode = temp->next;
    Node<T>* newTemp = copy;

    while (nextNode != nullptr) {
        Node<T>* newNode = new Node<T>(nextNode->data);
        
        newTemp->next = newNode;
        newNode->prev = newTemp;
        
        newTemp = newNode;
        nextNode = nextNode->next;
    }

    return copy;
}

template <typename T> Node<T>* copyPaste(Node<T>* head, int beginning, int length) {
    if (head == nullptr) {
        cout << "This list is empty." << endl;
        return nullptr;
    }

    if (beginning < 1) {
        cout << "Position outside of list" << endl;
        return nullptr;
    }

    if (length < 1) {
        cout << "Invalid length" << endl;
        return nullptr;
    } 

    // Move to beginning position
    Node<T>* temp = head;
    for (int i = 1; i < beginning && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position is outside of list" << endl;
        return nullptr;
    }
    // Create the first node of the copy
    Node<T>* copy = new Node<T>(temp->data);

    Node<T>* nextNode = temp->next;  // DECLARE nextNode BEFORE using it
    Node<T>* newTemp = copy;


    int i = 1;
    while (nextNode != nullptr && i < length) {
        Node<T>* newNode = new Node <T>(nextNode->data); // Must be Node<T>
        
        newTemp->next = newNode;
        newNode->prev = newTemp;
        
        newTemp = newNode;
        nextNode = nextNode->next;
        i++;
    }

    return copy;
}

template <typename T> Node<T>* cutPaste(Node<T>* head, int beginning = 1) {
    Node<T>* current_node = head;
    // Move to beginning position
    for (int i = 1; i < beginning && current_node != nullptr; i++) {
        current_node = current_node->next;
    } 

    if (!current_node) {
        cout << "Attempted to access beyond list." << endl;
        return nullptr;
    }

    /*  If there is a previous node, set the previous node's next node to nullptr
        and the current node's prev node to nullpointer*/
    if (current_node->prev) {
        current_node->prev->next = nullptr;
        current_node->prev = nullptr;
    } else {
        // If there is no previous node, current node is at the head
        head = nullptr;
    }


    return current_node;
}
