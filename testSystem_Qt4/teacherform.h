/********************************************************************************
* File Name:	teacherform.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef TEACHERFORM_H
#define TEACHERFORM_H

#include <QWidget>
#include <QModelIndex>
#include <QSqlTableModel>

namespace Ui {
    class teacherform;
}

class teacherform : public QWidget
{
    Q_OBJECT

public:
    explicit teacherform(QWidget *parent = 0);

    teacherform(QString name,QWidget *parent = 0);

    ~teacherform();

private:
    Ui::teacherform *ui;
    QSqlTableModel *scoreInfoModel;     //获取教师信息
    QString Name;
private slots:
    void on_btnQuit_3_clicked();
    void on_btnOk_3_clicked();
    void on_btnSearch_2_clicked();
    void on_lvTitle_clicked(QModelIndex index);
    void on_btnQuit_clicked();
    void on_btnRefresh_clicked();
    void on_btnDel_clicked();
    void on_btnAdd_clicked();
};

#endif // TEACHERFORM_H
