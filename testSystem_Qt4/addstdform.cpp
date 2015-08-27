/********************************************************************************
* File Name:	addstdform.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "addstdform.h"
#include "ui_addstdform.h"
#include <QMessageBox>
#include <QSqlQuery>

addstdform::addstdform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addstdform)
{
    ui->setupUi(this);
}

addstdform::~addstdform()
{
    delete ui;
}

void addstdform::on_btnOk_clicked()
{
    if(ui->leID->text()==""||ui->leStdNum->text()==""||ui->leName->text()==""||ui->lePwd->text()=="")
    {QMessageBox::about(this,"Message","item with * can't not be empty!");return ;}
     QSqlQuery query;
     query.exec("select count(*) from Student where ID='"+ui->leID->text()+"'");
     int ID=0;
     if(query.next())
            ID = query.value(0).toInt();
     if(ID!=0)
     {
            QMessageBox::about(this,"Message","this ID existed!");
            QString maxNum ;
            query.exec("select  ID from Student order by ID desc");
            if(query.next())
            {
                maxNum = query.value(0).toString();
            }
            QMessageBox::about(this,"Message","max ID="+maxNum);
            return ;
     }
     query.exec("select * from Student where Name='"+ui->leName->text()+"'");
     if(query.next())
     {
         QMessageBox::about(this,"Message",tr("该用户已经存在！"));
         return ;
     }
     query.exec("insert into Student values('"+ui->leID->text()+"','"+ui->leStdNum->text()+"','"+ui->leName->text()+"','"+ui->lePwd->text()+"')");
     if(query.isActive())
     {
            query.numRowsAffected();
            QMessageBox::about(this,"message","add success");
     }

}

void addstdform::on_btnQuit_clicked()
{
    this->close();
}
