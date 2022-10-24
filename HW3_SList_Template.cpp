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
    int size = 0; // New private field. Starts at 0, since the head starts as null. Increments and decrements as nodes are added/removed.
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
        if (head == nullptr) {
            return 0;
        }
        int idx = 0;
        Node* i = head;
        while (i != NULL) {
            i = i->GetLink_Next();
            idx++;
        }
        return idx;
        //return size;
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

        while (SearchNode->GetLink_Next() != NULL) { // keep searching until null pointer reached
            if (SearchNode->GetData() == key) {
                return i;
            }
            else {
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

        if (head == nullptr) { // if there is no head
            head = newNode; // set newNode as the head
        }
        else if (idx > size - 1) { // node goes at end of list
            
            Node* temp = head;

            while (temp->GetLink_Next() != NULL) {
                temp = temp->GetLink_Next();  
            }

            temp->SetLink_Next(newNode);
            newNode->SetLink_Next(NULL); // shouldn't be necessary, but just in case
          

        }
        else { // add node somewhere before end of list

            Node* temp = head;
            for (int i = 0; i < idx; i++) {
                temp = temp->GetLink_Next();
            }
            
            // We want to insert newNode where temp is and have it connect to temp
            
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
        }
        size = GetSize(); // update size

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
            
            if (temp->GetLink_Next()->GetLink_Next() != NULL) {
                temp->SetLink_Next(temp->GetLink_Next()->GetLink_Next());
            }
            else {
                temp->SetLink_Next(NULL);
            }
        }
        size = GetSize(); // update size
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
            NULL<-[1]<-[2]<-[3] // [3] is the head
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
    head = NULL; cout << "new SList constructed: head should be null" << endl;
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
Node* MergeSort(Node* ptr) { // Input is head pointer
    cout << "BEGIN MERGESORT" << endl;
    SList SListTest;
    SListTest.SetHead(ptr);
    cout << "Size of input list: " << SListTest.GetSize() << endl;
            cout << "Current list: ";
            Node* x = SListTest.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;
    /*
    * If our head pointer is NULL (size = 0) or if it points to NULL (size = 1), return ptr as it is. There's nothing to do.
    */

    if (ptr == NULL || ptr->GetLink_Next() == NULL) {
        return ptr;
    }
    cout << "Linked list has a size of 2 or greater. :)" << endl;
    /*
    * Split the linked list into a left list and a right list.
    * For this, we use a slow pointer (starting at node 0) and a fast pointer (starting at node 1).
    * The fast pointer progresses through the list twice as fast as the slow pointer.
    * 
    *    S    F
    *         S         F
    *              S              F
    *   [0]->[1]->[2]->[3]->[4]->NULL           // example linked list with 5 elements
    *   [0]->[1]->[2]->[3]->[4]->[5]->NULL      // example linked list with 6 elements
    * 
    * The slow pointer only advances whenever the fast pointer can advance two nodes without reaching NULL.
    * This means the slow pointer will have arrived right before the midpoint of the list.
    * To create the right list, a new node object is assigned to the midpoint. This node is the right list's head. 
    * The slow pointer's node is then set to point to NULL. This node is now the left list's tail, fully dividing the original list in two.
    * Even-sized lists will be divided into equal sublists. Odd-sized lists will give the middle element to the left list.
    */ 
    
    Node* slow = ptr;
    Node* fast = ptr->GetLink_Next();

    while (fast != NULL) {
        fast = fast->GetLink_Next(); // original code contains one GetLink and adds the commented line below
        if (fast != NULL) {
            slow = slow->GetLink_Next();
            fast = fast->GetLink_Next();
        }
    }

    Node* leftList = ptr; // left list starts at head
    Node* rightList = slow->GetLink_Next(); // right list starts at midpoint
    slow->SetLink_Next(NULL);

    cout << "Successfully divided into leftList and rightList. Probably." << endl;

    /*
    * Next, recursively apply merge sort to leftList and rightList.
    */

    leftList = MergeSort(leftList);
    rightList = MergeSort(rightList);

    cout << "Passed recursive sorting. Now leftList and rightList can be merged." << endl;

    /*
    * Finally, merge leftList and rightList together.
    * 
    * First, find the smallest value and assign it as the head of finalList.
    * Then, remove it from the list where it was found.
    * Continue to find the smallest values, assign them to the tail of finalList, and remove them from their respective lists.
    * When either leftList or rightList is depleted, add all of the remaining list to finalList.
    * Then return finalList. MergeSort is complete.
    */
    
    cout << "Just a recap: " << endl;
    cout << "LEFT: ";
    x = leftList;
    while (x != NULL) {
        cout << x->GetData();
        x = x->GetLink_Next();
    }
    cout << endl;
    cout << "RIGHT: ";
    x = rightList;
    while (x != NULL) {
        cout << x->GetData();
        x = x->GetLink_Next();
    }
    cout << endl;

    // Create SListLEFT.
    SList SListLEFT;
    SListLEFT.SetHead(leftList);
    cout << "leftList size: " << SListLEFT.GetSize() << endl;
            cout << "Current leftList: ";
            x = SListLEFT.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;

    // Create SListRIGHT.
    SList SListRIGHT;
    SListRIGHT.SetHead(rightList);
    cout << "rightList size: " << SListRIGHT.GetSize() << endl;
            cout << "Current rightList: ";
            x = SListRIGHT.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;

    SList SListFINAL;
    //Node* finalList = new Node(); 
    //SListFINAL.SetHead(finalList); 
    // cout << "SListFINAL has a head of " << finalList->GetData() << endl;
    // cout << "SListFINAL has a size of " << SListFINAL.GetSize() << endl;

    Node* search; // This node iterates through leftList and rightList

    // Repeat until either leftList or rightList is empty
    while (SListLEFT.GetSize() != 0 && SListRIGHT.GetSize() != 0) {
               
        // Find smallest value in leftList
        search = SListLEFT.GetHead(); // modded mirror
        int leftIdx = 0;
        int leftSmallest = SListLEFT.GetHead()->GetData();
        int leftSmallestIdx = 0;
        while (search != NULL) {
            if (search->GetData() < leftSmallest) {
                leftSmallest = search->GetData();
                leftSmallestIdx = leftIdx;
            }
            search = search->GetLink_Next();
            leftIdx++;
        }

        // Find smallest value in rightList
        search = SListRIGHT.GetHead();
        int rightIdx = 0;
        int rightSmallest = SListRIGHT.GetHead()->GetData();
        int rightSmallestIdx = 0;
        while (search != NULL) {
            if (search->GetData() < leftSmallest) {
                leftSmallest = search->GetData();
                leftSmallestIdx = leftIdx;
            }
            search = search->GetLink_Next();
            leftIdx++;
        }

        // Compare smallest values of each list. 
        // Add the smallest value to the tail of SListFINAL and remove it from the original list.
        if (leftSmallest < rightSmallest) {
            cout << "Smallest value found: " << leftSmallest << endl;
            if (SListFINAL.GetSize() == 0) { // if SListFINAL is empty so far
                Node* newHead = new Node();
                newHead->SetData(leftSmallest);
                SListFINAL.SetHead(newHead);
                cout << "SListFINAL once had a head of 0, but now is the new smallest: " << leftSmallest << endl;
            }
            else {
                SListFINAL.Add(leftSmallest, SListFINAL.GetSize());
            }
            SListLEFT.Remove(leftSmallestIdx);
            cout << "removed " << leftSmallest << " from SListLEFT" << endl;
            cout << " New SListLEFT: ";
            x = SListLEFT.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;
        }
        else {
            cout << "Smallest value found: " << rightSmallest << endl;
            if (SListFINAL.GetSize() == 0) { // if SListFINAL is empty so far
                Node* newHead = new Node();
                newHead->SetData(rightSmallest);
                SListFINAL.SetHead(newHead);
                cout << "SListFINAL once had a head of 0, but now is the new smallest: " << rightSmallest << endl;
            }
            else {
                SListFINAL.Add(rightSmallest, SListFINAL.GetSize());
            }
            SListRIGHT.Remove(rightSmallestIdx);
            cout << "removed " << rightSmallest << " from SListRIGHT" << endl;
            cout << " New SListRIGHT: ";
            x = SListRIGHT.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;
        }
    }

    // Finally, find whichever list is not yet empty and add its remaining contents to finalList.
    
    while (SListLEFT.GetSize() != 0) {    
        SListFINAL.Add(SListLEFT.GetHead()->GetData(), SListFINAL.GetSize());
        SListLEFT.Remove(0);
    }
    while (SListRIGHT.GetSize() != 0) {
        SListFINAL.Add(SListRIGHT.GetHead()->GetData(), SListFINAL.GetSize());
        SListRIGHT.Remove(0);
    }
    cout << "Final list size: " << SListFINAL.GetSize() << endl;
            cout << "Current final list: ";
            x = SListFINAL.GetHead();
            while (x != NULL) {
                cout << x->GetData();
                x = x->GetLink_Next();
            }
            cout << endl;
    // Now we can return finalList.
    return SListFINAL.GetHead(); // don't return finalList? why not???
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
        cin >> temp;
        x.Add(temp, 0);
    } 
    
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
