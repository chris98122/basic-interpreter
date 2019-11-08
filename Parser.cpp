#include "Parser.h"

#include <QDebug>
Parser::Parser()
{

    linenum_mode=true;
}
Statement *Parser::parse(std::list<Token>* token_list)
{

    if(linenum_mode)
    {
        //need to parse the line num
        int linenum = token_list->front().value;
        token_list->pop_front();
    }


    //parse
    while (!token_list->empty()) {
        switch(token_list->front().token_type)
        {
            token_list->pop_front();
            case token::LET:
            {
                if(token_list->front().token_type == token::ID)
                     token_list->pop_front();
                else
                     qDebug()<< "syntac error" ;
            }
            case token::GOTO:
            {

            }
            case token::IF:
            {

            }
            case token::PRINT:
            {

            }
            case token::INPUT:
            {

            }
            default:
                 qDebug()<< "syntac error" ;
            }

    }
    return new Statement();
}
//LET ID ASSIGN exp
//GOTO INT
//IF exp THEN INT
//PRINT exp
//INPUT var

//exp->ID
//exp->exp OP exp
//exp->INT

//OP->PLUS | MINUS| MULTI|DIVIDE

//todo: LET, PRINT, and INPUT statements can be executed directly by typing them without a line number

