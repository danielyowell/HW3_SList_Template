//
// This is the template for HW3. 
// We will implement a singly linked list (SLL) class and sort it. 
// 
// The node class is defined for you. 
// The singly linked list (SLL) class is partly defined. 
// Do not change the existing definitions. 
// 
// You have two major tasks: 
// 1. Complete five member functions of the SLL class. 
// 2. Complete merge sort based on the SLL data structure. 
// Detailed instructions are given below. 
// 
// Tip: to facilitate debugging, you may first implement a simple 
// add function (e.g., only add to head). This allows you to quickly 
// construct a list and test/debug other functions.
//
// 

#include <iostream>
using namespace std;

// -----------------------
// -----------------------
// Node Class Definition 
// -----------------------
// -----------------------
class Node {
private:
    int data; // data contained in this node
    Node* link_next; // pointer to next node
public:
    void SetData(int x);
    int GetData();
    void SetLink_Next(Node* ptr); // passes link_next a pointer to the next node
    Node* GetLink_Next(); // returns the pointer to the next node
    Node(); // constructor
};
Node::Node() {
    data = 0; // default data
    link_next = NULL; // by default, a node is created as an end node, which is why link_next points to NULL
}
void Node::SetData(int x) {
    data = x;
}
int Node::GetData() {
    return data;
}
void Node::SetLink_Next(Node* ptr) {
    link_next = ptr;
}
Node* Node::GetLink_Next() {
    return link_next;
}

// -------------------------------------
// -------------------------------------
// Singly Linked List Class Definition 
// -------------------------------------
// -------------------------------------
// The following is a partly defined singly linked class.  
// Its only private member is a head pointer -- you cannot add others. 
// It has multiple public member functions. 
// Four member functions are given to you.  

class SList {
private:
    Node* head;
    int size = 0; // DY: I added this. Should it be 0 or 1???
public:
    // The following four functions are given to you. 
    // The SetHead and GetHead functions are only useful for merge sort.
    SList();
    void Print();
    void SetHead(Node* ptr);
    Node* GetHead();

    // You need to complete the following five functions.

    // *************
    // 1. GetSize()
    // *************
    // This function returns the number of nodes in the list. 
    // Below is an example. 
    // 
    // Example: 
    // If list = 5, 7, 1, 3, 
    // then GetSize() returns 4. 
    
    int GetSize() {
        return size;
    };

    // *************************
    // 2. LinearSearch(int key)
    // *************************
    // This function performs linear search on the list with the given key.
    // If key is not found or the list is empty, return -1. 
    // If key is found, return location of the node holding that key. 
    // Location will start from 0 and ends at n-1. 
    // Below is an example. 
    // 
    // Example: 
    // If list = 5, 7, 1, 3, then  
    // LinearSearch(5) returns 0. 
    // LinearSearch(1) returns 2. 
    // LinearSearch(10) returns -1. 
    
    int LinearSearch(int key) {
        Node* SearchNode = GetHead(); // start at head
        int i = 0;
        cout << "Looking for: " << endl;
        while (SearchNode->GetLink_Next() != NULL) { // keep searching until null pointer reached
            if (SearchNode->GetData() == key) {
                cout << "Found: " << SearchNode->GetData() << endl;
                return i;
            }
            else {
                cout << "Not found: " << SearchNode->GetData() << endl;
                i++;
                SearchNode = SearchNode->GetLink_Next(); // set SearchNode to the next node in the list
            }
        }
        return -1; // could not find key in list
    };

    // *************************
    // 3. Add(int val, int idx)
    // *************************
    // This function adds a node with data "val" at location "idx". 
    // Here, "idx" starts from 0 (head node) and ends at n-1 (tail node). 
    // If the input "idx" is bigger than n-1, then add node to the tail. 
    // Below are three examples. 
    // 
    // Example 1: 
    // If list = 5, 7, 1, 2. 
    // If we run Add(3,2), 
    // then new list = 5, 7, 3, 1, 2. 
    // 
    // Example 2: 
    // If list = 5, 7, 1, 2. 
    // If we run Add(3,0), 
    // then new list = 3, 5, 7, 1, 2. 
    // 
    // Example 3:  
    // If list = 5, 7, 1, 2. 
    // If we run Add(3,7) 
    // then new list = 5, 7, 1, 2, 3. 
    // (Here, "7" is bigger than n-1, so add "3" to the tail.)  
    
