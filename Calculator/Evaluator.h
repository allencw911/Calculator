//
//  Evaluator.h
//  Tokenizer
//
//  Created by Allen Wang on 12/6/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#include "Shunt.h"
#include "ETokenize.h"
#include "myQueue.h"
#include "myStack.h"
#include "token.h"
#include "STokenize.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#ifndef Tokenizer_Evaluator_h
#define Tokenizer_Evaluator_h

class Evaluator{
private:
    ETokenize _etoken; //ETokenizer
    Shunt sh; //Shunting yard
    Queue<Token> input; //input Queue to be solved
    double xValue; //the xValue for the graph
    
    
public:
    Evaluator(string evaluateThis, double value);
    double evaluate();
    
};

Evaluator::Evaluator(string evaluateThis, double value){
    ETokenize temp(evaluateThis); //Will declare an ETokenize object.
    input = temp.combineExpression(temp.gatherToken()); //Calling the combineExpression method from ETokenize to get a cleaned expression.
    Shunt tempShunt(input); //creating a Shuting yard object from the cleaned-up expression.
    sh = tempShunt;
    xValue = value; //setting the x-Value.
    
}

double Evaluator::evaluate(){
    Queue<Token> expression = sh.shunt(); //Get a Queue with the post-fix expression.
    Token hold; //temporary hold Token
    string stringHold; //temporary string
    Stack<double> answerStack; //This is the Stack for the answer.
    
    double answer = 0.0;
    while (expression.Size() > 0){
        
        if (expression.peek().Type() == 4 || expression.peek().Type() == 8 || expression.peek().TokenizeString() == "x"){
            //this If statement is for is the first value of the Queue is a whole number, decimal number or an X
            hold = expression.pop(); //pop the top one
            stringHold = hold.TokenizeString(); //get the string
            if (stringHold == "x"){ //is it is an X
                answer = xValue; //just set it to X
            }
            else { //if not an X
                answer = stod(stringHold); //just turn the string to a double.
            }
            answerStack.push(answer); //push into the answer stack
        }
        if (expression.peek().Type() == 9){ //this If statement is if it is a Rational number.
            hold = expression.pop(); //pop it.
            //I originally tried STokenize for this, but a bug came up where it sometimes didn't work. I just decided to use substrings to get the individuals ones.
            int count = 0;
            stringHold = hold.TokenizeString();
            while (stringHold[count] != ' '){
                count++;
            }
            string whole = stringHold.substr(0,count); //This gets the whole number.
            count++;
            int numS = count;
            int numZ = count;
            count = 0;
            while (stringHold[numZ] != '/'){
                numZ++;
                count++;
            }
            string num = stringHold.substr(numS,count); //This gets the numerator
            numZ++;
            string denom = stringHold.substr(numZ); //This gets the denominator
            
            double rational1 = stod(whole); //Turn them all into doubles to be solved.
            double rational2 = stod(num);
            double rational3 = stod(denom);
            
            rational2 = rational2/rational3;
            rational1 = rational1 + rational2; //Turns the Rational number into a decimal
            answerStack.push(rational1); //push the decimal into the answer Stack
            
        }
        if (expression.peek().Type() == 5 || expression.peek().TokenizeString() == "max"){ //This if Statement is for if it is an operator.
            hold = expression.pop(); //pop it.
            double first = answerStack.pop(); //pop the first 2 from the answer stack
            double second = answerStack.pop();
            //Will perform the following operations on those 2 from the stack depending on the operator
            if (hold.TokenizeString() == "+"){
                answer = first + second;
            }
            if (hold.TokenizeString() == "-"){
                answer = second - first;
            }
            if (hold.TokenizeString() == "*"){
                answer = first * second;
            }
            if (hold.TokenizeString() == "/"){
                answer = second / first;
            }
            if (hold.TokenizeString() == "^"){
                answer = pow(second, first);
            }
            if (hold.TokenizeString() == "max"){
                if (first >= second){
                    answer = first;
                }
                else {
                    answer = second;
                }
            }
            answerStack.push(answer); //push the answer into the stack
        }
        if (expression.peek().TokenizeString() == "sin" || expression.peek().TokenizeString() == "cos" || expression.peek().
            TokenizeString() == "tan"){ //This if Statement is to for the trig operations
            hold = expression.pop();//pop it
            double first = answerStack.pop(); //take the first from the stack, usually will just be the X-value.
            //Will performed the following operations
            if (hold.TokenizeString() == "sin"){
                answer = sin(first);
            }
            if (hold.TokenizeString() == "cos"){
                answer = cos(first);
            }
            if (hold.TokenizeString() == "tan"){
                answer = tan(first);
            }
            answerStack.push(answer);//Push to the answer stack
        }
        
    }
    answer = answerStack.peek();//There will only be 1 value in the stack left. This is the answer
    return answer; //return the answer
}





#endif


