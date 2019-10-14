#ifndef LISTSTUDENT_H
#define LISTSTUDENT_H

#include <QDialog>
#include <QFile>
#include <QList>    //列表操作
#include <QString>
//产生表格
#include <QStandardItem>    //标准表格单元格
#include <QStandardItemModel>    //标准表格模型

namespace Ui {
class listStudent;
}

class listStudent : public QDialog
{
    Q_OBJECT

public:
    explicit listStudent(QWidget *parent = nullptr);
    ~listStudent();

    //读取文件
    int rFromFlie();
    //查询
    void find(int index, QString str);
    //显示数据在表格中
    void display(int raw, QStringList subs);
    //初始化表格
    void newTable();

private slots:
    void on_pushButton_find_clicked();

private:
    Ui::listStudent *ui;
    //学员列表
    QList<QString>  list_stu;
    //表格模型
    QStandardItemModel *model;
};

#endif // LISTSTUDENT_H
