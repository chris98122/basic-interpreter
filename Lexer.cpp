#include "Lexer.h"
#include <vector>
#include <sstream>

#include <QString>
#include <QDebug>
bool isvalid_variable_name(std::string s);
Lexer::Lexer()
{
    TOKEN_MAP["IF"] = token::IF;
    TOKEN_MAP["THEN"] = token::THEN;
    TOKEN_MAP["LET"] = token::LET;
    TOKEN_MAP["GOTO"] = token::GOTO;
    TOKEN_MAP["END"] = token::END;
    TOKEN_MAP["PRINT"] = token::PRINT;
    TOKEN_MAP["="] = token::ASSIGN;
    TOKEN_MAP[">"] = token::GT;
    TOKEN_MAP["<"] = token::LT;
    TOKEN_MAP["+"] = token::PLUS;
    TOKEN_MAP["-"] = token::MINUS;
    TOKEN_MAP["*"] = token::MULTI;
    TOKEN_MAP["/"] = token::DIVIDE;
    TOKEN_MAP["INPUT"] = token::INPUT;
    TOKEN_MAP["REM"] = token::REM;
}
std::list<Token> * Lexer::lex_a_line(const std::string& input,bool *lex_ok , std::string *errormessage)
{
     //循环，每次split 空格
     std::list<Token> *result = new std::list<Token>;

     QString input_str( input.c_str());

     input_str.replace('='," = ");

     input_str.replace('+'," + ");

     input_str.replace('/'," / ");

     input_str.replace('*'," * ");
     input_str.replace('<'," < ");


     input_str.replace('>'," > ");

     QStringList split_str = input_str.split(" ");


     for(int i=0; i < split_str.size();i++)
     {
        //do the mapping
        if(this->TOKEN_MAP.find(split_str[i].toStdString()) != this->TOKEN_MAP.end())
        {
            //找到一样的
            if(TOKEN_MAP[split_str[i].toStdString()] == token::REM)//ignore remark
            {
                return NULL;
            }
            else
            {
                result->push_back(Token(TOKEN_MAP[split_str[i].toStdString()]));
                qDebug()<< split_str[i] ;
            }
        }
        else
        {
            //empty then 跳过
            if(split_str[i].isEmpty() || split_str[i] == "\n")
                 continue;

            //not a keyword
            //数字？
            bool ok;
            split_str[i].toInt(&ok);
            if(ok)
            {

                result->push_back(Token(token::INT,split_str[i].toInt(&ok)));
                qDebug()<< "INT"<<split_str[i] ;
                continue;
            }
            // ID?
            std:: string variable_name = split_str[i].toStdString();
            if( isvalid_variable_name(variable_name ) )//naming rules unknow
            {
                result->push_back(Token(token::ID));
                qDebug()<< "ID"<<split_str[i] ;
                continue;
            }
            else
            {
                    result->push_back(token::ERROR);
                    *errormessage =  "ERROR!Invalid variable name " + split_str[i].toStdString() ;
                    *lex_ok = false;
                     return result;
            }

        }
     }
     *lex_ok = true;
     return result;
}

bool isvalid_variable_name(std::string s)
{
    int size= s.size();
    if(!( (s[0] - 'A' >=0 && s[0] -'Z' <= 0  )|| (s[0] - 'a' >= 0 && s[0] -'z' <=0)))
    {
        return false;
    }
    for(int i=1;i<size;i++)
    {
        if(!( (s[i] - 'A' >=0 && s[i] -'Z' <= 0  )|| (s[i] - 'i' >= 0 && s[i] -'z' <=0) || (s[i] == '_') || (s[i] -'9' <=0 && s[i]-'0' >=0)))
            return false;
    }
    return true;
}
