/********************************************************************************
* File Name:	login.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
    class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private:
    Ui::login *ui;

private slots:
    void on_btnQuit_clicked();
    void on_btnOk_clicked();
};

#endif // LOGIN_H
