//
//  STokenize.h
//  Tokenizer
//
//  Created by Allen Wang on 11/23/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#ifndef Tokenizer_STokenize_h
#define Tokenizer_STokenize_h

#include "tokenset.h"
#include "token.h"
#include <iostream>
using namespace std;

class STokenize{
public:
    STokenize();
    STokenize(const string aString); //take in a string to be Tokenized
    friend STokenize & operator >>(STokenize& stringToken, string &token);
    Token NextToken(); //returns the Next Token
    bool determineType(string tokenSet, char block); //determine the Type of the Token
    bool More(); //If there is more in the string
    int Position(); //return the position.
    int getType(char block); //get the type
    int Find(string charBlock, char block, int position); //Find
    int FindNot(string charBlock, string charSet, int position); //Find the first Not of
private:
    string _s; //the string to be tokenized
    int _position; //position
};

STokenize::STokenize(): _s(), _position(){
    
}

STokenize::STokenize(const string aString){
    _s = aString; //set the variables
    _position = 0;
}

STokenize& operator >> (STokenize& stringToken, string& token){
    stringToken._s = token; //overloaded >>
    return stringToken;
}

bool STokenize::determineType(string tokenSet, char block){ //This function determines if something is of a certain type or not. Will return true if it is, or false if it is not
    int i = 0;
    while (tokenSet[i] != '\0'){
        if (tokenSet[i] == block){
            return true;
        }
        i++;
    }
    return false;
}

int STokenize::Position(){
    return _position; //returns the position
}

int STokenize::getType(char block){
    Set tokenSet; //Declare a tokenSet object. The tokenSet has all the different types of delimitors.
    //This will give away the Token Types.
    if (determineType(tokenSet.whiteSpace(), block)){
        return 1; //If it is a white space, Token Type is 1
    } else if (determineType(tokenSet.endOfLine(), block)){
        return 2; //If it is the EndofLine, Token type is 2
    } else if (determineType(tokenSet.alpha(), block)){
        return 3; //If it is a alphabetic character, Type 3
    } else if (determineType(tokenSet.num(), block)){
        return 4; //If it is a number, type 4
    } else if (determineType(tokenSet.operators(), block)){
        return 5; //If an operator, type 5
    } else if (determineType(tokenSet.punctuation(), block)){
        return 6; //if punctuation, type 6
    } else if (determineType(tokenSet.match(), block)){
        return 7; //if it is parenthesis, {} and [], then type 7
    } else{
        return -1; //if None of the above, type -1.
    }
}

int STokenize::Find(string charBlock, char block, int position){ //This method will find the position
    int i = position;
    while (charBlock[i] != NULL){
        if (charBlock[i] == block){
            return i;
        }
        i++;
    }
    return -1;
}

int STokenize::FindNot(string charBlock, string charSet, int position){//This method will find the first Not of Position
    int i;
    while (charBlock[position] != NULL){
        i = Find(charSet, charBlock[position], 0);
        if (i == -1){
            return position;
        }
        position ++;
    }
    return -1;
}

Token STokenize::NextToken(){
    Set tokenSet;//declare tokenSet object
    string temp; //declare temporary string
    int i;
    int block = getType(_s[_position]); //This gets the type of the first character.
    
    if (block == 1){ //if that first character is a white space
        i = FindNot(_s, tokenSet.whiteSpace(), _position); //find the first Not of white space
    } else if (block == 2){ //...if end of Line
        i = FindNot(_s, tokenSet.endOfLine(), _position);//find the first Not of end of line
    } else if (block == 3){ //if alphabetic
        i = FindNot(_s, tokenSet.alpha(), _position);//find the first Not of alphabetic
    } else if (block == 4){// if number
        i = FindNot(_s, tokenSet.num(), _position);//find the first Not of number
    } else if (block == 5){// If an operator
        i = FindNot(_s, tokenSet.operators(), _position);//find the first Not of operator
    } else if (block == 6){// if a punctuation
        i = FindNot(_s, tokenSet.punctuation(), _position);//find the first Not of punctuation
    } else if (block == 7){// if a matched pair
        i = FindNot(_s, tokenSet.match(), _position);//find the first Not of matched pair
    } else {
        i = -1;
    }
    
    temp = _s.substr(_position, i - _position); //will take a substring of that 1 token Type.
    
    _position = _position + temp.length(); //increment the position
    Token token(temp, getType(temp[0])); //declare a Token with that substring
    return token; //Return the token. This is the NextToken
}

bool STokenize::More(){ //Return if there is more of that string or not
    if ((_s.length() - _position) != 0){
        return true;
    }
    return false;
}










#endif
