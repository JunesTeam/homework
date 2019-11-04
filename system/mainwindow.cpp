#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>     //数据库连接
#include <QMessageBox>
#include "globle.h"     //使用全局变量
#include <QSqlError>    //输出错误
#pragma execution_character_set("utf-8")    //防止出现中文乱码

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接数据库
    connectsql();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//连接数据库
void MainWindow::connectsql()
{
    //    QSqlDatabase db = QSqlDatabase::addDatabase("MYSQL");     //连接MySQL
    // 防止出现数据库连接错误
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
        QMessageBox::warning(this, "错误", db.lastError().text());
        QMessageBox::critical(this, "错误", "连接失败，请检查网络是否正确连接!", "确定");
        return ;
    }
}

//打开登录界面
void MainWindow::on_pushButton_login_clicked()
{
    //打开登录界面，并隐藏原界面，而不是选择关闭它
    this->close();
    s.show();
    //当子界面发送信号时，调用主界面的reshow()函数,注意应使用指针
}

