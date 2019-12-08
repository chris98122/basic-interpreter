#include "Parser.h"
#include <stack>
#include <QDebug>
Parser::Parser( )
{
    linenum_mode=true;
}
void Parser::setlineMode(bool mode)
{
    this->linenum_mode = mode;
}
Exp * create_exp_tree(std::list<Token>  token_list,bool *ok);
Statement *Parser::parse(std::list<Token>* token_list,bool *ok , std::string *errormessage)
{
    int linenum;
    if(linenum_mode)
    {
        //need to parse the line num
        linenum = token_list->front().value;
        token_list->pop_front();
    }
    *errormessage = "syntax error" ;
    *ok=true;
    qDebug()<< "parsing start" ;
    while (!token_list->empty()) {
        Token t = token_list->front();
        token_list->pop_front();
        switch(t.token_type)
        {
            case token::REM:
            {
                *ok = true;
                Rem_statement * r = new Rem_statement();
                if(linenum_mode)
                {
                    this->statement_list[linenum] = r;
                    return r;
                }
                else
                {
                    *ok =false;
                    *errormessage = "REM statement need to have line number" ;
                    return new Statement();
                }

            }
             case token::END:
            {
                qDebug()<< "LEX END LINENUM"<<linenum ;
                End_statement * r = new End_statement();
                if(linenum_mode)
                {
                    this->statement_list[linenum] = r;
                    return r;
                }
                else
                {
                    *ok =false;
                    *errormessage = "END statement need to have line number" ;
                    return new Statement();
                }
            }
            case token::LET:
            {
                  qDebug()<< "LET" ;
                if(token_list->front().token_type == token::ID)
                {
                    std::string id = token_list->front().name;
                    token_list->pop_front();
                    if(token_list->front().token_type == token::ASSIGN)
                    {
                        token_list->pop_front();
                        qDebug()<< "PARSE An EXPRESSION" ;

                        Exp *e = parse_exp(token_list, ok , errormessage);
                        if(ok)
                        {
                            //assign the value directly
                         // this is run time to do:symbol_table[id] = expression_value;

                            Let_statement* r=  new Let_statement( id ,e);
                            if(linenum_mode)
                            {
                               this->statement_list[linenum] = r;
                            }
                            else
                            {

                                this-> direct_statement =r;
                            }

                            return r;
                        }
                        else
                        {
                          return new Statement();
                        }
                    }
                    else
                    {
                        *ok =false;
                        return new Statement();
                    }
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            case token::GOTO:
            {
                     qDebug()<< "GOTO" ;
                if(token_list->front().token_type == token::INT)
                {
                    if(linenum_mode)
                    {
                        Goto_statement* r=  new Goto_statement( token_list->front().value);
                        this->statement_list[linenum] = r;
                        return r;
                    }
                     else
                    {
                        *ok =false;
                        *errormessage = "GOTO statement need to have line number" ;
                        return new Statement();
                    }
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            case token::IF:
            {
                    qDebug()<< "IF";
              std::list<Token>  token_list_tmp;
              while(token_list->front().token_type != token::THEN)
              {
                  token_list_tmp.push_back(token_list->front());
                  token_list->pop_front();
              }
              //找到THEN
                    Exp *e = parse_exp(&token_list_tmp, ok , errormessage);
              //IF exp THEN INT
                  token_list->pop_front();
                if(token_list->front().token_type == token::INT)
                {
                    if(linenum_mode)
                    {
                        int dest = token_list->front().value;
                        If_statement * r = new If_statement(e , dest);
                        this->statement_list[linenum] = r;
                        return r;
                    }
                    else
                   {
                       *ok =false;
                       *errormessage = "IF statement need to have line number" ;
                       return new Statement();
                   }
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            case token::PRINT:
            {
                qDebug()<< "PRINT";

                   Exp *e = parse_exp(token_list, ok , errormessage);
                if(ok)
                {

                    Print_statement* r =  new Print_statement( e );
                     if(linenum_mode)
                     {
                         this->statement_list[linenum] = r;

                     }
                     else
                     {
                            this-> direct_statement =r;
                     }
                     return r;
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            case token::INPUT:
            {
                //INPUT var
                if(token_list->front().token_type == token::ID)
                {

                    Input_statement * r = new Input_statement(token_list->front().name);
                    if(linenum_mode)
                    {
                        this->statement_list[linenum] = r;

                    }
                    else
                    {
                           this-> direct_statement =r;
                    }
                    return r;
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            default:
                {
                    *errormessage = "syntax error" ;
                    *ok =false;
                    return new Statement();
                }
            }
    }

    *ok = true;
    return new Statement();
}
std::list<Token>* split_GT_LT(std::list<Token>* token_list, token op);
Exp *  Parser::parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage)
{
   Exp * e = create_exp_tree(*token_list,ok);

    if(ok  )
    {
       return e;
    }
    else
    {
        *ok = false;
        *errormessage = "not a valid expression";
        return NULL;
    }
}

void BinaryOp( token op,std::stack<Exp *> *dataStack,bool *ok)
{

    Exp *left;
    Exp *right;
    if(dataStack->size()<2)
    {
         qDebug()<<  dataStack->size();

            qDebug()<< " BinaryOp dataStack->size()<2";
        *ok =false;
        return;
    }
    right = dataStack->top();
    dataStack->pop();
    left =dataStack->top();
    dataStack->pop();
      qDebug()<< " OK";
    OpExp *opexp = new OpExp(left,op,right);
    dataStack->push(opexp);
}
Exp * create_exp_tree(std::list<Token>  token_list,bool *ok)
{

    qDebug()<< "create_exp_tree";
    *ok =true;

    std::stack<Exp *> exp_stack;
    std::stack<token> token_stack;
    Token lastOp;
    token topOp;
    std::stack<token> opStack;
    std::stack<Exp *> dataStack;
    qDebug()<< token_list.size();
    while(!token_list.empty())
    {

        qDebug()<< "PARSE EXP";
        lastOp = token_list.front();
        qDebug()<< lastOp.token_type;
        switch(lastOp.token_type)
        {
            case token::INT:
                qDebug()<< "EXP token::INT";
                dataStack.push(new IntExp(lastOp.value));
                break;
            case token::ID:
               qDebug()<< "EXP token::ID";
                dataStack.push(new VarExp(lastOp.name));
                break;
            case token::RIGHTPAR:
             qDebug()<< "RIGHTPAR";
                while(!opStack.empty() &&( topOp =opStack.top()) != LEFTPAR)
                {
                     qDebug()<< "   BinaryOp";
                        BinaryOp(opStack.top() ,&dataStack,ok);

                        if(!ok)return new Exp();

                     qDebug()<< "BEFORE POP" <<opStack.size();
                    opStack.pop();
                }
                if(!opStack.empty())
                {
                    opStack.pop();
                 }

                if( topOp != LEFTPAR)
                {
                    *ok =false;
                    return new Exp();
                }
                 qDebug()<< "BEFORE BREAK";
                break;
            case token::LEFTPAR:
                opStack.push(token::LEFTPAR);
                break;
            case MULTI:case DIVIDE:
                while (!opStack.empty() && opStack.top() >= MULTI) {
                     BinaryOp(opStack.top(),&dataStack,ok);
                     if(!ok)return new Exp();
                     opStack.pop();
                }
                opStack.push(lastOp.token_type);
                 break;
            case PLUS:case MINUS:
                while (!opStack.empty() && opStack.top() >= PLUS) {
                    BinaryOp(opStack.top(),&dataStack,ok);
                    if(!ok)return new Exp();
                    opStack.pop();
                }
                opStack.push(lastOp.token_type);
                 break;
             case GT:case LT:case ASSIGN:
                    while (!opStack.empty() && opStack.top() >= GT) {
                        BinaryOp(opStack.top(),&dataStack,ok);
                        if(!ok)return new Exp();
                        opStack.pop();
                    }
                    opStack.push(lastOp.token_type);
                     break;
        }
        token_list.pop_front();
    }

    qDebug()<< "opStack.size() "<<opStack.size() ;

    qDebug()<< "dataStack.size() "<<dataStack.size() ;
    while (!opStack.empty() ) {
        qDebug()<<opStack.top() ;
        BinaryOp(opStack.top(),&dataStack,ok);
         qDebug()<< *ok;
        if(!ok)return new Exp();
        opStack.pop();
    }

    if(dataStack.size() != 1)
    {
        *ok =false;
        return new Exp();
    }
    return dataStack.top();
}

std::list<Token>* split_GT_LT(std::list<Token>* token_list, token op)
{
    std::vector<Token> token_vec;
    while(!token_list->empty())
    {
        Token t =token_list->front();
        if(t.token_type!=GT && t.token_type != LT)
        {
            token_vec.push_back(t);
            token_list->pop_front();
        }
        else
        {
            op = t.token_type;
            break;
        }
    }

    std::list<Token> *res = new  std::list<Token> ;
    for(int i=0;i<token_vec.size();i++)
    {
        res->push_back(token_vec[i]);
    }
    if(op)
    {
       return  res;
    }
    else
    {
        *token_list = *res;
        return NULL;
    }

    return NULL;




}
