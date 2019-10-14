#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
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

    //判断是否登录成功
    static int count = 0;
    if (name == "123" && passwd == "123") { //登录成功，打开系统主界面，关闭本界面
        this->close();
        s.show();
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
