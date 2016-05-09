
//

#ifndef List_ListFunctions_h
#define List_ListFunctions_h

#include <iostream>
#include "Node.h"



using namespace std;

template <typename ITEM_TYPE>
node<ITEM_TYPE>* insertHead(node<ITEM_TYPE>*& head, ITEM_TYPE item); //InserHead

template <typename ITEM_TYPE>
void printList(node<ITEM_TYPE>* head); //Print the list

template <typename ITEM_TYPE>
node<ITEM_TYPE>* search(node<ITEM_TYPE>* head, ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* insertAfter(node<ITEM_TYPE>* afterThis, ITEM_TYPE value); //InsertAfter a node

template <typename ITEM_TYPE>
node<ITEM_TYPE>* previousNode(node<ITEM_TYPE>* head, node<ITEM_TYPE>* beforeThis); //returns the previous node

template <typename ITEM_TYPE>
void insertBefore(node<ITEM_TYPE>* head, node<ITEM_TYPE>* beforeThis, ITEM_TYPE value); //insert before a node

template <typename ITEM_TYPE>
void deleteNode(node<ITEM_TYPE>* head, node<ITEM_TYPE>* n); //delete a node

template <typename ITEM_TYPE>
void clearList(node<ITEM_TYPE>* head);//clear the entire list

template <typename ITEM_TYPE>
node<ITEM_TYPE>* copyList(node<ITEM_TYPE>* head);




template <typename ITEM_TYPE>
node<ITEM_TYPE>* insertHead(node<ITEM_TYPE>*& head, ITEM_TYPE item){
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(item); //declare new node of the item
    temp-> _next = head; //temp's pointer will point to what head was pointing to
    head = temp; //head will now point to temp
    return temp;
}

template <typename ITEM_TYPE>
void printList(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* walker = head;
    while(walker){//while there is still stuff in the life,
        cout<<*walker; //cout what is there
        walker = walker->_next; //go to the next node
    }
    cout<<endl;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* search(node<ITEM_TYPE>* head, ITEM_TYPE key){ //search for a node.
    node<ITEM_TYPE>* walker = head;
    while(walker){
        if (walker -> _item == key){
            return walker;
        }
        walker = walker->_next;
    }
    return NULL;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* insertAfter(node<ITEM_TYPE>* afterThis, ITEM_TYPE value){ //insert AFTER a node
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(value); //declare the new node
    temp->_next = afterThis->_next; //temp's pointer will point to where the after one was pointing to
    afterThis->_next = temp; //the afterThis node will now point to temp
    return temp;
}

template <typename ITEM_TYPE>
void clearList(node<ITEM_TYPE>* head){
    while(head){ //while there is still stuff in life
        deleteNode(head, head); //delete the node
        head = head->_next; //increment the head
    }
    delete head; //delete the head, which will be by itself now.
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* previousNode(node<ITEM_TYPE>* head, node<ITEM_TYPE>* beforeThis){ //Returns the previousNode of a node
    node<ITEM_TYPE>* walker = head;
    while (walker ->_next != beforeThis){ //while the next is not the Node, increment
        walker = walker->_next;
    }
    return walker;
}

template <typename ITEM_TYPE>
void insertBefore(node<ITEM_TYPE>* head, node<ITEM_TYPE>* beforeThis, ITEM_TYPE value){ //Will insertBefore a node
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(value);
    node<ITEM_TYPE>* x = previousNode(head, beforeThis);
    temp->_next = beforeThis;
    x->_next = temp;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* copyList(node<ITEM_TYPE>* head){//copys the list
    node<ITEM_TYPE>* walker = head;//declare walker
    if (head == NULL){//if head is null, just return null. This is the base case. So no infinite recursive calls.
        return NULL;
    }
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>; //declare a new node
    temp->_item = walker->_item;//This node's item is same as the walker's item
    temp->_next = copyList(walker->_next); //call recursively, for the next one.
    return temp; //returns the copied list
}

template <typename ITEM_TYPE>
void deleteNode(node<ITEM_TYPE> *head, node<ITEM_TYPE> *x){
    
    if (x->_next != NULL){
        x->_item = (x->_next)->_item;
        node<ITEM_TYPE>* temp = x ->_next;
        x ->_next = (x->_next)->_next;
        delete temp;
    }else{
        if (x == head){
            head = NULL;
            //delete x;
        }
        else{
            node<ITEM_TYPE>* prev = previousNode(head, x);
            delete x;
            x = prev;
            prev->_next = NULL;
        }
    }
    
}



#endif

