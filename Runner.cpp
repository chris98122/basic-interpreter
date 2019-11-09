#include "Runner.h"

#include "Parser.h"

#include <QDebug>
#include <iostream>
#include <exception>

Runner::Runner(std::map<int,Statement *> statement_list)
{
    this->statement_list = statement_list;
}


void Runner::run( bool rerun, int input)
{

    std::map<int,Statement *>::iterator start_point ;
    if(!rerun)//sequntial run
    {
        start_point = statement_list.begin();
    }
    else
    {
        start_point =statement_list.find(start_line);
    }

    auto i =  start_point ;


    for( i =  start_point ; i != statement_list.end();)
    {
        Statement *running_statement = i->second;
        std::string line =std::to_string(i->first) ;

       qDebug()<<line.c_str()<<endl;

        switch(running_statement->kind)
        {
            case statement_kind::Rem:
                i++;
                break; //do nothing
            case statement_kind::Print:
                {
                  Exp * exp = ((Print_statement *)running_statement)->expression;
                  bool ok;
                  int exp_val = calculation_exp(exp,&ok);
                  //拜托command 打印一下
                  if(ok)
                  {
                      Commandprint(QString(std::to_string(exp_val).c_str()));
                      i++;
                      break;
                  }
                      else {
                      //跳出循环
                      Commandprint(QString(( line + " " +  " Print Error! Not a valid expression.").c_str()));

                      i = statement_list.end();
                  }
                }
            case statement_kind::If:
                {

                  Exp * exp = ((If_statement *)running_statement)->expression;
                  int dest= ((If_statement *)running_statement)->dest;
                  bool ok;
                  int exp_val = calculation_exp(exp,&ok);
                  if(ok && exp_val == 1)
                  {
                      //goto dest
                      //设置i, 重新开始循环
                      i = statement_list.find(dest);//
                      break;
                  }//不管跳不跳转都要break
                  else if(ok)
                  {
                       i++;
                      break;
                  }
                  else
                     {
                      Commandprint(QString(( line + " " +  "If Error! Not a valid expression.").c_str()));
                      i = statement_list.end();
                  }

                }
            case statement_kind::Let:
            {
                Exp * exp = ((Let_statement *)running_statement)->expression;
                std::string name =((Let_statement *)running_statement)->id;
                bool ok;
                int exp_val = calculation_exp(exp,&ok);
                if(ok)
                {

                    symbol_table[name] = exp_val;//赋值就完事了
                     i++;
                    break;
                }
                else
                {
                    Commandprint(QString(( line + " " +  "Let Error! Not a valid expression.").c_str()));
                    i = statement_list.end();
                }
            }
            case statement_kind::Goto:
             {
                int dest= ((Goto_statement *)running_statement)->dest;
                //goto dest
                //设置i, 重新开始循环
                //qDebug()<<"GOTO DEST"<<dest<<endl;
                i = statement_list.find(dest);
                break;
             }
            case statement_kind::Input:
            {
                if(!rerun)
                {

                    input_a_val();//send signal
                    qDebug()<<" send signal input_a_vaL"<<endl;
                    this->start_line = i->first; //保存当前的行数
                    return;// wait for rerun
                }
                else
                {
                    //保存读入的变量
                    std::string name =((Input_statement *)running_statement)->id;
                    this->symbol_table[name] = input;
                     i++;
                     break;
                }
            }
            case statement_kind::End:
                {
                  qDebug()<<"END"<<endl;
                  i = statement_list.end();
                  break;
                }
        }
    }

}
int Runner:: calculation_exp(Exp *exp,bool *ok)
{
    *ok = true;
    switch(exp->kind)
    {
    case Op:
        {
            Exp * leftExp= ((OpExp *)exp)->leftvalue;
            Exp * rightExp = ((OpExp *)exp)->rightvalue;
            token op = ((OpExp *)exp)->operation;
            int left_value = calculation_exp(leftExp,ok);
            if(ok)
            {
                int right_value = calculation_exp(rightExp,ok );
                if(ok)
                    return CalculationOpExp(left_value,op , right_value );
                else return 0;
            }
             else return 0;
        }
    case Int:
        return ((IntExp *)exp)->value;
    case Var:
        std::string var_name=((VarExp *)exp)->var_name;
        if(symbol_table.find(var_name) != symbol_table.end())
        {
            return symbol_table[var_name];
            //找到了 返回值
        }
        else {
            //没找到
            //拜托command发个错误信息
            *ok = false;
            Commandprint(QString(( "can't find variable " +var_name ).c_str()));
            return 0;
        }
    }
    return 0;
}

int Runner::CalculationOpExp(int left , token op, int right)
{
    switch (op) {
        case PLUS:
            return left+right;
        case MINUS:
            return left-right;
        case MULTI:
            return left*right;
        case DIVIDE:
            return left/right;
        case GT:
            return left > right;
        case LT:
            return left < right;
    }
    return 0;
}
void Runner::continue_runnning(int input)
{
      qDebug()<<"continue_runnning"<<endl;
    this->run(true, input);
}
