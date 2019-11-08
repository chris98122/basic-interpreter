#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <map>

#include "Lexer.h"
#include <QString>
struct Variable
{
    std::string name;
    int value;
};
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

};
class Input_statement: public Statement
{

};

class Goto_statement: public Statement
{

};

class If_statement: public Statement
{

};

class Exp
{
    //kind

};

class IntExp :public Exp
{

};
class IdExp :public Exp
{

};
class OpExp :public Exp
{

};


class Parser
{
public:
    Parser();
    bool linenum_mode;

    std::map<std::string,Variable *> symbol_table;

    std::list<Statement *> statement_list;

    Statement *parse(std::list<Token>* token_list);

};
#endif // PARSER_H
