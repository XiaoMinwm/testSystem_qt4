/********************************************************************************
* File Name:	adminform.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "adminform.h"
#include "ui_adminform.h"

#include "addthform.h"
#include "addstdform.h"
#include "login.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

adminform::adminform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminform)
{
    ui->setupUi(this);
    //teacherInfoModel;
    //教师管理
    teacherInfoModel=new QSqlTableModel(this);
    teacherInfoModel->setTable("Teacher");
    teacherInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //修改提交过之后更新到数据库
    teacherInfoModel->select();
    //获取当前列 的索引
    teacherInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    teacherInfoModel->setHeaderData(1,Qt::Horizontal,tr("教师编号"));
    teacherInfoModel->setHeaderData(2,Qt::Horizontal,tr("用户名"));
    teacherInfoModel->setHeaderData(3,Qt::Horizontal,tr("用户密码"));
    ui->tvTeacher->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑
    ui->tvTeacher->setModel(teacherInfoModel);

    //StudentInfoModel;
    //学生管理
    StudentInfoModel=new QSqlTableModel(this);
    StudentInfoModel->setTable("Student");
    StudentInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //修改提交过之后更新到数据库
    StudentInfoModel->select();
    //获取当前列 的索引
    StudentInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    StudentInfoModel->setHeaderData(1,Qt::Horizontal,tr("学生编号"));
    StudentInfoModel->setHeaderData(2,Qt::Horizontal,tr("用户名"));
    StudentInfoModel->setHeaderData(3,Qt::Horizontal,tr("用户密码"));
    ui->tvStudent_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑
    ui->tvStudent_2->setModel(StudentInfoModel);

    ui->tabWidget->setCurrentIndex(0);
}

adminform::~adminform()
{
    delete ui;
}

void adminform::on_btnAdd_clicked()
{
    addthform *addth = new addthform;
    addth->show();
}

void adminform::on_btnDel_clicked()
{
    QString ID=ui->tvTeacher->currentIndex().data().toString();
    qDebug()<<ID;
    QSqlQuery query;
    query.exec("delete from Teacher where ID ='"+ID+"'");
    if(query.isActive())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message","Delete success!");
    }
    init();
}

void adminform::on_btnRefresh_clicked()
{
    init();
}

void adminform::on_btnAdd_2_clicked()
{
    addstdform *addstd = new addstdform;
    addstd->show();
}

void adminform::on_btnDel_2_clicked()
{
    QString ID=ui->tvStudent_2->currentIndex().data().toString();
    qDebug()<<ID;
    QSqlQuery query;
    query.exec("delete from Student where ID ='"+ID+"'");
    if(query.isActive())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message","Delete success!");
    }
    init();
}

void adminform::on_btnRefresh_2_clicked()
{
    init();
}
void adminform::init()
{
    teacherInfoModel->select();
    StudentInfoModel->select();
}

void adminform::on_pushButton_clicked()
{
    login *lg = new login;
    lg->show();
    this->close();
}
