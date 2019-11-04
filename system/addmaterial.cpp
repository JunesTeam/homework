#include "addmaterial.h"
#include "ui_addmaterial.h"
#include <QMessageBox>  //小提示窗口
#include <QPushButton>  //按钮
#include <QSqlQuery>    //对数据库进行操作
#include "globle.h"     //使用全局变量
#pragma execution_character_set("utf-8")    //防止出现中文乱码

addmaterial::addmaterial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmaterial)
{
    ui->setupUi(this);

    QSqlDatabase db;   //连接postgreql
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else {
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName(sqlhost);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
        db.setPort(sqlport);                 //连接数据库端口号
        db.setDatabaseName(sqlname);      //连接数据库名
        db.setUserName(sqluser);          //数据库用户名
        db.setPassword(sqlpass);   //数据库密码
        db.setDatabaseName(sqldataname); //使用system数据库
    }
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
    QString note = this->ui->lineEdit_note->text();        //备注SS

    if (note == "")
        note = "无";

    QString sql = QString("INSERT INTO 物资 (名称, 数量, 存放位置, 负责人, 备注, 学员队)"
                          "VALUES ('%1','%2','%3','%4','%5','%6')")
                  .arg(name).arg(num).arg(place).arg(fuze).arg(note).arg(username_qj);    //SQL语句

    //显示内容, QString::number(platoon)->int转QString
    QString connect = "名  称：" + name + "\n数  量：" + QString::number(num) + "\n存放位置：" +place + '\n'
            + "负责人 ：" + fuze + "\n备注:" + note + '\n';
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
            //开启一个事务
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.exec(sql);

            //确定添加
            QSqlDatabase::database().commit();
            QMessageBox::information(this, "成功", "物资添加成功", "确认");
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

