//
//  ETokenize.h
//  Tokenizer
//
//  Created by Allen Wang on 12/5/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#include "token.h"
#include "STokenize.h"
#include "myQueue.h"
#include "myStack.h"
#include <iostream>
#include <vector>

using namespace std;

#ifndef Tokenizer_ETokenize_h
#define Tokenizer_ETokenize_h

class invalidExpression{}; //exception class for invalid expression

class ETokenize{
private:
    STokenize _stringToken; //STokenize as a variable.
    
public:
    ETokenize();
    ETokenize(string getThis);
    Queue<Token> gatherToken(); //This gets all the tokens into a Queue
    Queue<Token> combineExpression(Queue<Token> combineThis) throw (invalidExpression); //This will combine the 3.14 into 1 Token
};

ETokenize::ETokenize(){
}

ETokenize::ETokenize(string getThis){
    _stringToken = getThis; //Initialize the STokenizer with the string to be tokenized
}

Queue<Token> ETokenize::gatherToken(){
    Queue<Token> temp; //A queue to hold the tokens
    Token hold;
    while(_stringToken.More()){ //While there is more in the String expression
        hold = _stringToken.NextToken(); //Call the NextToken method from STokenize.
        if ((hold.TokenizeString())[0] == '(' || (hold.TokenizeString())[0] == ')'){ //The problem with the STokenize is that (( will bcome 1 token, when it needs to be 2. The following code will separate them.
            int length = (hold.TokenizeString()).length(); //Get how many parenthesis there are in the Token
            string s(hold.TokenizeString()); //Turn the Token to a string
            vector<char> v(s.begin(), s.end()); //Put all the characters from the string into a vector
            for (int i = 0; i < v.size(); i++){ //Iterate through the vector
                char a = v[i]; //Get the one single parenthesis, like just (
                string tempHold(1, a); //turn the char into a string
                hold = Token(tempHold, 7); //Declare it as a Token
                temp.push(hold); //Push into the Queue
            }
        } else {
            temp.push(hold); //push to the Queue
        }
    }
    return temp;
}

Queue<Token> ETokenize::combineExpression(Queue<Token> combineThis) throw (invalidExpression){
    Queue<Token> gather;
    Token hold;
    int left = 0, right = 0; //counting number of left and right parenthesis. They have to be equal for the evaluator to work
    while (combineThis.Size() > 0){
        if ((combineThis.peek()).Type() == 3 || (combineThis.peek()).Type() == 5 ||  (combineThis.peek()).Type() == 7){
            //If the Token is alphabetic, an operator, or parenthesis...
            hold = combineThis.pop(); //just pop from the incoming Queue
            if (hold.TokenizeString() == "("){
                left++; //increment # of left
            }
            if (hold.TokenizeString() == ")"){
                right++; //increment # of right
            }
            gather.push(hold); //push to the outgoing Queue
        }
        if ( (combineThis.peek()).Type() == 4 || (combineThis.peek()).Type() == 6 || (combineThis.peek()).Type() == 1){
            //If incoming is a number, punctuation, or white space
            if ((combineThis.peek().Type()) == 6){
                //if the incoming is a ".", so the beginnning of a decimal such as .35.
                if (combineThis.peek().TokenizeString() == "."){
                    hold = combineThis.pop(); //take the "."
                    string part1 = hold.TokenizeString(); //Put the "." as a string
                    hold = combineThis.pop();//take the next Token, which will be the number part
                    string part2 = hold.TokenizeString(); //put number as string
                    string part = part1 + part2; //combine them together into .35
                    Token combined(part, 8); //Put as a token of type 8.
                    gather.push(combined); //push into the outgoing Queue
                }
                else {
                    hold = combineThis.pop();//if it is not a ".",
                    gather.push(hold); //just push into the outgoing. This is will only be a comma.
                }
            }
            else if ((combineThis.peek().Type()) == 1){
                //If it is a white space, just pop. Move on. Discard it.
                hold = combineThis.pop();
            }
            else if ((combineThis.peek().Type()) == 4){
                //if the incoming is a number...
                hold = combineThis.pop(); //pop the number.
                string part1 = hold.TokenizeString(); //put it in a string.
                if (combineThis.peek().TokenizeString() == "."){
                    //if after is a decimal. This means something like 3.14
                    hold = combineThis.pop(); //take the "."
                    string part2 = hold.TokenizeString(); //put "." as string
                    hold = combineThis.pop(); //take the next one, which is the 14 part.
                    string part3 = hold.TokenizeString(); //put as a string
                    string part = part1 + part2 + part3; //combine all three parts to form 3.14
                    Token combined(part, 8); //Put as a Token type of 8
                    gather.push(combined); //push into Queue
                }
                else if (combineThis.peek().Type() == 1){ //If the token after a number is white space...
                    Token temp = hold; //hold that first number.
                    hold = combineThis.pop(); //pop the white space.
                    string part2 = hold.TokenizeString(); //put the white space as a string
                    if (combineThis.peek().Type() == 4){ //if the token after the white space is a number...this means rational like 3 3/4
                        hold = combineThis.pop(); //pop the numerator
                        string part3 = hold.TokenizeString(); //put number as string
                        hold = combineThis.pop();//pop the "/"
                        string part4 = hold.TokenizeString(); //put as string
                        hold = combineThis.pop();//pop the denominator
                        string part5 = hold.TokenizeString(); //put as string
                        string part = part1 + part2+ part3+ part4+ part5; //combine all 5 parts
                        Token combined(part, 9); //put as a token type of 9
                        gather.push(combined); //push into the queue
                    } else {
                        gather.push(temp); //If the token after the white isn't a number, just push that first number into Queue
                    }
                }
                else {
                    gather.push(hold); //if there is nothing after the number,push that whole number into queue
                }
            }
            else {
                hold = combineThis.pop(); //if it is not of the above types,
                gather.push(hold); //just push into the outgoing queue
            }
        }
    }
        if (left != right){//if not the same number of left and right parenthesis
            throw invalidExpression(); //throw an exception
        }
        return gather; //return the queue that has the tokens combined
}











#endif
