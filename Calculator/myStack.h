//
//  myStack.h
//  Map
//
//  Created by Allen Wang on 11/24/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//
#include <iostream>
#include "Node.h"
#include "ListFunctions.h"

using namespace std;

#ifndef Map_myStack_h
#define Map_myStack_h

template <typename ITEM_TYPE>
class Stack{
public:
    Stack(); //constructor
    
    //BIG THREE
    ~Stack();
    Stack(const Stack& a);
    Stack& operator = (const Stack& RHS);

    bool empty();
    
    ITEM_TYPE pop(); //pop from front
    void push(ITEM_TYPE a); //push
    ITEM_TYPE peek(); //return the front ITEM.
    
    void PrintStack();
    
    void ClearStack();
    
    int Size();
    
    template <typename U>
    friend ostream &operator <<(ostream & output, const Stack<U>& a);
    
    
private:
    node<ITEM_TYPE>* front; //the node pointer to the top of the Stack.
    int size; //size of the Stack
    
    
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(){
    front = NULL; //initialize member variables
    size = 0;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE> &a){ //copy constructor
    front = copyList(a.front);
    size = a.size;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>:: ~Stack(){ //destructor
    ClearStack();
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>:: operator = (const Stack<ITEM_TYPE>& RHS){
    //assignment operator
    if (&RHS == this){
        return *this;
    }
    ClearStack();
    front = RHS.front;
    front = NULL;
    front = copyList(RHS.head);
    size = RHS.size;
    return *this;
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::ClearStack(){
    clearList(front); //clear the Stack
}


template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){
    return (front == NULL); //If the Stack is empty
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE a){
    front = insertHead(front, a); //just keep insertHead
    size++; //increase the size by 1
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop(){
    ITEM_TYPE temp = front->_item; //take the Top ITEM
    deleteNode(front, front); //delete the top ITEM
    size--; //decrease size by 1
    return temp; //return the top ITEM
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::peek(){
    ITEM_TYPE temp = front -> _item; //return the top ITEM without deleting it
    return temp;
}

template <typename ITEM_TYPE>
int Stack<ITEM_TYPE>::Size(){
    return size; //return the size of Stack
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::PrintStack(){
    printList(front); //print the Stack
}





#endif
