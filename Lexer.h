#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <list>
#include <map>
enum token
{ LEFTPAR,GT,LT,ASSIGN,PLUS,MINUS,MULTI,DIVIDE,RIGHTPAR,IF,THEN,LET,REM,GOTO,END,PRINT, INT,INPUT,ID ,ERROR ,EXP};
struct Token{
     token token_type;
     int value;
     std::string name;
     Token(){};
     Token(token t)
     {
         this->token_type =t;
     }
     Token(token t,int v)
     {
         this->token_type = t;
         this->value = v;
     }
     Token(token t,std::string n)
     {
         this->token_type = t;
         this->name= n;
     }
};

class Lexer
{

public:
    Lexer();
     std::map<std::string, token> TOKEN_MAP;


    std::list<Token>*  lex_a_line(const std::string& input,bool *ok , std::string *errormessage);

};


#endif // LEXER_H
