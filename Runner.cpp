#include "Runner.h"

#include "Parser.h"
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

    for(auto i =  start_point ; i != statement_list.end();i++)
    {
        Statement *running_statement = i->second;
        switch(running_statement->kind)
        {
            case statement_kind::Rem:
                break; //do nothing
            case statement_kind::Print:
                {
                  Exp * exp = ((Print_statement *)running_statement)->expression;
                  int exp_val = calculation_exp(exp);
                  //拜托command 打印一下
                  Commandprint(QString(exp_val));
                  break;
                }
            case statement_kind::If:
                {
                  Exp * exp = ((If_statement *)running_statement)->expression;
                  int dest= ((If_statement *)running_statement)->dest;
                  int exp_val = calculation_exp(exp);
                  if(exp_val == 1)
                  {
                      //goto dest
                      //设置i, 重新开始循环
                      i = statement_list.find(dest);
                  }//不管跳不跳转都要break
                  break;
                }
            case statement_kind::Let:
            {
                Exp * exp = ((Let_statement *)running_statement)->expression;
                std::string name =((Let_statement *)running_statement)->id;
                int exp_val = calculation_exp(exp);
                symbol_table[name] = exp_val;//赋值就完事了
                break;
            }
            case statement_kind::Goto:
             {
                int dest= ((Goto_statement *)running_statement)->dest;
                //goto dest
                //设置i, 重新开始循环
                i = statement_list.find(dest);
                break;
             }
            case statement_kind::Input:
            {
                if(!rerun)
                {

                    input_a_val();//send signal
                    this->start_line = i->first; //保存当前的行数
                    return;// wait for rerun
                }
                else
                {
                    //保存读入的变量
                    std::string name =((Input_statement *)running_statement)->id;
                    this->symbol_table[name] = input;

                }
            }
        }
    }

}
int Runner:: calculation_exp(Exp *e)
{
    return 0;
}


void Runner::continue_runnning(int input)
{
    this->run(true, input);
}
