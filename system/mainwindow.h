#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //连接数据库
    void connectsql();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    login s;   //登录界面
    QSqlDatabase db;    //数据库
};

#endif // MAINWINDOW_H
