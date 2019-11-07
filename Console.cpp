#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

#include <QTextEdit>
Console::Console(QWidget *parent) : QTextEdit(parent)
{
    this->document ()->setMaximumBlockCount (1000);

}


void Console::write(QString msg)
{
    this->append(msg);
}



void Console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
        {
        QTextCursor cursor = this->textCursor();
        qDebug(std::to_string( cursor.columnNumber() ).c_str());
        if(cursor.columnNumber()  <= 2) return;

        cursor.clearSelection();
        cursor.deletePreviousChar();
        this->setTextCursor(cursor);
        this->show();
        }
    else if (event->key() == Qt::Key_Return) {
        int rownum = this->document()->lineCount();
        QString index =  std::to_string(rownum+1).c_str();

        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        QString lastLine = cursor.selectedText();
        this->write(index +  " " +lastLine);
    }
    else
    QTextEdit::keyPressEvent(event);
}
