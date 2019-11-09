#ifndef COMMAND_H
#define COMMAND_H


#include <QObject>
#include <QTextEdit>
#include <QWidget>

#include <QLabel>
class Command: public QTextEdit
{
    Q_OBJECT
public:
    Command(QWidget *parent = nullptr);
    bool is_inputting_variable;

signals:
    void newLineWritten(QString newline);
    void showCode( );
    void run();
    void input_finish(int input);

public slots:
    void write(QString msg);
    void set_is_inputtiing_variable();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    void process(QString s);
};

#endif // CONSOLE_H

