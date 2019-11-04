#include "studentform.h"
#include "ui_studentform.h"
#include <QApplication>
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlDatabase>     //数据库连接
#include <QDebug>
#include <login.h>
#include "leavesystem.h"
#include "globle.h"     //使用全局变量
#pragma execution_character_set("utf-8")    //防止出现中文乱码

studentForm::studentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentForm)
{
    ui->setupUi(this);

    //显示信息
    display();

//    //实现两个界面的通信，从而获取学号
//    connect(this, SIGNAL(sends(QString)), &lis, SLOT(receiveData(QString)));
//    //实现两个界面的通信，从而获取学号
//    connect(this, SIGNAL(sends(QString)), &lea, SLOT(receiveData(QString)));
//    connect(this, SIGNAL(sends(QString)), &pp, SLOT(receiveData(QString)));
}

studentForm::~studentForm()
{
    delete ui;
}

void studentForm::on_pushButton_xinxi_clicked()
{
    lis = new listuser();
    lis->show();
}

void studentForm::display()
{
//    emit sends(data);
    QString sql = QString("select * from 请销假 where 学号 = '%1'").arg(username_qj);
    QString text = "";

    //开启一个事务
    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(sqlhost);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(sqlport);                 //连接数据库端口号
    db.setDatabaseName(sqlname);      //连接数据库名
    db.setUserName(sqluser);          //数据库用户名
    db.setPassword(sqlpass);   //数据库密码
    db.setDatabaseName(sqldataname); //使用system数据库
    }

    if(!db.open())
    {
        //弹出提示窗口提示连接失败
        QMessageBox::critical(this, "错误", "连接失败，请检查网络是否正确连接!", "确定");
        return ;
    }

    QSqlQuery query(db);
    query.exec(sql);

    //根据学号 获取名字
    query.next();
    QString name = query.value(0).toString();

    text = QString(" %1，您好！\n").arg(name);

    ui->label_xinxi->setText(text);
}

void studentForm::on_pushButton_qingjia_clicked()
{
    lea = new leave_stu();
    lea->show();
}

void studentForm::on_pushButton_3_clicked()
{
    pp = new pass2();
    pp->show();
}

void studentForm::on_pushButton_clicked()
{
    this->close();
    login *a = new login();
    a->show();
}
