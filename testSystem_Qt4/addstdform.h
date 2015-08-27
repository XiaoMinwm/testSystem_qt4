/********************************************************************************
* File Name:	addstdform.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef ADDSTDFORM_H
#define ADDSTDFORM_H

#include <QWidget>

namespace Ui {
    class addstdform;
}

class addstdform : public QWidget
{
    Q_OBJECT

public:
    explicit addstdform(QWidget *parent = 0);
    ~addstdform();

private:
    Ui::addstdform *ui;

private slots:
    void on_btnQuit_clicked();
    void on_btnOk_clicked();
};

#endif // ADDSTDFORM_H
