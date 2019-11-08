#include "Parser.h"
#include <stack>
#include <QDebug>
Parser::Parser()
{

    linenum_mode=true;
}

bool is_exp_legal(std::list<Token>* token_list);
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

    //parse
    while (!token_list->empty()) {
        switch(token_list->front().token_type)
        {
            token_list->pop_front();
            case token::LET:
            {
                if(token_list->front().token_type == token::ID)
                {
                    std::string id = token_list->front().name;
                    token_list->pop_front();
                    if(token_list->front().token_type == token::ASSIGN)
                    {
                        token_list->pop_front();
                        //PARSE An EXPRESSION
                        int expression_value = parse_exp(token_list, ok , errormessage);
                        if(ok)
                        {
                            //assign the value directly
                         // this is run time to do:symbol_table[id] = expression_value;
                            if(linenum_mode)
                            {
                               Let_statement* r=  new Let_statement( id , expression_value );
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
              std::list<Token>  token_list_tmp;
              while(token_list->front().token_type != token::THEN)
              {
                  token_list_tmp.push_back(token_list->front());
                  token_list->pop_front();
              }
              //找到THEN
                int expression_value = parse_exp(&token_list_tmp, ok , errormessage);
              //IF exp THEN INT
                  token_list->pop_front();
                if(token_list->front().token_type == token::INT)
                {
                    int dest = token_list->front().value;
                    If_statement * r = new If_statement(expression_value , dest);
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
                //PRINT exp

                int expression_value = parse_exp(token_list, ok , errormessage);
                if(ok)
                {
                     if(linenum_mode)
                     {
                         Print_statement* r =  new Print_statement( expression_value );
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

int  Parser::parse_exp(std::list<Token>* token_list,bool *ok , std::string *errormessage)
{
    //basic it's a calculator

    std::stack<token> stack;
    bool exp_legal = is_exp_legal(token_list);
    if(exp_legal){
        // do the calculation and return int
    }
    else
    {
        *ok = false;
        *errormessage = "not a valid expression";
        return 0;
    }
}

bool is_op(token input)
{
    return input == token::GT || input==token::LT ||input ==token::PLUS ||input==token::MINUS || input ==token::MULTI || input==token::DIVIDE;
}
bool is_exp_legal(std::list<Token>* token_list)
{
    enum exp_token{EXP,OP,LEFTPAR,RIGHTPAR};
    std::stack<exp_token> token_stack;
    while(!token_list->empty())
    {
        switch(token_list->front().token_type)
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
                if(is_op(token_list->front().token_type)) //OP->PLUS | MINUS| MULTI|DIVIDE
                {
                     token_stack.push(OP);
                }
                else
                {
                    return false;
                }
            }
        }
        //看一下token_stack 能不能 reduce
        //pop 到vector 里面遍历 ok就push一个EXP回去 只有两种reduce 情况 1.exp->exp OP exp  2.exp->(exp)
        //所以正好只需要POP三个出来
        std::vector<exp_token> token_vec;
        for(int i=0;i<3;i++)
        {
            token_vec.push_back(token_stack.top());
            token_stack.pop();
        }
        //开始查看vector里面这三个exp_token能不能REDUCE
        for(int i=0;i<3;i++)
        {

        }





    }

    return true;
}


std::list<token> reverse_polish_expression(std::list<Token>* token_list)
{

}




//todo: LET, PRINT, and INPUT statements can be executed directly by typing them without a line number

