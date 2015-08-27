/********************************************************************************
* File Name:	studentform.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "studentform.h"
#include "ui_studentform.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <qdatetime.h>
#include <stdlib.h>
#include <time.h>


studentform::studentform(QString n,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentform)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    stdName =n;
    QString stdNum;
    QString name;
    QString pwd;
    QString sub;
    QString score1;
    QSqlQuery query;
    query.exec("select * from Student where Name= '"+stdName+"'");
    while(query.next())
    {
        stdNum = query.value(1).toString();
        name = query.value(2).toString();
        pwd = query.value(3).toString();
        ui->textEdit->append(tr("学号：")+stdNum);
        ui->textEdit->append(tr("用户名：")+name);
        ui->textEdit->append(tr("密码：")+pwd);
    }
    query.exec("select * from Score where StdNum= '"+stdNum+"'");
    while(query.next())
    {
        sub = query.value(2).toString();
        score1 = query.value(3).toString();
        ui->textEdit->append(tr("科目：")+sub+tr("  成绩：")+score1);
    }

    /////////////////////////////////////////////////////////////////
    score = 0;
    currentNum = 0;
    questionNum = 20;
    currentTime = 0;
    for(int i =0;i<20;i++)
    {
        ans[i] = "";
        questionId[i]=0;
    }
    timer = new QTimer(this);
    ui->btnPrevious_3->setEnabled(false);
    ui->btnNext_3->setEnabled(false);
    ui->btnSubmit_3->setEnabled(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
}


studentform::studentform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentform)
{
    ui->setupUi(this);
}

studentform::~studentform()
{
    delete ui;
}

void studentform::timerUpDate()
{
    currentTime++;
    ui->leTime_3->setText(QString::number(currentTime));
}

void studentform::on_btnOk_2_clicked()
{
    if(ui->leOldPwd_2->text()==""||ui->leNewPwd_2->text()==""||ui->leNewPwd2_2->text()=="")
    {QMessageBox::about(this,"Message","item with * can't not be empty!");return ;}
    if(ui->leNewPwd_2->text()!=ui->leNewPwd2_2->text())
    {QMessageBox::about(this,"Message",tr("新密码和确认新密码不统一！"));return ;}
    QSqlQuery query;
    query.exec("update Student set PassWd='"+ui->leNewPwd_2->text()+"' WHERE Name='"+stdName+"'");
    if(query.isActive())
    {
            query.numRowsAffected();
            QMessageBox::about(this,"message","success");
    }
}

void studentform::on_btnQuit_2_clicked()
{
    this->close();
}

void studentform::on_btnStart_3_clicked()
{
    int num;
    timer->start(1000);
    ui->btnPrevious_3->setEnabled(true);
    ui->btnNext_3->setEnabled(true);
    ui->btnSubmit_3->setEnabled(true);
    ui->btnStart_3->setEnabled(false);

    QSqlQuery query;
    query.exec("select count(*) from Question");
    if(query.next())
        num = query.value(0).toInt();
    if(num>20)
    {
        srand((int)time(NULL));
        for(int i=0;i<20;i++)
        {
            questionId[i]=rand()%num;
        }
    }
    else
    {
        for(int i=0;i<num;i++)
             questionId[i]=i+1;
        questionNum = num;
    }
    currentNum =1;
    query.exec("select * from Question where ID='"+QString::number(questionId[0])+"'");
    ui->leQuestionID_3->setText(QString::number(currentNum));
    if(query.next())
        ui->textEdit_3->append(query.value(3).toString());

}

void studentform::on_btnSubmit_3_clicked()
{
    int maxID;
    QString stdNum;
    timer->stop();
    ui->btnSubmit_3->setEnabled(false);
    ui->btnStart_3->setEnabled(true);

    if(ui->rBtnA_3->isChecked())
        ans[currentNum-1] = "A";
    else if(ui->rBtnB_3->isChecked())
        ans[currentNum-1] = "B";
    else if(ui->rBtnC_3->isChecked())
        ans[currentNum-1] = "C";
    else
        ans[currentNum-1] = "D";

    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(questionId[currentNum-1])+"'");
    if(query.next())
        if(query.value(4).toString()==ans[currentNum-2])
            score = score +5;

    query.exec("select StdNum from Student where Name='"+stdName+"'");
    if(query.next())
        stdNum = query.value(0).toString();
    query.exec("select count(*) from Score ");
    if(query.next())
        maxID= query.value(0).toInt();
    query.exec("insert into Score values('"+QString::number(maxID+1)+"','"+stdNum+"','"+ui->cbxSub_3->currentText()+"','"+QString::number(score)+"')");
    ui->leScore_3->setText(QString::number(score));

}

void studentform::on_btnPrevious_3_clicked()
{
    if(currentNum<=1)
    {
        QMessageBox::warning(this,tr("Warning"),tr("这是第一道题！"));
        return;
    }
    ui->textEdit_3->clear();
    currentNum = currentNum-1;
    ui->leQuestionID_3->setText(QString::number(currentNum));
    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(questionId[currentNum-1])+"'");
    if(query.next())
    {
        ui->textEdit_3->append(query.value(3).toString());
        ui->leAns_3->setText(query.value(4).toString());
    }
    ui->leYourAns_3->setText(ans[currentNum-1]);
}

void studentform::on_btnNext_3_clicked()
{
    if(currentNum>=questionNum)
    {
        QMessageBox::warning(this,tr("Warning"),tr("这已经是最后一道题了！"));
        return;
    }
    if(ui->rBtnA_3->isChecked())
        ans[currentNum-1] = "A";
    else if(ui->rBtnB_3->isChecked())
        ans[currentNum-1] = "B";
    else if(ui->rBtnC_3->isChecked())
        ans[currentNum-1] = "C";
    else
        ans[currentNum-1] = "D";

    ui->textEdit_3->clear();
    currentNum = currentNum+1;
    ui->leQuestionID_3->setText(QString::number(currentNum));
    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(questionId[currentNum-1])+"'");
    if(query.next())
    {
        ui->textEdit_3->append(query.value(3).toString());
        if(query.value(4).toString()==ans[currentNum-2])
            score = score +5;
    }
    ui->leAns_3->setText("");
    ui->leYourAns_3->setText("");
}
