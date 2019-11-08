#include "Lexer.h"
#include <vector>
#include <sstream>

#include <QDebug>
std::vector<std::string> split(const std::string& s, char delimiter);
Lexer::Lexer()
{
    TOKEN_MAP["IF"] = token::IF;
    TOKEN_MAP["THEN"] = token::THEN;
    TOKEN_MAP["LET"] =token::LET;
    TOKEN_MAP["GOTO"] =token::GOTO;
    TOKEN_MAP["END"] =token::END;
    TOKEN_MAP["PRINT"] = token::PRINT;
    TOKEN_MAP["="] = token::ASSIGN;
    TOKEN_MAP[">"] = token::GT;
    TOKEN_MAP["<"] =token::LT;
    TOKEN_MAP["+"] =token::PLUS;
    TOKEN_MAP["-"] = token::MINUS;
    TOKEN_MAP["INPUT"] =token::INPUT;
}
std::list<token>
Lexer::lex_a_line(const std::string& input)
{
   //循环，每次split 空格
     qDebug()<< " lex_a_line";
     qDebug()<<  split("122",' ').size() ;
}
std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
