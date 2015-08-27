/********************************************************************************
* File Name:	studentform.h
* Description:	第9章实例训练
* Reference book:《Linux环境下Qt4图形界面与MySQL编程》，机械工业出版社.2012.1
* E_mail: openlinux2011@gmail.com
*
********************************************************************************/
#ifndef STUDENTFORM_H
#define STUDENTFORM_H
#include <QTimer>
#include <QWidget>

namespace Ui {
    class studentform;
}

class studentform : public QWidget
{
    Q_OBJECT

public:
    explicit studentform(QWidget *parent = 0);
    studentform(QString name,QWidget *parent = 0);
    ~studentform();

private:
    Ui::studentform *ui;
    QString stdName;
    QTimer *timer;
    int questionId[20];
    QString ans[20];
    int questionNum;
    int currentNum;
    int currentTime;
    int score;


private slots:
    void on_btnNext_3_clicked();
    void on_btnPrevious_3_clicked();
    void on_btnSubmit_3_clicked();
    void on_btnStart_3_clicked();
    void on_btnQuit_2_clicked();
    void on_btnOk_2_clicked();
    void timerUpDate();
    void on_tabWidget_tabBarClicked(int index);
    void on_textEdit_textChanged();
};

#endif // STUDENTFORM_H
