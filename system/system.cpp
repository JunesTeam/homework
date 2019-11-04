#include "system.h"
#include "ui_system.h"
#include "login.h"
#include "pass1.h"
#include "globle.h"     //使用全局变量
#pragma execution_character_set("utf-8")    //防止出现中文乱码

System::System(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::System)
{
    ui->setupUi(this);

    //实现两个界面的通信，从而获取学号
//    connect(this, SIGNAL(sends2(QString)), &list_m, SLOT(receiveData(QString)));
//    connect(this, SIGNAL(sends2(QString)), &list_stu, SLOT(receiveData2(QString)));
//    connect(this, SIGNAL(sends2(QString)), &add_m, SLOT(receiveData(QString)));
//    connect(this, SIGNAL(sends2(QString)), &add_stu, SLOT(receiveData(QString)));
//    connect(this, SIGNAL(sends2(QString)), &lea, SLOT(receiveData(QString)));

    // 使用全局变量来接收其他界面的数据会更加不容易出错误。同时界面使用指针，在需要时才分配空间较好
    QString str = QString("学员队端(%1)").arg(username_qj);
    ui->label_2->setText(str);
}

System::~System()
{
    delete ui;
}

//转到学员管理界面
void System::on_pushButton_clicked()
{
    list_stu = new listStudent();
//    list_stu->data = data1;       //也可以使用public来传递数据
    list_stu->show();
}

//转到物资管理界面
void System::on_pushButton_2_clicked()
{
    list_m = new listmaterial();
    list_m->show();
}

//转到请销假系统界面
void System::on_pushButton_3_clicked()
{
    leave1 = new leaveSystem();
    leave1->show();
}

void System::on_pushButton_4_clicked()
{
    this->close();
    login *l = new login();
    l->show();
}

//接收账号数据
//void System::receiveData(QString data)
//{
//    emit sends2(data);
//    data1 = data;
//}

void System::on_pushButton_5_clicked()
{
    pass1 *p = new pass1();
    p->show();
}
