#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <list>
class Lexer
{
public:
    Lexer();

    enum token
    { IF,THEN,LET,REM,GOTO,END,PRINT,EQ,GT,LT,PLUS,MINUS, INT,INPUT }  ;

    std::list<token> tokens;

    std::list<token> lex_a_line(std::string);
};


#endif // LEXER_H
