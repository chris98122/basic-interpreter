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
signals:
    void newLineWritten(QString newline);

public slots:
    void write(QString msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    void process(QString s);
};

#endif // CONSOLE_H

