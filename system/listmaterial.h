#ifndef LISTMATERIAL_H
#define LISTMATERIAL_H

#include <QDialog>
#include <QFile>
#include <QList>    //列表操作
#include <QString>
//产生表格
#include <QStandardItem>    //标准表格单元格
#include <QStandardItemModel>    //标准表格模型

namespace Ui {
class listmaterial;
}

class listmaterial : public QDialog
{
    Q_OBJECT

public:
    explicit listmaterial(QWidget *parent = nullptr);
    ~listmaterial();

    //读取文件
    int rFromFlie();
    //查询
    void find(int index, QString str);
    //显示数据在表格中
    void display(int raw, QStringList subs);
    //初始化表格
    void newTable();

private slots:
    void on_pushButton_clicked();

private:
    Ui::listmaterial *ui;

    //物资列表
    QList<QString>  list;
    //表格模型
    QStandardItemModel *model;
};

#endif // LISTMATERIAL_H
