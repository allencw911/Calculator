//
//  tokenset.h
//  Tokenizer
//
//  Created by Allen Wang on 11/23/15.
//  Copyright (c) 2015 Allen Wang. All rights reserved.
//

#include <iostream>
using namespace std;


#ifndef Tokenizer_tokenset_h
#define Tokenizer_tokenset_h

class Set{
public:
    Set(); //constructor
    string whiteSpace(); //returns the whiteSpace
    string endOfLine(); //returns the endofline
    string alpha(); //returns all alphabetic characters
    string num(); //returns all the numbers
    string operators(); //returns all the operators
    string punctuation(); //returns all the punctuation
    string match(); //returns all the matched pairs
private:
    string _white; //private variables for these.
    string _end;
    string _alpha;
    string _num;
    string _operators;
    string _punctuation;
    string _match;
};

Set::Set(){
    _white = " \t"; //intialize the private variables.
    _end = "\r\n";
    _alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    _num = "1234567890";
    _operators = "+=-*/^";
    _punctuation = "<,>.?~`$%&_|\\@:;!#\"'";
    _match = "{}[]()";
}


string Set:: whiteSpace(){
    return _white;
}

string Set::endOfLine(){
    return _end;
}

string Set::alpha(){
    return _alpha;
}

string Set::num(){
    return _num;
}

string Set::operators(){
    return _operators;
}

string Set::punctuation(){
    return _punctuation;
}

string Set::match(){
    return _match;
}





#endif
