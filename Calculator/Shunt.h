//
//  Shunt.h
//  Tokenizer
//
//  Created by Allen Wang on 12/6/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#include "token.h"
#include "STokenize.h"
#include "myQueue.h"
#include "myStack.h"
#include <iostream>
#include <vector>

using namespace std;


#ifndef Tokenizer_Shunt_h
#define Tokenizer_Shunt_h

class Shunt{
private:
    Queue<Token> fixThis; //Pre-fix queue
    
public:
    Shunt();
    Shunt(Queue<Token> here); //constructor
    Queue<Token> shunt(); //make into post-fix method
};

Shunt::Shunt(){}

Shunt::Shunt(Queue<Token> here){
    fixThis = here; //set the private member variable
}

Queue<Token> Shunt::shunt(){
    Token hold; //temporary hold oken
    Queue<Token> output; //output Post-fix queue
    Stack<Token> functionStack; //Function Stack
    while (fixThis.Size() > 0){ //Loop this while the input Queue is not empty
        if (fixThis.peek().Type() == 4 || fixThis.peek().Type() == 8 || fixThis.peek().Type() == 9 || fixThis.peek().
            TokenizeString() == "x"){
            //If the incoming Token is a whole number, decimal, rational, or X....
            hold = fixThis.pop(); //just pop from the Incoming queue...
            output.push(hold); //...and push into output Queue
        }
        
        if (fixThis.peek().TokenizeString() == ","){
            //if incoming is a comma
            hold = fixThis.pop(); //pop it.
            hold = fixThis.pop(); //pop the next one so comma is discarded. This next one will be a value
            output.push(hold); //push to the output Queue
        }
        if (fixThis.peek().TokenizeString() == "cos" || fixThis.peek().TokenizeString() == "tan" || fixThis.peek().TokenizeString() == "sin" || fixThis.peek().TokenizeString() == "max"){
            //if incoming is a function
            hold = fixThis.pop(); //pop from incoming
            functionStack.push(hold); //push to functionStack
        }
        if (fixThis.peek().TokenizeString() == "("){ //If incoming is (
            hold = fixThis.pop(); //pop from incoming Queue
            functionStack.push(hold); // push to functionStack
        }
        
        if (fixThis.peek().TokenizeString() == ")"){ //If incoming is right parenthesis
            hold = fixThis.pop(); // pop from incoming
            while (functionStack.peek().TokenizeString() != "("){ //Until you reach a left parenthesis
                hold = functionStack.pop(); //pop from function
                if (hold.Type() != 7){ //If it is not a ( of )
                    output.push(hold); //push to the output
                }
            }
            hold = functionStack.pop(); //pop from the functionStack. (This is be the left parenthesis)
            if (functionStack.peek().Type() == 3){ //check if the one after the left parenthesis is a function, if so
                hold = functionStack.pop(); //pop from the functionstack
                output.push(hold); //push into output Queue
            }
        }
        
        
        
        
        
        
        if (fixThis.peek().Type() == 5){
            //if the incoming type is an Operator...
            if (functionStack.Size() < 1 || functionStack.peek().TokenizeString() == "("){
                //If nothing in FunctionStack or top of FunctionStack is a (,
                hold = fixThis.pop(); //pop from incoming
                functionStack.push(hold); //push into functionStack
            }
        }
        if (fixThis.peek().Type() == 5){
            //This is for a * or / incoming. They are higher precedence of + and -, but lower then ^
            if (((fixThis.peek()).TokenizeString() == "*" || (fixThis.peek()).TokenizeString() == "/" ) && ((functionStack.peek()).TokenizeString() == "+" || (functionStack.peek()).TokenizeString() == "-") && (functionStack.peek().TokenizeString() != "^")){
                hold = fixThis.pop(); //pop from incoming
                functionStack.push(hold); //push to function
            }
            //This is for incoming ^
            if (fixThis.peek().TokenizeString() == "^"){
                hold = fixThis.pop(); //pop from incoming
                functionStack.push(hold); //push to function stack
            }
            
        }
        if (fixThis.peek().Type() == 5){
            //These are if incoming operators are the same precedence. +-*/ are left-associative.
            if ((fixThis.peek().TokenizeString() == "*" || fixThis.peek().TokenizeString() == "/" ) && (functionStack.peek().TokenizeString() == "*" || functionStack.peek().TokenizeString() == "/")){
                hold = functionStack.pop(); //pop from functionStack
                output.push(hold); //push that to the output
                hold = fixThis.pop(); //pop from the incoming
                functionStack.push(hold); //push to the functionStack
            }
            //Same as the above, but for + and -
            if ((fixThis.peek().TokenizeString() == "+" || fixThis.peek().TokenizeString() == "-" ) && (functionStack.peek().TokenizeString() == "+" || functionStack.peek().TokenizeString() == "-")){
                hold = functionStack.pop();
                output.push(hold);
                hold = fixThis.pop();
                functionStack.push(hold);
            }
            //The ^ are right associative, so they are different.
            if (fixThis.peek().TokenizeString() == "^" && functionStack.peek().TokenizeString() == "^"){
                hold = fixThis.pop(); //pop from incoming
                functionStack.push(hold); //push to functionStack
            }
        }
        if (fixThis.peek().Type() == 5){
            //These are for incoming is LOWER precedence than the top of the functionStack
            while ((fixThis.peek().TokenizeString() == "+" || fixThis.peek().TokenizeString() == "-" ) && (functionStack.peek().TokenizeString() == "/" || functionStack.peek().TokenizeString() == "*" || functionStack.peek().TokenizeString() == "^")){ //While incoming is lower precedence than the top...
                hold = functionStack.pop(); //keep popping from the functionStack
                output.push(hold); //and push it into the output
            }
            while ((fixThis.peek().TokenizeString() == "*" || fixThis.peek().TokenizeString() == "/") && (functionStack.peek().TokenizeString() == "^")){//This is same as above but for * and /
                hold = functionStack.pop();
                output.push(hold);
            }
            hold = fixThis.pop(); //pop the incoming
            functionStack.push(hold); //push to the functionStack
        }
    }
    while (functionStack.Size() > 0){ //This is for what is remaining in the functionStack
        hold = functionStack.pop(); //Pop from it
        output.push(hold); //push to the output Queue
    }
    return output; //return the output Queue. This is post-fixed
}




#endif
