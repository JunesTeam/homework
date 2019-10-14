#include "liststudent.h"
#include "ui_liststudent.h"
#include <QMessageBox>
#include <QTextStream>  //（文件）流式操作
#include <QIODevice>    //打开模式(文件)
#include <QDebug>
#include <QStringList>  //string容器
#pragma execution_character_set("utf-8")    //防止出现中文乱码

listStudent::listStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listStudent)
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

listStudent::~listStudent()
{
    delete ui;
}

//读取学生列表文件
int listStudent::rFromFlie()
{
    QFile file("../system/data/student.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //提示窗口提示未打开文件
        QMessageBox::critical(this, "错误", "未找到../system/data/student.csv文件，无法进行正确查询", "确定");
        return -1;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();   //每次读取一行
        list_stu.append(line);          //添加到列表中
    }

    file.close();

//    int i = 0;
//    for (i = 0; i < list_stu.length(); i++) {
//        qDebug() << list_stu.at(i);     //打印列表，确认是否读取进去
//    }

    return 0;
}

//响应查询按钮
void listStudent::on_pushButton_find_clicked()
{
    //每次查询前需要先清屏
    newTable();

    int index = this->ui->comboBox_method->currentIndex();  //获取查询方式下标
    QString str = this->ui->lineEdit_connect->text();       //获取查询文本

    //查询
    find(index, str);
}

//查询
void listStudent::find(int index, QString str)
{
    int i = 0;
    int row  = 0; //查询到的数据在表格中的行号，每查到一次加一
    for (i = 0; i < list_stu.length(); i++) {
        QString line = list_stu.at(i);
        QStringList subs = line.split(",");     //分割字符串,存进list列表中

        //subs(name, id, sex, age, major, platoon, squad, job)
        //index：name(1), id(2), major(3), squad(4), platoon(5)
        if (str == "") {         //全部显示
            display(row++, subs);
        }
        else {
            switch (index) {
            case 0:             //全部显示
                display(row++, subs);
                break;
            case 1: //姓名
                if (str == subs.at(0)){
                    display(row++, subs);
                }
                break;
            case 2: //学号
                if (str == subs.at(1)){
                    display(row++, subs);
                }
                break;
            case 3: //专业
                if (str == subs.at(4)){
                    display(row++, subs);
                }
                break;
            case 4: //班
                if (str == subs.at(6)){
                    display(row++, subs);
                }
                break;
            case 5: //排
                if (str == subs.at(5)){
                    display(row++, subs);
                }
                break;
            case 6: //职务
                if (str == subs.at(7)){
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
void listStudent::display(int raw, QStringList subs)
{
    int i = 0;
    //通过循环，将每一条数据取出，并存入表格中
    for (i = 0; i < subs.length(); i++)
    {
        this->model->setItem(raw, i, new QStandardItem(subs.at(i)) ); //设置不同单元格
    }
}

void listStudent::newTable()
{
    //清除原表格
    model->clear();

    //设置表头
    model->setHorizontalHeaderItem(0, new QStandardItem("姓名") );    //即设置第0列头部单元格为姓名
    model->setHorizontalHeaderItem(1, new QStandardItem("学号") );
    model->setHorizontalHeaderItem(2, new QStandardItem("性别") );
    model->setHorizontalHeaderItem(3, new QStandardItem("年龄") );
    model->setHorizontalHeaderItem(4, new QStandardItem("专业") );
    model->setHorizontalHeaderItem(5, new QStandardItem("排") );
    model->setHorizontalHeaderItem(6, new QStandardItem("班") );
    model->setHorizontalHeaderItem(7, new QStandardItem("职务") );

    //设置列宽
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,50);
    ui->tableView->setColumnWidth(4,200);
    ui->tableView->setColumnWidth(5,50);
    ui->tableView->setColumnWidth(6,50);
    ui->tableView->setColumnWidth(7,100);
}
