/********************************************************************************
* File Name:	login.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "login.h"
#include "ui_login.h"
#include "adminform.h"
#include "teacherform.h"
#include "studentform.h"

#include <QtSql/QSqlQuery>
#include <qmessagebox.h>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lePwd->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}



void login::on_btnOk_clicked()
{

    bool flag = false;
    QString usrn,pwd,type;
    usrn=ui->leName->text();
    pwd=ui->lePwd->text();
    type=ui->cbxType->currentText();
    QSqlQuery query;
    if(type==tr("管理员"))
   {
        query.exec("select * from Usr ");
        while(query.next())
        {
            if(query.value(1).toString()==usrn&&query.value(2).toString()==pwd)
            {
                flag = true;
                adminform *a = new adminform;
                a->show();
                this->close();
            }
        }
    }
    else if(type==tr("教师"))
    {
        query.exec("select * from Teacher");
        while(query.next())
        {
            if(query.value(2).toString()==usrn&&query.value(3).toString()==pwd)
            {
                flag = true;
                teacherform *t = new teacherform(usrn);
                t->show();
                this->close();
            }
        }
    }
    else
    {
        query.exec("select * from Student");
        while(query.next())
        {
            if(query.value(2).toString()==usrn&&query.value(3).toString()==pwd)
            {
                flag = true;
                studentform *t = new studentform(usrn);
                t->show();
                this->close();
            }
        }
    }
    if(!flag)
        QMessageBox::warning(this,tr("Warning"),tr("Usrname or passwd is not wrong!"));

}

void login::on_btnQuit_clicked()
{
    this->close();
}