    void Add(int val, int idx) {
        
        Node* newNode = new Node();
        newNode->SetData(val);
        cout << "New node with value " << newNode->GetData() << endl;

        if (head == nullptr) { // if there is no head
            head = newNode; // set newNode as the head
        }
        else if (idx > size - 1) { // node goes at end of list
            
            cout << "   Node goes at end of list" << endl;
            Node* temp = head;
            cout << "   head is " << temp->GetData() << endl;

            while (temp->GetLink_Next() != NULL) {
                temp = temp->GetLink_Next();
                cout << "   iterating thru list, current data: " << temp->GetData() << endl;    
            }

            cout << "   next node is null." << endl;
            temp->SetLink_Next(newNode);
            newNode->SetLink_Next(NULL); // shouldn't be necessary, but just in case
            
            cout << "   SUCCESSFULLY ADDED NODE TO END OF LIST (large index)" << endl;

        }
        else { // add node somewhere before end of list
            cout << "   Add node somewhere before end of list" << endl;
            Node* temp = head;
            for (int i = 0; i < idx; i++) {
                temp = temp->GetLink_Next();
                cout << "   iterating thru list, current data: " << temp->GetData() << endl;
            }
            
            cout << "   temp node represents node at index; has value " << temp->GetData() << endl;
            cout << "   newNode has value " << newNode->GetData() << endl;
            cout << "   We want to insert newNode where temp is and have it connect to temp" << endl;
            
            /*
            CASE 1: temp points to another node
            - Make newNode point to temp->next
            - Make temp point to newNode
            - Swap values of temp and newNode
            */

            if (temp->GetLink_Next() != NULL) {
                newNode->SetLink_Next(temp->GetLink_Next());
                temp->SetLink_Next(newNode);

                int x = newNode->GetData();
                newNode->SetData(temp->GetData());
                temp->SetData(x);
            }
            
            /*
            CASE 2: temp points to NULL
            - Make newNode point to NULL (just in case it isn't already, even though it should be)
            - Make temp point to newNode
            - Swap values of temp and newNode
            */

            else {
                newNode->SetLink_Next(NULL);
                temp->SetLink_Next(newNode);

                int x = newNode->GetData();
                newNode->SetData(temp->GetData());
                temp->SetData(x);
            }
            cout << "   SUCCESSFULLY ADDED NODE TO LIST" << endl;
        }
        size++;

    };

    // *******************
    // 4. Remove(int idx)
    // *******************
    // This function removes the node at location "idx". 
    // Here, "idx" starts from 0 (head node) and ends at n-1 (tail node). 
    // If the input "idx" is bigger than n-1, then remove the tail. 
    // Below are three examples. 
    // 
    // Example 1: 
    // If list = 5, 7, 1, 2. 
    // If we run Remove(0), 
    // then new list = 7, 1, 2. 
    // 
    // Example 2: 
    // If list = 5, 7, 1, 2. 
    // If we run Remove(2), 
    // then new list = 5, 7, 2. 
    // 
    // Example 3: 
    // If list = 5, 7, 1, 2. 
    // If we run Remove(7), 
    // then new list = 5, 7, 1. 
    // (Here, "7" is bigger than n-1, so remove the tail. ) 

    void Remove(int idx) {
        cout << "REMOVE NODE AT INDEX " << idx << endl;
        /*
        if (head == nullptr) { // if there is no head
            // just do nothing i guess
        } else
        */
        if (idx == 0) { // remove the head
            if (head->GetLink_Next() != NULL) { // if head points to another node
                head = head->GetLink_Next(); // new head
            }
            else {
                head = NULL;
            }
        }
        else if (idx > size - 1) { // index is too large; just remove the tail
            Node* temp = head;
            while (temp->GetLink_Next()->GetLink_Next() != NULL) {
                temp = temp->GetLink_Next();
            }
            temp->SetLink_Next(NULL);
        }
        else { // Regular remove
            /*
            - Iterate through list until temp node is at index - 1
            - If node at index + 1 is not NULL, then have temp point to that node
            - Otherwise, have temp point to NULL
            */
            Node* temp = head;
            for (int i = 0; i < idx-1; i++) {
                temp = temp->GetLink_Next();
            }

            cout << "temp node is at index - 1, with value " << temp->GetData() << endl;
            
            if (temp->GetLink_Next()->GetLink_Next() != NULL) {
                temp->SetLink_Next(temp->GetLink_Next()->GetLink_Next());
            }
            else {
                temp->SetLink_Next(NULL);
            }
        }

        size--;
    };

