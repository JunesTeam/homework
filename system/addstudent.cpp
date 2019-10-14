#include "addstudent.h"
#include "ui_addstudent.h"
#include <QString>  //对text文本进行操作
#include <QDebug>   // 打印信息
#include <QMessageBox>  //小提示窗口
#include <QPushButton>  //按钮
//读写文件流
#include <QFile>        //文件操作
#include <QTextStream>  //（文件）流式操作
#include <QIODevice>    //打开模式(文件)
#pragma execution_character_set("utf-8")    //防止出现中文乱码

addstudent::addstudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addstudent)
{
    ui->setupUi(this);
}

addstudent::~addstudent()
{
    delete ui;
}

//添加学员
void addstudent::on_pushButton_ok_clicked()
{
    //通过text函数获取文本信息
    QString name = this->ui->lineEdit_name->text(); //姓名
    QString id = this->ui->lineEdit_id->text();     //学号
    QString job = this->ui->lineEdit_job->text();   //职务
    QString major = this->ui->lineEdit_major->text();   //专业
    QString sex = this->ui->sexGroup->checkedButton()->text(); //性别
    QString age = this->ui->comboBox_age->currentText();   //年龄
    int platoon = this->ui->spinBox_platoon->value();   //排
    int squad = this->ui->spinBox_squad->value();       //班

    //显示内容, QString::number(platoon)->int转QString
    QString connect = name + '\n' + id + '\n' + sex + '\n' + age + '\n' + major + '\n' +
            QString::number(platoon) + "排" + QString::number(squad) + "班\n" + job + '\n';
    //每个学生信息独占一行，方便读取文件（readline）,以逗号分隔开（csv文件）
    QString str = name + ',' + id + ',' + sex + ',' + age + ',' + major + ',' +
            QString::number(platoon) + "," + QString::number(squad) + "," + job + '\n';
    int ret = 0;        //返回值

    // 判断输入信息是否完整,响应事件后弹出一个小窗口(QMessageBox)
    // question/critical/information/warning(QWidget *parent, 标题，文本，按钮。。。) ，预定义样式，与前面功能相同
    if (name.length() < 1 || id.length() < 2){
        QMessageBox::critical(this, "错误", "信息输入不完整，请重新检查 ", "确认");
    }
    else{
        //获得返回值，从0开始计算，与定义按钮顺序相同，如点击确认返回0；
        ret = QMessageBox::question(this, "请确认信息：", connect, "取消", "确认");
        if (ret == 1) {
            QMessageBox::information(this, "成功", "人员添加成功", "确认");   //添加成功
            wToFile(str);   //写入文件
            clear();        //点击确认后，清除原先界面
        }
    }
}

//清除界面
void addstudent::clear()
{
    //文本输入置为空
    this->ui->lineEdit_name->setText("");
    this->ui->lineEdit_id->setText("");
    this->ui->lineEdit_job->setText("");
    this->ui->lineEdit_major->setText("");
    //单选按钮设置一个按钮默认
    this->ui->radioButton_male->setChecked(true);
    //下拉列表设置一个地址默认
    this->ui->comboBox_age->setCurrentIndex(0);

    this->ui->lineEdit_name->setFocus();    //设置焦点
}

void addstudent::wToFile(QString str)
{
    //写入文件,若不存在自动创建，（../ 表示当前路径的上一级路径）
    //csv文件是以逗号为分隔符号，将各字段列分离出的一种ASCII文件。
    //数据列以逗号分隔，每一行数据都以回车符结束。如果单元格中包含逗号，则该单元格中的内容以双引号引起。
    QFile file("../system/data/student.csv");
    //判断文件是否打，WriteOnly会把旧内容覆盖掉，防止覆盖，使用Append
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        //提示窗口提示未打开
        QMessageBox::critical(this, "错误", "文件打开失败，信息未保存！", "确定");
        return;
    }

    QTextStream out(&file); //实现流操作
    out << str;

    file.close();   //关闭文件
}
