/********************************************************************************
* File Name:	teacherform.cpp
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#include "teacherform.h"
#include "ui_teacherform.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>
#include <QTextStream>

teacherform::teacherform(QString name,QWidget *parent) :
    QWidget(parent),ui(new Ui::teacherform)
{
    ui->setupUi(this);
    Name = name;
    scoreInfoModel=new QSqlTableModel(this);
    scoreInfoModel->setTable("Score");
    scoreInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //修改提交过之后更新到数据库
    scoreInfoModel->select();
    //获取当前列 的索引
    scoreInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    scoreInfoModel->setHeaderData(1,Qt::Horizontal,tr("学生学号"));
    scoreInfoModel->setHeaderData(2,Qt::Horizontal,tr("类型"));
    scoreInfoModel->setHeaderData(3,Qt::Horizontal,tr("成绩"));
    ui->tvScore_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑
    ui->tvScore_2->setModel(scoreInfoModel);
    ui->tabWidget->setCurrentIndex(0);
}


teacherform::teacherform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherform)
{
    ui->setupUi(this);
}

teacherform::~teacherform()
{
    delete ui;
}

void teacherform::on_btnAdd_clicked()
{
    QString sub=ui->cbxType->currentText();
    QString ans=ui->cbxAns->currentText();
    int id;
    int maxid;
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"error","操作文件失败");
        return ;
    }
    QTextStream in(&file);
    QString temp=in.readAll();
    QSqlQuery  query;
    query.exec("select max(ID) from Question");
    if(query.next())
        maxid = query.value(0).toInt();
    id = maxid +1;
    query.exec("insert into Question values('"+QString::number(id)+"','"+sub+"','"+fileName+"','"+temp+"','"+ans+"')");
    on_btnRefresh_clicked();
}

void teacherform::on_btnDel_clicked()
{
    QString title = ui->lvTitle->currentIndex().data().toString();
    QSqlQuery query;
    query.exec("delete from Question where Title='"+title+"'");
    if(query.isActive())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message","Delete success!");
    }
    on_btnRefresh_clicked();
}

void teacherform::on_btnRefresh_clicked()
{
    QString sub=ui->cbxType->currentText();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select Title from Question where sub ='"+sub+"'");
    ui->lvTitle->setModel(model);
}

void teacherform::on_btnQuit_clicked()
{
    this->close();
}

void teacherform::on_lvTitle_clicked(QModelIndex index)
{
    QString title=index.data().toString();
    QString sub=ui->cbxType->currentText();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select Content from Question where Title ='"+title+"' and sub='"+sub+"'");

    ui->lvContent->setModel(model);
    //ui->listView_2->show();
}

void teacherform::on_btnSearch_2_clicked()
{
    scoreInfoModel->setFilter("StdNum="+ui->leStdNum_2->text());
    scoreInfoModel->select();
}

void teacherform::on_btnOk_3_clicked()
{
    if(ui->leOldPwd_3->text()==""||ui->leNewPwd_3->text()==""||ui->leNewPwd2_3->text()=="")
    {QMessageBox::about(this,"Message","item with * can't not be empty!");return ;}
    if(ui->leNewPwd_3->text()!=ui->leNewPwd2_3->text())
    {QMessageBox::about(this,"Message",tr("新密码和确认新密码不统一！"));return ;}
    QSqlQuery query;
    query.exec("update Teacher set PassWd='"+ui->leNewPwd_3->text()+"' WHERE Name='"+Name+"'");
    if(query.isActive())
    {
            query.numRowsAffected();
            QMessageBox::about(this,"message","success");
    }
}

void teacherform::on_btnQuit_3_clicked()
{
    this->close();
}
