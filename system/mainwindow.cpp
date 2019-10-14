#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开登录界面
void MainWindow::on_pushButton_login_clicked()
{
    //打开登录界面，并隐藏原界面，而不是选择关闭它
    this->close();
    s.show();
    //当子界面发送信号时，调用主界面的reshow()函数,注意应使用指针
}

