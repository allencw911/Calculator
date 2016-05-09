//
//  myQueue.h
//  Map
//
//  Created by Allen Wang on 12/5/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "ListFunctions.h"

#ifndef Map_myQueue_h
#define Map_myQueue_h

using namespace std;

template <typename ITEM_TYPE>
class Queue{
private:
    node <ITEM_TYPE>* front; //front node
    node <ITEM_TYPE>* rear; //rear node
    int size;
public:
    Queue();//constructor
    
    //BIG THREE
    ~Queue();
    Queue(const Queue& a);
    Queue& operator = (const Queue& RHS);
    
    ITEM_TYPE getRear(); //get the rear
    
    bool empty();
    
    ITEM_TYPE pop(); //pop from the front
    void push(ITEM_TYPE a); //push to the rear
    ITEM_TYPE peek(); //get the front. I used peek because I'm used to using this term instead of getFront
    
    void PrintQueue(); //print the Queue
    
    void ClearQueue(); //clear the Queue
    int Size(); //return the size of the Queue
};

template <typename ITEM_TYPE>
Queue<ITEM_TYPE>::Queue(){
    front = NULL; //initializing the Queue's member variables
    rear = NULL;
    size = 0;
}

template <typename ITEM_TYPE>
Queue<ITEM_TYPE>::Queue(const Queue<ITEM_TYPE> &a){ //COPY CONSTRUCTOR
    front = copyList(a.front);
    size = a.size;
}

template <typename ITEM_TYPE>
Queue<ITEM_TYPE>:: ~Queue(){
    ClearQueue(); //destructor
}

template <typename ITEM_TYPE>
Queue<ITEM_TYPE>& Queue<ITEM_TYPE>:: operator = (const Queue<ITEM_TYPE>& RHS){
    //assignment operator
    if (&RHS == this){
        return *this;
    }
    ClearQueue();
    front = RHS.front;
    front = NULL;
    front = copyList(RHS.front);
    size = RHS.size;
    return *this;
}

template <typename ITEM_TYPE>
void Queue<ITEM_TYPE>::ClearQueue(){
    clearList(front); //deletes the Queue
}

template <typename ITEM_TYPE>
bool Queue<ITEM_TYPE>::empty(){
    return (front == NULL); //if the Queue is empty
}

template <typename ITEM_TYPE>
void Queue<ITEM_TYPE>::push(ITEM_TYPE a){
    if (rear){//if rear isn't NULL
        rear = insertAfter(rear, a); //insertAfter
    }else{//if rear IS NULL
        rear = insertHead(front, a); //Inserthead. This only happens once, when the Queue is empty.
    }
    size++; //increase the size by 1.
}

template <typename ITEM_TYPE>
ITEM_TYPE Queue<ITEM_TYPE>::getRear(){
    if (!rear){ //if Rear isn't null
        return rear->_item; //return the rear ITEM
    }
}

template <typename ITEM_TYPE>
ITEM_TYPE Queue<ITEM_TYPE>::peek(){
    ITEM_TYPE temp = front -> _item;
    return temp; //return the front ITEM, without deleting it
}

template <typename ITEM_TYPE>
ITEM_TYPE Queue<ITEM_TYPE>::pop(){
    ITEM_TYPE temp = front->_item; //take the front ITEM
    deleteNode(front, front); //delete that front ITEM
    size--; //reduce size by 1
    return temp; //return the front ITEM
}

template <typename ITEM_TYPE>
int Queue<ITEM_TYPE>::Size(){
    return size; //return the size
}

template <typename ITEM_TYPE>
void Queue<ITEM_TYPE>::PrintQueue(){
    printList(front); //print the queue
}










#endif
