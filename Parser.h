#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <map>

#include "Lexer.h"
#include <QString>
class Statement
{
    //kind
protected:
    int linenum;

};

class Print_statement: public Statement
{

};

class Let_statement: public Statement
{
public:
    std::string id;
    int expression_value;
    Let_statement( std::string id , int expression_value)
    {
        this->id = id;
        this->expression_value = expression_value;
    }
};
class Input_statement: public Statement
{

};

class Goto_statement: public Statement
{

public:
    int dest;
    Goto_statement(int value)
    {
        this->dest =value;
    }
};

class If_statement: public Statement
{

};


class Parser
{
public:
    Parser();
    bool linenum_mode;

    std::map<std::string,int > symbol_table;

    std::map<int,Statement *> statement_list;

    Statement *parse(std::list<Token>* token_list,bool *ok , std::string *errormessage);

    int parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage);

};
#endif // PARSER_H
