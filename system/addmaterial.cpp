﻿#include "addmaterial.h"
#include "ui_addmaterial.h"
#include <QMessageBox>  //小提示窗口
#include <QPushButton>  //按钮
//读写文件流
#include <QFile>        //文件操作
#include <QTextStream>  //（文件）流式操作
#include <QIODevice>    //打开模式(文件)
#pragma execution_character_set("utf-8")    //防止出现中文乱码

addmaterial::addmaterial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmaterial)
{
    ui->setupUi(this);
}

addmaterial::~addmaterial()
{
    delete ui;
}

void addmaterial::on_pushButton_ok_clicked()
{
    //通过text函数获取文本信息
    QString name = this->ui->lineEdit_name->text(); //名称
    int num = this->ui->spinBox_num->value();   //数量
    QString place = this->ui->lineEdit_place->text();   //存放位置
    QString fuze = this->ui->lineEdit_name_fuze->text();   //负责人
    QString note = this->ui->lineEdit_note->text();        //备注

    if (note == "")
        note = "无";

    //显示内容, QString::number(platoon)->int转QString
    QString connect = "名  称：" + name + "\n数  量：" + QString::number(num) + "\n存放位置：" +place + '\n'
            + "负责人 ：" + fuze + "\n备注:" + note + '\n';
    //每种物资独占一行，方便读取文件（readline）,以逗号分隔开（csv文件）
    QString str = name + "," + QString::number(num) + "," +place + ','
             + fuze + "," + note + '\n';
    int ret = 0;        //返回值

    // 判断输入信息是否完整,响应事件后弹出一个小窗口(QMessageBox)
    // question/critical/information/warning(QWidget *parent, 标题，文本，按钮。。。) ，预定义样式，与前面功能相同
    if (name.length() < 1 || place.length() < 1){
        QMessageBox::critical(this, "错误", "信息输入不完整，请重新检查 ", "确认");
    }
    else{
        //获得返回值，从0开始计算，与定义按钮顺序相同，如点击确认返回0；
        ret = QMessageBox::question(this, "请确认信息：", connect, "取消", "确认");
        if (ret == 1) {
            QMessageBox::information(this, "成功", "物资添加成功", "确认");
            wToFile(str);   //写入文件
            clear();        //点击确认后，清除原先界面
        }
    }
}

//清除界面
void addmaterial::clear()
{
    //文本输入置为空
    this->ui->lineEdit_name->setText("");
    this->ui->lineEdit_name_fuze->setText("");
    this->ui->lineEdit_place->setText("");
    this->ui->lineEdit_note->setText("");

    this->ui->lineEdit_name->setFocus();    //设置焦点
}

void addmaterial::wToFile(QString str)
{
    //写入文件,若不存在自动创建，（../ 表示当前路径的上一级路径）
    //csv文件是以逗号为分隔符号，将各字段列分离出的一种ASCII文件。
    //数据列以逗号分隔，每一行数据都以回车符结束。如果单元格中包含逗号，则该单元格中的内容以双引号引起。
    QFile file("../system/data/meterial.csv");
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