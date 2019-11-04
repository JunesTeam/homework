#include "leave_stu.h"
#include "ui_leave_stu.h"
#include <QDateTimeEdit>
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlDatabase>     //数据库连接
#include <QMessageBox>
#include <studentform.h>
#include <QDebug>
#include "globle.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

leave_stu::leave_stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::leave_stu)
{
    ui->setupUi(this);

    // 注意：日历是对应的是QDate，而非QTime。所以QDateEdit、QDateTimeEdit可以使用，而QTimeEdit并不能使用，也可通过设计界面勾选
    ui->dateTimeEdit_1->setCalendarPopup(true);  // 日历弹出
    ui->dateTimeEdit_2->setCalendarPopup(true);  // 日历弹出

    //将其设置为当前时间
    ui->dateTimeEdit_1->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

leave_stu::~leave_stu()
{
    delete ui;
}

//void leave_stu::receiveData(QString str)
//{
//    num = str;
//}

void leave_stu::on_pushButton_re_clicked()
{
    //将其设置为当前时间
    ui->dateTimeEdit_1->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    ui->lineEdit_num->setText("");
    ui->lineEdit_note->setText("");
    ui->lineEdit_reason->setText("");

    ui->lineEdit_reason->setFocus();
}

void leave_stu::on_pushButton_ok_clicked()
{
    QString reason = ui->lineEdit_reason->text();
    QString note = ui->lineEdit_note->text();
    QString phone = ui->lineEdit_num->text();
    QString d1 = ui->dateTimeEdit_1->dateTime().toString("yyyy-MM-dd hh:mm");
    QString d2 = ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm");

    QString sql = QString("update 请销假 set 请假状态 = '待批假', 联系电话 = '%1', 离队时间 = '%2', 归队时间 = '%3', 备注 = '%4', 原因 = '%5' where 学号 = '%6'")
            .arg(phone).arg(d1).arg(d2).arg(note).arg(reason).arg(username_qj);

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

    QSqlQuery query(db);
    //确定添加
    if (query.exec(sql))
    {
        QMessageBox::information(this, "成功", "申请成功", "确认");   //添加成功
        //关闭页面
        this->close();
    }
    else QMessageBox::information(this, "失败", "申请失败，请重试", "确认");     //打印错误

}
