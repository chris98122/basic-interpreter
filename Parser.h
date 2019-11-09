#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <map>

#include "Lexer.h"
#include <QString>
class Exp;
enum statement_kind{ Print, Let , Input, Goto,If,Rem,End };
class Statement
{

public:
   statement_kind  kind;

};

class Rem_statement: public Statement
{
public:
        Rem_statement()
        {
            this->kind = Rem;
        }

};


class End_statement: public Statement
{
public:
        End_statement()
        {
            this->kind = End;
        }

};


class Print_statement: public Statement
{
public:
        Exp *  expression;
        Print_statement(Exp *  expression)
        {
            this->kind = Print;
            this->expression= expression;
        }

};

class Let_statement: public Statement
{
public:
    std::string id;
    Exp * expression;
    Let_statement( std::string id ,Exp * expression)
    {
        this->kind = Let;
        this->id = id;
        this->expression = expression;
    }
};

class Input_statement: public Statement
{
public:
    std::string id;
    Input_statement(std::string n)
    {
        this->kind = Input;
        this->id = n;
    }
};

class Goto_statement: public Statement
{

public:
    int dest;
    Goto_statement(int value)
    {
        this->kind = Goto;
        this->dest =value;
    }
};

class If_statement: public Statement
{
public:
    Exp * expression;
    int dest;
    If_statement(Exp *  expression , int dest)
    {
        this->kind = If;
        this->expression = expression;
        this->dest =dest;
    }
};


enum exp_kind{ Op,Int,Var};
class Exp
{
public:
        exp_kind kind;
};
class OpExp:public Exp
{
public:
    Exp * leftvalue;
    Exp * rightvalue;
    token operation;

    OpExp(Exp * l,token op,Exp * r)
    {
        this->kind = Op;
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
        this->kind  = Int;
        this->value =v;
    }
};
class VarExp:public Exp
{
public:
    std::string var_name;
    VarExp(std::string s)
    {
        this->kind = Var;
        this->var_name=s;
    }
};


class Parser
{
public:
    Parser();
    bool linenum_mode;

    std::map<int,Statement *> statement_list;

    Statement *parse(std::list<Token>* token_list,bool *ok , std::string *errormessage);

    Exp * parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage);

};
#endif // PARSER_H
