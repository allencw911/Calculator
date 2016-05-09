
//

#ifndef __List__ListFunctions__
#define __List__ListFunctions__

#include <stdio.h>
#include <iostream>

using namespace std;

//typedef int ITEM_TYPE;

template <typename ITEM_TYPE>
struct node {
public:
    ITEM_TYPE _item; //ITEM in the node
    node<ITEM_TYPE>* _next; //the pointer to the next
    
    template <typename U>
    friend ostream &operator <<(ostream & output, const node<U>& a); //overloaded cout << for the node
    
    node<ITEM_TYPE>(); //different constructors
    node<ITEM_TYPE>(ITEM_TYPE i);
    node<ITEM_TYPE>(node<ITEM_TYPE>* copy);
};

template <typename ITEM_TYPE>
node<ITEM_TYPE>::node(){
    _next = NULL; //set next to NULL
}
template <typename ITEM_TYPE>
node<ITEM_TYPE>::node(ITEM_TYPE i){
    _item = i;
    _next = NULL;
}
template <typename ITEM_TYPE>
node<ITEM_TYPE>::node(node<ITEM_TYPE>* copy){ //this copies a node. its item and next pointer
    _item = copy->_item;
    _next = copy->_next;
}

template <typename U>
ostream &operator <<(ostream & output, const node<U>& a){
    output<<a._item;
    return output;
}


#endif /* defined(__List__ListFunctions__) */