    // *************
    // 5. Reverse()
    // *************
    // This function reverses the current list. 
    // If the list is empty or contains only one node, do nothing. 
    // Below are three examples. 
    // 
    // Example 1: 
    // If list is empty. 
    // If we run Reverse(), 
    // then new list is empty. 
    // 
    // Example 2: 
    // If list = 5. 
    // If we run Reverse(), 
    // then new list = 5. 
    // 
    // Example 3: 
    // If list = 5, 7, 1, 2. 
    // If we run Reverse(), 
    // then new list = 2, 1, 7, 5. 

    void Reverse() {
        /*
        BEFORE:
            [1]->[2]->[3]->NULL // [1] is the head
        AFTER:
            [1]<-[2]<-[3]<-NULL // [3] is the head
        A linked list can easily be reversed not by rearranging the nodes, but by reversing the direction that the nodes point.
        */
        Node* prevNode = NULL;
        Node* currNode = head;
        Node* nextNode = NULL;

        while (currNode != NULL) {
            // store the value of the next node after currNode
            nextNode = currNode->GetLink_Next();
            // flip the direction that currNode points, from the next node in the list to the previous
            currNode->SetLink_Next(prevNode);
            // advance pointers
            prevNode = currNode;
            currNode = nextNode; // eventually, nextNode will be NULL, which passes to currNode, which ends the loop
        }
        // Finally, our tail needs to be designated as the new head. 
        // Since currNode is NULL, the preceding node prevNode is our new head.
        head = prevNode;
    };
};
// methods below are already provided
SList::SList() {
    head = NULL;
}
void SList::Print() {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->GetData() << endl;
        temp = temp->GetLink_Next();
    }
}
Node* SList::GetHead() {
    return head;
}
void SList::SetHead(Node* ptr) {
    head = ptr;
}

//
// -----------
// Merge Sort  
// -----------
// The following is an incomplete merge sort function. 
// Its input is the head pointer of a singly linked list. 
// Its output is the head pointer of the sorted list. 
// We will test this function in the following way: 
// First, use your SList class to generate a singly linked list. 
// Then, retrive its head pointer and pass it to the merge sort function.
// Finally, get a new head pointer of the sorted list, pass it back to the list class and print it.
// You can see the testing code in the main function (mode = 7)
// .........
// Your task is to design and implement this merge sort function 
// based on the singly linked list data structure. 
// No array or vector can be used. 
// Tip: it should be recursive. 
// 
Node* MergeSort(Node* ptr) {

    // ...... 
    // ...... 
    Node* x{};
    return x;
}


int main()
{
    // 
    // The main function is given to you. 
    // It first constructs a singly linked list. 
    // It then tests your implemented member functions 
    // and the merge sort function. 
    // 

    SList x;
    int mode, value, idx, key; int temp; // I added int temp, is this necessary?

    cin >> mode >> value >> idx >> key; // mode, value, index, key

    for (int i = 0; i < 4; i++) {
        cout << "Add new node at index 0" << endl;
        cin >> temp;
        x.Add(temp, 0);
    } 
    cout << "head data: " << x.GetHead()->GetData() << endl;
    cout << "next node data: " << x.GetHead()->GetLink_Next()->GetData() << endl;
    cout << "PRINT:" << endl;
    switch (mode) {

    case 1: // check your add function with idx = 0
        x.Print();
        break;

    case 2: // check your GetSize function
        cout << x.GetSize();
        break;

    case 3: // check your LinearSearch function
        cout << x.LinearSearch(key);
        break;

    case 4: // check your add function with arbirary idx 
        x.Add(value, idx);
        x.Print();
        break;

    case 5: // check your remove function
        x.Remove(idx);
        x.Print();
        break;

    case 6: // check your reverse function 
        x.Reverse();
        x.Print();
        break;

    case 7: // check your merge sort function
        x.SetHead(MergeSort(x.GetHead()));
        x.Print();
        break;
    }

    return 0;
}
