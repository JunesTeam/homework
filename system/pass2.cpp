#include "pass2.h"
#include "ui_pass2.h"
#include <QMessageBox>
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlDatabase>     //数据库连接
#include <QDebug>
#include "globle.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

pass2::pass2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pass2)
{
    ui->setupUi(this);
}

pass2::~pass2()
{
    delete ui;
}

void pass2::on_pushButton_2_clicked()
{
    this->close();
}

//void pass2::receiveData(QString str)
//{
//    this->num = str;
//}

void pass2::on_pushButton_clicked()
{
    QString p1 = ui->lineEdit->text();
    QString p2 = ui->lineEdit_2->text();
    QString p3 = ui->lineEdit_3->text();
    QString pass = "";

    //比较原密码
    QString sql = QString("select * from 用户 where 账号 = '%1'").arg(username_qj);

    //开启一个事务
    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {
        db = QSqlDatabase::addDatabase("QPSQL");
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
    if (query.next())
         pass = query.value("密码").toString();

    if (pass != p1)
    {
        QMessageBox::critical(this, "错误", "原密码错误", "确定");
//        qDebug() << pass << p1;
    }

    else if (p2 != p3)
        QMessageBox::warning(this, "警告", "两次输入密码不一致", "确定");

    else {
        sql =  QString("update 用户 set 密码 = '%1' where 账号 = '%2'").arg(p3).arg(username_qj);
        if (query.exec(sql))
            QMessageBox::information(this, "成功", "修改密码成功", "确定");
    }
}
