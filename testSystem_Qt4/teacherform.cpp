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
#include <QRegExp>
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
    query.exec("SELECT MAX(ID) FROM Question");
    if(query.next())
        maxid = query.value(0).toInt();
    id = maxid +1;
    query.prepare("INSERT INTO Question VALUES(?,?,?,?,?)");
    query.addBindValue(id);
    query.addBindValue(sub);
    query.addBindValue(fileName);
    query.addBindValue(temp);
    query.addBindValue(ans);
    query.exec();
    on_btnRefresh_clicked();
}

void teacherform::on_btnDel_clicked()
{
    QString title = ui->lvTitle->currentIndex().data().toString();
    QSqlQuery query;
    query.prepare("DELETE FROM Question WHERE Title=?");
    query.addBindValue(title);
    if(query.exec())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message","Delete success!");
    }
    on_btnRefresh_clicked();
}

void teacherform::on_btnRefresh_clicked()
{
    QString sub=ui->cbxType->currentText();
    QSqlQuery query;
    query.prepare("SELECT Title FROM Question WHERE sub=?");
    query.addBindValue(sub);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
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

    QSqlQuery query;
    query.prepare("SELECT Content FROM Question WHERE Title=? AND sub=?");
    query.addBindValue(title);
    query.addBindValue(sub);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->lvContent->setModel(model);
}

void teacherform::on_btnSearch_2_clicked()
{
    QString stdNum = ui->leStdNum_2->text().trimmed();
    // Validate that student number contains only alphanumeric characters
    // to prevent SQL injection via setFilter() which does not support binding
    static QRegExp validStdNum("^[A-Za-z0-9]+$");
    if (!stdNum.isEmpty() && !validStdNum.exactMatch(stdNum)) {
        QMessageBox::warning(this, tr("Input Error"), tr("学号只能包含字母和数字！"));
        return;
    }
    if (stdNum.isEmpty())
        scoreInfoModel->setFilter("");
    else
        scoreInfoModel->setFilter(QString("StdNum='%1'").arg(stdNum));
    scoreInfoModel->select();
}

void teacherform::on_btnOk_3_clicked()
{
    if(ui->leOldPwd_3->text()==""||ui->leNewPwd_3->text()==""||ui->leNewPwd2_3->text()=="")
    {QMessageBox::about(this,"Message","item with * can't not be empty!");return ;}
    if(ui->leNewPwd_3->text()!=ui->leNewPwd2_3->text())
    {QMessageBox::about(this,"Message",tr("新密码和确认新密码不统一！"));return ;}
    // Verify old password before updating
    QSqlQuery query;
    query.prepare("SELECT ID FROM Teacher WHERE Name=? AND PassWd=?");
    query.addBindValue(Name);
    query.addBindValue(ui->leOldPwd_3->text());
    if(!query.exec() || !query.next())
    {
        QMessageBox::about(this,"Message",tr("旧密码错误！"));
        return;
    }
    query.prepare("UPDATE Teacher SET PassWd=? WHERE Name=?");
    query.addBindValue(ui->leNewPwd_3->text());
    query.addBindValue(Name);
    if(query.exec())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message","success");
    }
}

void teacherform::on_btnQuit_3_clicked()
{
    this->close();
}
