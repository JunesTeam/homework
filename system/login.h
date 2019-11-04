#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "system.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "studentform.h"
#include "admin.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void clear();

//signals:
//    void sendData(QString str);     //利用信号在两个界面之间传递数据
//    void sendData2(QString str);     //利用信号在两个界面之间传递数据

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::login *ui;
//    界面使用指针，在需要时才分配空间较好
    System *s;          //学员队界面
    studentForm *stu;   //学员界面
    Admin *ad;          //管理员界面
};

#endif // LOGIN_H
