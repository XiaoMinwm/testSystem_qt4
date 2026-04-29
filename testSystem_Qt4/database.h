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
#include <QSettings>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>


static bool createConnection()
{
    // Read database credentials from db.conf (not committed to version control)
    QSettings settings("db.conf", QSettings::IniFormat);
    QString host     = settings.value("database/host",     "localhost").toString();
    QString user     = settings.value("database/user",     "").toString();
    QString password = settings.value("database/password", "").toString();
    QString dbname   = settings.value("database/dbname",   "mydb").toString();

    if (user.isEmpty()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             QObject::tr("Database credentials not configured. "
                                         "Please create db.conf based on db.conf.example."));
        return false;
    }

    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL"));
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(dbname);
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}
#endif // DATABASE_H

