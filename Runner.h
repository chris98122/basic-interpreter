#ifndef RUNNER_H
#define RUNNER_H

#include "Parser.h"


#include <QObject>

#include <QWidget>

class Runner: public QWidget
{
Q_OBJECT
public:
    Runner(){};
    Runner(std::map<int,Statement *> statement_list);

    std::map<std::string,int > symbol_table;

    std::map<int,Statement *> statement_list;

    void run(bool rerun,int input);
signals:
    void  input_a_val();
    void Commandprint(QString);
public slots:
    void continue_runnning(int input);

private:
    int start_line;
    int calculation_exp(Exp *e,bool *ok);
    int CalculationOpExp(int left , token op, int right);

};

#endif // RUNNER_H
