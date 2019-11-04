#include "addstudent.h"
#include "ui_addstudent.h"
#include <QString>  //对text文本进行操作
#include <QDebug>   // 打印信息
#include <QMessageBox>  //小提示窗口
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlError>    //输出错误
#include "globle.h"     //使用全局变量
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
    QString sql = QString("INSERT INTO 学员 (姓名, 学号, 性别, 专业, 排, 班, 职务, 年龄, 学员队)"
                          "VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
                  .arg(name).arg(id).arg(sex).arg(major).arg(platoon).arg(squad).arg(job).arg(age).arg(username_qj);    //SQL语句
    QString sql1 = QString("INSERT INTO 请销假 (姓名, 学号, 请假状态, 学员队)"
                          "VALUES ('%1','%2','%3','%4')").arg(name).arg(id).arg("未请假").arg(username_qj);   //SQL
    QString sql2 = QString("INSERT INTO 用户 (账号, 密码, 用户名, 学员队)"
                          "VALUES ('%1','%2','%3','%4')").arg(id).arg("12345").arg(name).arg(username_qj);     //SQL

    //显示内容, QString::number(platoon)->int转QString
    QString connect = name + '\n' + id + '\n' + sex + '\n' + age + '\n' + major + '\n' +
            QString::number(platoon) + "排" + QString::number(squad) + "班\n" + job + '\n';
    int ret = 0;        //返回值

    // 判断输入信息是否完整,响应事件后弹出一个小窗口(QMessageBox)
    // question/critical/information/warning(QWidget *parent, 标题，文本，按钮。。。) ，预定义样式，与前面功能相同
    if (name.length() < 1 || id.length() < 2 || major.length() < 2 || job.length() < 2){
        QMessageBox::critical(this, "错误", "信息输入不完整，请重新检查 ", "确认");
    }
    else{
        ret = QMessageBox::question(this, "请确认信息：", connect, "确认", "取消");
        if (!ret)
        {
            if (wToSQL(sql, sql1, sql2))    //写到数据库中
                QMessageBox::information(this, "成功", "人员添加成功", "确认");   //添加成功
            else QMessageBox::information(this, "错误", "人员已存在", "确认");     //打印错误
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

//写到数据库中
int addstudent::wToSQL(QString str, QString str1, QString str2)
{
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
    if (!query.exec(str1))
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return 0;
    }
    //添加到请销假表格中
    if (!query.exec(str2))
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return 0;
    }
    //为其添加用户登录账号，账号即学号，初始密码：12345

    //确定添加
    //添加到学员表格中
    if (!query.exec(str))
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return 0;
    }
    clear();        //点击确认后，清除原先界面
    return 1;
}
