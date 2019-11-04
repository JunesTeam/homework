#include "liststudent.h"
#include "ui_liststudent.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>           //获取记录
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlError>    //输出错误
#include "globle.h"     //使用全局变量
#pragma execution_character_set("utf-8")    //防止出现中文乱码

listStudent::listStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listStudent)
{
    ui->setupUi(this);

    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(sqlhost);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(sqlport);                 //连接数据库端口号
    db.setDatabaseName(sqlname);      //连接数据库名
    db.setUserName(sqluser);          //数据库用户名
    db.setPassword(sqlpass);   //数据库密码
    db.setDatabaseName(sqldataname); //使用system数据库
    }

    if(!db.open())
    {
        //弹出提示窗口提示连接失败
        QMessageBox::critical(this, "错误", "连接失败，请检查网络是否正确连接!", "确定");
//        return ;
    }

    //设置模型
    model = new QSqlTableModel();
    model->setTable("学员");  //指定使用哪个表

    //把model放在view
    ui->tableView->setModel(model);

//    model->setHeaderData(0, Qt::Horizontal, "姓名");

    //设置model的编辑模式，手动提交修改，修改后需要确定后才会修改到数据库
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString str = QString("学员队 = '%1'").arg(username_qj);
    model->setFilter(str);
    model->select();

    //设置view中的数据库不允许修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

listStudent::~listStudent()
{
    delete ui;
}

//响应查询按钮
void listStudent::on_pushButton_find_clicked()
{
    int index = ui->comboBox_method->currentIndex();
    QString note = ui->lineEdit_connect->text();
    QString str = "";

    switch (index) {
    case 0: //查找全部(只显示该学员队信息)
        str = QString("学员队 = '%1'").arg(username_qj);
        break;
    case 1:
        str = QString("姓名 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    case 2:
        str = QString("学号 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    case 3: //专业
        str = QString("专业 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    case 4: //班
        str = QString("班 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    case 5: //排
        str = QString("排 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    case 6: //职务
        str = QString("职务 = '%1' and 学员队 = '%2'").arg(note).arg(username_qj);
        break;
    default:
        str = QString("学员队 = '%1'").arg(username_qj);
        break;
    }

    model->setFilter(str);
    model->select();
}

//确认修改按钮
void listStudent::on_pushButton_sure_clicked()
{
    model->submitAll(); //提交动作
}

//取消修改按钮
void listStudent::on_pushButton_cancle_clicked()
{
    model->revertAll(); //取消所用动作
    model->submitAll(); //提交动作
}

//删除(通过点击行号)，可以选中多行删除(需要用到模型的概念：选中的多行就形成一个模型)
//将会同时删除学员、用户、请销假表格中的相关信息
void listStudent::on_pushButton_del_clicked()
{
    //使用默认连接
    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(sqlhost);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(sqlport);                 //连接数据库端口号
    db.setDatabaseName(sqlname);      //连接数据库名
    db.setUserName(sqluser);          //数据库用户名
    db.setPassword(sqlpass);   //数据库密码
    db.setDatabaseName(sqldataname); //使用system数据库
    }

    if(!db.open())
    {
        //弹出提示窗口提示连接失败
        QMessageBox::critical(this, "错误", "连接失败，请检查网络是否正确连接!", "确定");
//        return ;
    }

    QSqlQuery query(db);
    QVariantList ID;
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView->selectionModel();
    //取出模型中的索引(每条记录的索引集合)
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < list.size(); i++)
    {
        model->removeRow( list.at(i).row() );
        ID << model->record(list.at(i).row()).value(1).toString();  //获取学号
    }
//    qDebug() << ID;

    int ok = QMessageBox::warning(this, "删除选中行!", "你确定删除选中行吗（将会同时删除该用户的账号）？",
                        "确定", "取消");
    if(ok == 1)
    {
       model->revertAll();//如果不删除，则撤销
    }
    else {
        model->submitAll(); //否则提交，在数据库中删除该行

        //?表示一个占位符, prepare表示预处理语句
        query.prepare("delete from 用户 where 账号 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        query.prepare("delete from 请销假 where 学号 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        if (query.execBatch())     //执行预处理语句
            QMessageBox::warning(this, "成功!", "删除成功", "确定");
    }
    //重新显示查询结果
    on_pushButton_find_clicked();
}

//id属性，即第1列，升序排列
void listStudent::on_pushButton_sort_clicked()
{
    model->setSort(1,Qt::AscendingOrder);
    model->select();
}

//添加学员
void listStudent::on_pushButton_add_clicked()
{
    add = new addstudent();
    add->exec();
}

//void listStudent::receiveData2(QString str)
//{
//    data = str;
//}
