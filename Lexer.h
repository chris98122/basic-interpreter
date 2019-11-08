#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <list>
#include <map>


enum token
{ IF,THEN,LET,REM,GOTO,END,PRINT,ASSIGN,GT,LT,PLUS,MINUS,MULTI,DIVIDE, INT,INPUT,ID ,ERROR }  ;

class Lexer
{
public:
    Lexer();
     std::map<std::string, token> TOKEN_MAP;

   // std::list<token> tokens;

    std::list<token>*  lex_a_line(const std::string& input);
};


#endif // LEXER_H
