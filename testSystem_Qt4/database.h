/********************************************************************************
* File Name:	database.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>


static bool createConnection()
{

    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL"));
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("878455");
    db.setDatabaseName("mydb");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}
#endif // DATABASE_H

