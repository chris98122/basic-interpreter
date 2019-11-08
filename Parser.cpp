#include "Parser.h"
#include <stack>
#include <QDebug>
Parser::Parser()
{

    linenum_mode=true;
}
Exp * create_exp_tree(std::list<Token>  token_list);
bool is_exp_legal(std::list<Token>  token_list);
std::list<token> reverse_polish_expression(std::list<Token>* token_list);
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

    qDebug()<< "parsing start" ;
    while (!token_list->empty()) {
        Token t = token_list->front();
        token_list->pop_front();
        switch(t.token_type)
        {
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
                            if(linenum_mode)
                            {
                               qDebug()<< "LET" ;
                               Let_statement* r=  new Let_statement( id ,e);
                               this->statement_list[linenum] = r;
                               return r;
                            }
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

                    Goto_statement* r=  new Goto_statement( token_list->front().value);
                    this->statement_list[linenum] = r;
                    return r;
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
                    int dest = token_list->front().value;
                    If_statement * r = new If_statement(e , dest);
                    this->statement_list[linenum] = r;
                    return r;

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
                     if(linenum_mode)
                     {
                         Print_statement* r =  new Print_statement( e );
                         this->statement_list[linenum] = r;
                         return r;
                     }
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
                    if(linenum_mode)
                    {
                    Input_statement * r = new Input_statement(token_list->front().name);
                    this->statement_list[linenum] = r;
                    return r;
                    }
                }
                else
                {
                    *ok =false;
                    return new Statement();
                }
            }
            default:
                 *errormessage = "syntax error" ;
            }
    }

    *ok = true;
    return new Statement();
}

Exp *  Parser::parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage)
{
    //basic it's a calculator

    std::stack<token> stack;

    qDebug()<< token_list->size();
    bool exp_legal = is_exp_legal(*token_list);
    if(exp_legal){
        qDebug()<< "exp_legal" ;

        // create exp tree
       Exp * e = create_exp_tree(*token_list);
       return e;
    }
    else
    {
        *ok = false;
        *errormessage = "not a valid expression";
        return NULL;
    }
}

bool is_op(token input)
{
    return input == token::GT || input==token::LT ||input ==token::PLUS ||input==token::MINUS || input ==token::MULTI || input==token::DIVIDE;
}

Exp * create_exp_tree(std::list<Token>  token_list)
{

   qDebug()<< "create_exp_tree";

   qDebug()<< token_list.size();
    std::stack<Exp *> exp_stack;
    std::stack<token> token_stack;
    while(!token_list.empty())
    {
        switch(token_list.front().token_type)
        {
            case token::ID:
                token_stack.push(EXP);//reduce  exp->ID
                exp_stack.push(new VarExp(token_list.front().name));
                break;
            case token::INT:
                token_stack.push(EXP);//reduce exp->INT
                exp_stack.push(new IntExp(token_list.front().value));
                break;
            case token::LEFTPAR:
                token_stack.push(LEFTPAR);//shift
                break;
            case token::RIGHTPAR:
                token_stack.push(RIGHTPAR);//shift
                break;
            default:
            {
                if(is_op(token_list.front().token_type)) //OP->PLUS | MINUS| MULTI|DIVIDE
                {
                     token_stack.push(token_list.front().token_type);
//                     if(token_list.front().token_type == PLUS || token_list.front().token_type == MINUS)
//                     {
//                         //check if later has MULTI / DIVIDE
//                         token_list.pop_front();
//                         token a = token_list.pop_front();
//                         token b = token_list.pop_front();
//                         if(b == MULTI ||b =DIVIDE)
//                         {
//                             token_stack.push()
//                         }

//                     }

                }
            }
        }

        token_list.pop_front();
        std::vector<token> token_vec;
        if(token_stack.size()>=3)
         {
            for(int i = 0;i<3;i++)
            {
                token_vec.push_back(token_stack.top());
                token_stack.pop();
            }

                if(token_vec[0]==EXP && is_op(token_vec[1])  && token_vec[2] == EXP)
                {
                    token_stack.push(EXP);
                    Exp * right = exp_stack.top();
                    exp_stack.pop();
                    Exp * left =exp_stack.top();
                    exp_stack.pop();
                    exp_stack.push(new OpExp(left,token_vec[1],right));
                }
                else if(token_vec[2]== LEFTPAR && token_vec[1] == EXP && token_vec[0] == RIGHTPAR)
                {
                    token_stack.push(EXP);
                    //exp_stack 不变
                    continue;
                }
                else
                {
                     token_stack.push(token_vec[2]);//注意顺序
                     token_stack.push(token_vec[1]);
                     token_stack.push(token_vec[0]);
                }
         }

    }

    if( exp_stack.size() == 1  )
        return exp_stack.top();
}
bool is_exp_legal(std::list<Token>  token_list)
{
     qDebug()<< token_list.size();
    enum exp_token{EXP,OP,LEFTPAR,RIGHTPAR};
    std::stack<exp_token> token_stack;
    while(!token_list.empty())
    {
       qDebug()<< " is_exp_legal";
        switch(token_list.front().token_type)
        {
            case token::ID:
                token_stack.push(EXP);//reduce  exp->ID
                break;
            case token::INT:
                token_stack.push(EXP);//reduce exp->INT
                break;
            case token::LEFTPAR:
                token_stack.push(LEFTPAR);//shift
                break;
            case token::RIGHTPAR:
                token_stack.push(RIGHTPAR);//shift
                break;
            default:
            {
                if(is_op(token_list.front().token_type)) //OP->PLUS | MINUS| MULTI|DIVIDE
                {
                     token_stack.push(OP);
                }
                else
                {
                    return false;
                }
            }
        }

        token_list.pop_front();
        //看一下token_stack 能不能 reduce
        //pop 到vector 里面遍历 ok就push一个EXP回去 只有两种reduce 情况 1.exp->exp OP exp  2.exp->(exp)
        //所以正好只需要POP三个出来
        std::vector<exp_token> token_vec;
        if(token_stack.size()>=3)
         {
            for(int i=0;i<3;i++)
            {
                token_vec.push_back(token_stack.top());
                token_stack.pop();
            }
            //开始查看vector里面这三个exp_token能不能REDUCE 注意这里先不管乘法的优先级
                if(token_vec[0]==EXP && token_vec[1] == OP && token_vec[2] == EXP)
                {
                    token_stack.push(EXP);
                }
                else if(token_vec[2]== LEFTPAR && token_vec[1] == EXP && token_vec[0] == RIGHTPAR)
                {
                    token_stack.push(EXP);
                    continue;
                }
                else
                {
                     token_stack.push(token_vec[2]);//注意顺序
                     token_stack.push(token_vec[1]);
                     token_stack.push(token_vec[0]);
                }
             }
    }
    if(token_stack.size() == 1 && token_stack.top() ==EXP)
        return true;
    return false;
}


std::list<token> reverse_polish_expression(std::list<Token>* token_list)
{

}




//todo: LET, PRINT, and INPUT statements can be executed directly by typing them without a line number

