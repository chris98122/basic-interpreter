#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <map>

#include "Lexer.h"
#include <QString>
class Exp;
class Statement
{
protected:
    int linenum;

};

class Print_statement: public Statement
{
public:
        Exp *  expression_value;
        Print_statement(Exp *  expression_value)
        {
            this->expression_value = expression_value;
        }

};

class Let_statement: public Statement
{
public:
    std::string id;
    Exp * expression_value;
    Let_statement( std::string id ,Exp * expression_value)
    {
        this->id = id;
        this->expression_value = expression_value;
    }
};

class Input_statement: public Statement
{
public:
    std::string id;
    Input_statement(std::string n)
    {
        this->id = n;
    }
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
public:
    Exp * expression_value;
    int dest;
    If_statement(Exp * expression_value , int dest)
    {
        this->expression_value = expression_value;
        this->dest =dest;
    }
};
class Exp
{

};
class OpExp:public Exp
{
public:
    Exp * leftvalue;
    Exp * rightvalue;
    token operation;

    OpExp(Exp * l,token op,Exp * r)
    {
        this->leftvalue = l;
        this->operation =op;
        this->rightvalue = r;
    }
};

class IntExp:public Exp
{
public:
    int value;
    IntExp(int v)
    {
        this->value =v;
    }
};
class VarExp:public Exp
{
public:
    std::string var_name;
    VarExp(std::string s)
    {
        this->var_name=s;
    }
};


class Parser
{
public:
    Parser();
    bool linenum_mode;

    std::map<std::string,int > symbol_table;

    std::map<int,Statement *> statement_list;

    Statement *parse(std::list<Token>* token_list,bool *ok , std::string *errormessage);

    Exp * parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage);

};
#endif // PARSER_H
