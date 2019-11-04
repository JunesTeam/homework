#ifndef LISTSTUDENT_H
#define LISTSTUDENT_H

#include <QDialog>
#include <QString>
#include <QSqlTableModel>
#include "addstudent.h"

namespace Ui {
class listStudent;
}

class listStudent : public QDialog
{
    Q_OBJECT

public:
    explicit listStudent(QWidget *parent = nullptr);
    ~listStudent();

//    QString data;     //使用public来传递数据

private slots:
    void on_pushButton_find_clicked();

    void on_pushButton_sure_clicked();

    void on_pushButton_cancle_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_add_clicked();

//    void receiveData2(QString str);     //接收来自管理端的账号信息

private:
    Ui::listStudent *ui;
    //表格模型
    QSqlTableModel *model;
    addstudent *add;
};

#endif // LISTSTUDENT_H
