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
            Node* new_node = new Node<T>(data);
            
            new_node->next = this->next;
            new_node->prev = this;
        
            if (this->next != nullptr)
                this->next->prev = new_node;
            
            this->next = new_node;
        }

        void display() {
            Node* current = this;
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
void insertAtBeginning(Node*& head, T data) {
            // Create a new node with the given data.
            Node* newNode = new Node(data);
            // Check if the doubly linked list is empty.
            if (head == nullptr) {
                head = newNode;
                return;
            }

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

void insertAtEnd(Node*& head, T data) {
            Node* newNode = new Node(data);

            if (head == nullptr) {
                head = newNode;
                return;
            }

            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }

void insertAtPosition(Node*& head, T data, int position) {            
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
            Node* newNode = new Node(data);
            Node* temp = head;

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
void deleteFirst(Node*& head) {
    // Check if the doubly linked list is empty
    if (head == nullptr) {
        cout << "The list is already empty." << endl;
        return;
    }

    // Update the head pointer and delete the first node
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void deleteLast(Node*& head) {
    // Check if the doubly linked list is empty
    if (head == nullptr) {
        cout << "The list is already empty." << endl;
        return;
    }

    Node* temp = head;
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

void deleteList(Node*& head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        if (temp != nullptr)
            delete temp;
    }
}

/* Print functions */
void printListForward(Node*& head) {
    Node* temp = head;
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

void printListBackward(Node*& head) {
    Node* temp = head;
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
int size(Node*& head) {
    Node *temp = head;

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

Node* copyPaste(Node*& head) {
    if (head == nullptr) {
        cout << "This list is empty." << endl;
        return nullptr;
    }

    if (head->next == nullptr) {
        Node* copy = new Node(head->data);
        return copy;
    }

    Node* copy = new Node(head->data);
    Node* nextNode =  head->next;
    Node* newTemp = copy;

    while (nextNode != nullptr) {
        Node* newNode = new Node(nextNode->data);
        
        newTemp->next = newNode;
        newNode->prev = newTemp;
        
        newTemp = newNode;
        nextNode = nextNode->next;
    }

    return copy;
}

Node* copyPaste(Node* head, int beginning) {
    if (head == nullptr) {
        cout << "This list is empty." << endl;
        return nullptr;
    }

    if (beginning < 1) {
        cout << "Position outside of list" << endl;
        return nullptr;
    }

    // Move to beginning position
    Node* temp = head;
    for (int i = 1; i < beginning && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position is outside of list" << endl;
    }

    Node* copy = new Node(temp->data);
    Node* nextNode =  temp->next;
    Node* newTemp = copy;

    while (nextNode != nullptr) {
        Node* newNode = new Node(nextNode->data);
        
        newTemp->next = newNode;
        newNode->prev = newTemp;
        
        newTemp = newNode;
        nextNode = nextNode->next;
    }

    return copy;
}

Node* copyPaste(Node* head, int beginning, int length) {
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
    Node* temp = head;
    for (int i = 1; i < beginning && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position is outside of list" << endl;
    }

    Node* copy = new Node(temp->data);
    Node* nextNode =  temp->next;
    Node* newTemp = copy;

    int i = 1;
    while (nextNode != nullptr && i < length) {
        Node* newNode = new Node(nextNode->data);
        
        newTemp->next = newNode;
        newNode->prev = newTemp;
        
        newTemp = newNode;
        nextNode = nextNode->next;
        i++;
    }

    return copy;
}

Node* cutPaste(Node* head) {
    Node* newNode = copyPaste(head, 1);
    deleteList(head);
    return newNode;
}

int main() {
    Node* head = new Node(10);
    insertAtBeginning(head, 20);
    insertAtBeginning(head, 30);
    insertAtBeginning(head, 40);
    insertAtBeginning(head, 50);
    insertAtBeginning(head, 60);
    insertAtEnd(head, 0);

    cout << "Original list's size: " << size(head) << endl;
    printListForward(head);
    
    Node* clone = cutPaste(head);
    cout << "Copy's size: " << endl;
    printListForward(clone);

    cout << endl << "Original list's size:" <<size(head) << endl;
    printListForward(head);
   
    return 0;
}
