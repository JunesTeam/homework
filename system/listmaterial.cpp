#include "listmaterial.h"
#include "ui_listmaterial.h"
#include <QMessageBox>
#include <QTextStream>  //（文件）流式操作
#include <QIODevice>    //打开模式(文件)
#include <QDebug>
#include <QStringList>  //string容器
#pragma execution_character_set("utf-8")    //防止出现中文乱码

listmaterial::listmaterial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listmaterial)
{
    ui->setupUi(this);
    // 界面出来时，文件就应该已经读好
    if (rFromFlie() == -1) {
        this->close();  //未打开文件，关闭窗口
    }

    //构造函数中将表格具体化，设置表头
    model = new QStandardItemModel;
    //将表格模型设置为界面中的表格
    ui->tableView->setModel(model);
    //初始化表格
    newTable();
}

listmaterial::~listmaterial()
{
    delete ui;
}

//读取物资列表文件
int listmaterial::rFromFlie()
{
    QFile file("../system/data/material.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //提示窗口提示未打开文件
        QMessageBox::critical(this, "错误", "未找到../system/data/material.csv文件，无法进行正确查询", "确定");
        return -1;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();   //每次读取一行
        list.append(line);          //添加到列表中
    }

    file.close();

    return 0;
}

//响应查询按钮
void listmaterial::on_pushButton_clicked()
{
    //每次查询前需要先清屏
    newTable();

    int index = this->ui->comboBox_method->currentIndex();  //获取查询方式下标
    QString str = this->ui->lineEdit_connect->text();       //获取查询文本

    //查询
    find(index, str);
}

//查询
void listmaterial::find(int index, QString str)
{
    int i = 0;
    int row  = 0; //查询到的数据在表格中的行号，每查到一次加一
    for (i = 0; i < list.length(); i++) {
        QString line = list.at(i);
        QStringList subs = line.split(",");     //分割字符串,存进list列表中

        //material(name, num, place, fuze, note)
        //index：name(1), place(2), fuze(3)
        if (str == "") {         //全部显示
            display(row++, subs);
        }
        else {
            switch (index) {
            case 0:             //全部显示
                display(row++, subs);
                break;
            case 1: //名称
                if (str == subs.at(0)){
                    display(row++, subs);
                }
                break;
            case 2: //存放位置
                if (str == subs.at(2)){
                    display(row++, subs);
                }
                break;
            case 3: //负责人
                if (str == subs.at(3)){
                    display(row++, subs);
                }
                break;
            default:
                break;
            }
        }
    }
}

//显示数据在表格中
void listmaterial::display(int raw, QStringList subs)
{
    int i = 0;
    //通过循环，将每一条数据取出，并存入表格中
    for (i = 0; i < subs.length(); i++)
    {
        this->model->setItem(raw, i, new QStandardItem(subs.at(i)) ); //设置不同单元格
    }
}

void listmaterial::newTable()
{
    //清除原表格
    model->clear();

    //设置表头
    model->setHorizontalHeaderItem(0, new QStandardItem("名称") );    //即设置第0列头部单元格为名称
    model->setHorizontalHeaderItem(1, new QStandardItem("数量") );
    model->setHorizontalHeaderItem(2, new QStandardItem("存放位置") );
    model->setHorizontalHeaderItem(3, new QStandardItem("负责人") );
    model->setHorizontalHeaderItem(4, new QStandardItem("备注") );

    //设置列宽
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,100);
    ui->tableView->setColumnWidth(4,200);
}
