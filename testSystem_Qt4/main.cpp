/********************************************************************************
* File Name:	main.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include <QtGui/QApplication>
#include "login.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QTextCodec>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec=QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForCStrings(codec);
    codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForTr(codec);
    if(!createConnection())
    {
        qWarning("Database Error");
        return 0;
    }
    login w;
    w.show();

    return a.exec();
}
