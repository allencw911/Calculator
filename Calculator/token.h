
//

#include <iostream>

using namespace std;



#ifndef Tokenizer_token_h
#define Tokenizer_token_h

class Token{
public:
    Token();
    Token(string s, int type); //Token with a String
    Token(char ch, int type); //Token with a char
    friend ostream& operator <<(ostream &out, const Token& token); //overloaded cout for Token
    int& Type(); //get the Token Type
    string &TokenizeString(); //get the string in the Token. VERY USEFUL
    friend bool operator ==(const Token& a, const Token& b); //the == overloaded
    bool operator <(const Token& b); //overloaded < for comparison.
private:
    string _token; //the string
    int _type; //the token type
};

Token::Token(): _token(), _type(){
    
}

Token::Token(string s, int type): _token(s), _type(type){
    //intialize the member variables.
}

ostream& operator <<(ostream &out, const Token& token){ //overloaded cout <<
    out<<"{ ["<<token._token<<"] "<<token._type<<" }";
    return out;
}

int& Token::Type(){
    return _type; //return the type
}

string& Token::TokenizeString(){
    return _token; //return the string
}

bool operator ==(const Token& a, const Token& b){
    if (a._token == b._token){ //check if the strings are equal or not
        return true;
    }
    return false;
}

bool Token:: operator <(const Token& b){
    if (_token < b._token){ //check if < 
        return true;
    }
    return false;
}










#endif
