/********************************************************************************
* File Name:	adminform.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
    class adminform;
}

class adminform : public QWidget
{
    Q_OBJECT

public:
    explicit adminform(QWidget *parent = 0);
    ~adminform();
    void init();

private:
    Ui::adminform *ui;
    QSqlTableModel *teacherInfoModel;     //获取教师信息
    QSqlTableModel *StudentInfoModel;    //获取学生信息

private slots:
    void on_btnRefresh_2_clicked();
    void on_btnDel_2_clicked();
    void on_btnAdd_2_clicked();
    void on_btnRefresh_clicked();
    void on_btnDel_clicked();
    void on_btnAdd_clicked();
    void on_pushButton_clicked();
};

#endif // ADMINFORM_H
