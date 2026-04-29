/********************************************************************************
* File Name:	addthform.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "addthform.h"
#include "ui_addthform.h"
#include <QMessageBox>
#include <QSqlQuery>

addthform::addthform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addthform)
{
    ui->setupUi(this);
}

addthform::~addthform()
{
    delete ui;
}

void addthform::on_btnOk_clicked()
{
    if(ui->leID->text()==""||ui->leThNum->text()==""||ui->leName->text()==""||ui->lePwd->text()=="")
    {QMessageBox::about(this,"Message","item with * can't not be empty!");return ;}

     QSqlQuery query;
     query.prepare("SELECT COUNT(*) FROM Teacher WHERE ID=?");
     query.addBindValue(ui->leID->text());
     query.exec();

     int ID=0;
     if(query.next())
            ID = query.value(0).toInt();
     if(ID!=0)
     {
            QMessageBox::about(this,"Message","this ID existed!");
            QString maxNum ;
            query.exec("SELECT MAX(ID) FROM Teacher");
            if(query.next())
            {
                maxNum = query.value(0).toString();
            }
            QMessageBox::about(this,"Message","max ID="+maxNum);
            return ;
     }
     query.prepare("SELECT ID FROM Teacher WHERE Name=?");
     query.addBindValue(ui->leName->text());
     query.exec();
     if(query.next())
     {
         QMessageBox::about(this,"Message",tr("该用户已经存在！"));
         return ;
     }
     query.prepare("INSERT INTO Teacher VALUES(?,?,?,?)");
     query.addBindValue(ui->leID->text());
     query.addBindValue(ui->leThNum->text());
     query.addBindValue(ui->leName->text());
     query.addBindValue(ui->lePwd->text());
     if(query.exec())
     {
            query.numRowsAffected();
            QMessageBox::about(this,"message","add success");
     }

}

void addthform::on_btnQuit_clicked()
{
    this->close();
}
