#include "listuser.h"
#include "ui_listuser.h"
#include "login.h"
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlDatabase>     //数据库连接
#include <QDebug>
#include "globle.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

listuser::listuser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listuser)
{
    ui->setupUi(this);

    //显示信息
    display();
}

listuser::~listuser()
{
    delete ui;
}

//打印信息到界面上
void listuser::display()
{
    QString sql = QString("select * from 学员 where 学号 = '%1'").arg(username_qj);
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
//        return ;
    }

    QSqlQuery query(db);
    query.exec(sql);
//    qDebug() << username_qj;

    if (query.next())   //跳过开头的空
    {
        QString name = query.value(0).toString();
        QString id = query.value(1).toString();
        QString sex = query.value("性别").toString();
        QString age = query.value("年龄").toString();
        QString major = query.value("专业").toString();
        int ban = query.value("班").toInt();
        int pai = query.value("排").toInt();
        QString job = query.value("职务").toString();
        QString dui = query.value("学员队").toString();

        sql = QString("select * from 请销假 where 学号 = '%1'").arg(username_qj);
        text = "";

        query.exec(sql);

        query.next();
        QString xin = query.value(2).toString();

        text = QString(" 姓名：%1\n 学号：%2\n 性别：%3\n 年龄：%4\n 专业：%5\n 班排：%6排%7班"
                       "\n 职务：%8\n 学员队：%9\n 当前请假状态：%10\n")
                .arg(name).arg(id).arg(sex).arg(age).arg(major).arg(pai).arg(ban).arg(job).arg(dui).arg(xin);

        ui->label_name->setText(text);
    }
}
