#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <list>
#include <map>
enum token
{ IF,THEN,LET,REM,GOTO,END,PRINT,ASSIGN,GT,LT,PLUS,MINUS,MULTI,DIVIDE, INT,INPUT,ID ,ERROR };
struct Token{
     token token_type;
     int value;
     Token(token t)
     {
         this->token_type =t;
     }
     Token(token t,int v)
     {
         this->token_type = t;
         this->value = v;
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
