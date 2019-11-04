#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "globle.h"     //使用全局变量
#pragma execution_character_set("utf-8")    //防止出现中文乱码

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //实现两个界面的通信，从而获取学号
//    connect(this, SIGNAL(sendData(QString)), &stu, SLOT(receiveData(QString)));
//    connect(this, SIGNAL(sendData2(QString)), &s, SLOT(receiveData(QString)));
}

login::~login()
{
    delete ui;
}

//判断是否登录成功
void login::on_pushButton_login_clicked()
{
    //获取账号、密码
    QString name = this->ui->lineEdit_name->text();
    QString passwd = this->ui->lineEdit_passwd->text();

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

    QSqlQuery query(db);    //这句话很重要！

    //学员队登录
    if (ui->radioButton_admin->isChecked()) {
        //判断是否登录成功
        QString str = "select * from admin";
        static int count = 0;

        query.exec(str);

        bool T = false;

        while(query.next())
        {
            QString user = query.value(0).toString();
            QString pass = query.value(1).toString();
            //账号密码均匹配
            if (!name.compare(user) && !passwd.compare(pass))
            {
                //向下一个界面发送信息
//                emit sendData(name);

                T = true;

                username_qj = name;
                password_qj = passwd;

                s = new System();
                //打开用户端
                s->show();
                this->close();
            }
        }
        //账号密码不对
        if (T == false) {
            clear();
            count++;
            //提示窗口提示密码错误
            QMessageBox::critical(this, "错误", "用户名或密码错误!", "确定");
            if (count >= 3){    //失败次数超过三次，断开登录连接
                QMessageBox::critical(this, "错误", "输入错误超过三次，已冻结登录功能!", "确定");
                disconnect(this->ui->pushButton_login, SIGNAL(clicked()), this, SLOT(on_pushButton_login_clicked()));
            }
        }
    }

    //用户登录
    else if (ui->radioButton_user->isChecked()) {
        //判断是否登录成功
        QString str = "select * from 用户";
        static int count = 0;

        query.exec(str);

        bool T = false;

        while(query.next())
        {
            QString user = query.value(0).toString();
            QString pass = query.value(1).toString();
            //账号密码均匹配
            if (!name.compare(user) && !passwd.compare(pass))
            {
                //向下一个界面发送信息
//                emit sendData(name);
                username_qj = name;
                password_qj = passwd;

                stu = new studentForm();

                T = true;

                //打开用户端
                stu->show();
                this->close();
            }
        }
        //账号密码不对
        if (T == false) {
            clear();
            count++;
            //提示窗口提示密码错误
            QMessageBox::critical(this, "错误", "用户名或密码错误!", "确定");
            if (count >= 3){    //失败次数超过三次，断开登录连接
                QMessageBox::critical(this, "错误", "输入错误超过三次，已冻结登录功能!", "确定");
                disconnect(this->ui->pushButton_login, SIGNAL(clicked()), this, SLOT(on_pushButton_login_clicked()));
            }
        }
    }
    //管理员登录
    else {
        //判断是否登录成功
        static int count = 0;
        if (name == "admin" && passwd == "admin") { //登录成功，打开系统主界面，关闭本界面
            this->close();
//            emit sendData2(name);
            username_qj = name;
            password_qj = passwd;
            ad = new Admin();
            ad->show();
            this->close();
        }
        else {
            clear();
            count++;
            //提示窗口提示密码错误
            QMessageBox::critical(this, "错误", "密码输入错误!", "确定");
            if (count >= 3){    //失败次数超过三次，断开登录连接
                QMessageBox::critical(this, "错误", "输入错误超过三次，已冻结登录功能!", "确定");
                disconnect(this->ui->pushButton_login, SIGNAL(clicked()), this, SLOT(on_pushButton_login_clicked()));
            }
        }
    }
}

//显示初始界面，同时关闭本界面
void login::on_pushButton_return_clicked()
{
    MainWindow *a;
    a = new MainWindow;
    a->show();
    this->close();
}

//清除界面
void login::clear()
{
    //文本输入置为空
    this->ui->lineEdit_name->setText("");
    this->ui->lineEdit_passwd->setText("");

    this->ui->lineEdit_name->setFocus();    //设置焦点
}
