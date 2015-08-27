/********************************************************************************
* File Name:	addthform.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef ADDTHFORM_H
#define ADDTHFORM_H

#include <QWidget>

namespace Ui {
    class addthform;
}

class addthform : public QWidget
{
    Q_OBJECT

public:
    explicit addthform(QWidget *parent = 0);
    ~addthform();

private:
    Ui::addthform *ui;

private slots:
    void on_btnQuit_clicked();
    void on_btnOk_clicked();
};

#endif // ADDTHFORM_H
