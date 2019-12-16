#include "admin.h"
#include "ui_admin.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QInputDialog>
#include "addstudent.h"
#include "globle.h"
#include "login.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
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
        return ;
    }

    //设置模型
    model = new QSqlTableModel();
    model->setTable("admin");  //指定使用哪个表
    model2 = new QSqlTableModel();
    model2->setTable("用户");  //指定使用哪个表

    //把model放在view
    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model2);

//    QString data = "12-6-29";
//    QString str = QString("学员队 = '%1' and 排 = '1'").arg(data);
//    model->setFilter(str);

    //显示model里的数据
    model->select();  //这样就把表中所有的数据显示成表格的样子在窗口中
    model2->select();  //这样就把表中所有的数据显示成表格的样子在窗口中
    //我们使用QSqlTableModel只能进行 SELECT * 的查询，不能只查询其中某些列的数据。

//    model->setHeaderData(0, Qt::Horizontal, "姓名");

    //设置model的编辑模式，手动提交修改，修改后需要确定后才会修改到数据库
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_add_clicked()
{
    //添加空记录,然后自己填写
    QSqlRecord record = model->record(); //获取空记录
    //或者
    //QSqlRecord record = tablemodel.record();
    //record.setValue("nam","new");

    //获取行号
    int row = model->rowCount();
    model->insertRecord(row, record);
}

void Admin::on_pushButton_ok_clicked()
{
    model->submitAll(); //提交动作
}

void Admin::on_pushButton_cal_clicked()
{
    model->revertAll(); //取消所用动作
    model->submitAll(); //提交动作
}

void Admin::on_pushButton_del_clicked()
{
    //使用默认连接
    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {
        db = QSqlDatabase::addDatabase("QPSQL");
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
        ID << model->record(list.at(i).row()).value(0).toString();  //获取账号
    }
//    qDebug() << ID;

    int ok = QMessageBox::warning(this, "删除选中行!", "你确定删除选中行吗（将会同时删除该学员队的所有信息）？",
                        "确定", "取消");
    if(ok == 1)
    {
       model->revertAll();//如果不删除，则撤销
    }
    else {
        model->submitAll(); //否则提交，在数据库中删除该行

        //?表示一个占位符, prepare表示预处理语句
        query.prepare("delete from 用户 where 学员队 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        query.prepare("delete from 请销假 where 学员队 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        query.prepare("delete from 物资 where 学员队 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        query.prepare("delete from 学员 where 学员队 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        if (query.execBatch())     //执行预处理语句
            QMessageBox::warning(this, "成功!", "删除成功", "确定");
    }
    //重新显示查询结果
    on_pushButton_clicked();
}

void Admin::on_pushButton_clicked()
{
    int index = ui->comboBox->currentIndex();
    QString data = ui->lineEdit->text();
    QString str = "";

    switch (index) {
    case 0: //查找全部
        str = "";
        break;
    case 1:
        str = QString("账号 = '%1'").arg(data);
        break;
    }

    model->setFilter(str);
    model->select();
}

void Admin::on_pushButton_sort_clicked()
{
    //按照账号进行排序
    model->setSort(0,Qt::AscendingOrder);
    model->select();
}

void Admin::on_pushButton_2_clicked()
{
    int index = ui->comboBox_2->currentIndex();
    QString data = ui->lineEdit_2->text();
    QString str = "";

    switch (index) {
    case 0: //查找全部
        str = "";
        break;
    case 1:
        str = QString("学员队 = '%1'").arg(data);
        break;
    }

    model2->setFilter(str);
    model2->select();
}

void Admin::on_pushButton_sort_2_clicked()
{
    //按照学员队进行排序
    model2->setSort(2,Qt::AscendingOrder);
    model2->select();
}

void Admin::on_pushButton_del_2_clicked()
{
    //使用默认连接
    QSqlDatabase db;   //连接postgreql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else    {
        db = QSqlDatabase::addDatabase("QPSQL");
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
    QItemSelectionModel *sModel2 =ui->tableView_2->selectionModel();
    //取出模型中的索引(每条记录的索引集合)
    QModelIndexList list = sModel2->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < list.size(); i++)
    {
        model2->removeRow( list.at(i).row() );
        ID << model2->record(list.at(i).row()).value(0).toString();  //获取账号
    }
    qDebug() << ID;

    int ok = QMessageBox::warning(this, "删除选中行!", "你确定删除选中行吗（将会同时删除该学员的所有信息）？",
                        "确定", "取消");
    if(ok == 1)
    {
       model2->revertAll();//如果不删除，则撤销
    }
    else {
        model2->submitAll(); //否则提交，在数据库中删除该行

        //?表示一个占位符, prepare表示预处理语句
        query.prepare("delete from 请销假 where 学号 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        query.prepare("delete from 学员 where 学号 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        if (query.execBatch())     //执行预处理语句
            QMessageBox::warning(this, "成功!", "删除成功", "确定");
    }
    //重新显示查询结果
    on_pushButton_2_clicked();
}

void Admin::on_pushButton_add_2_clicked()
{
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
        return ;
    }

    QSqlQuery query(db);    //这句话很重要！

    bool isOK;

    // 弹出带文本输入的窗口
    QString text = QInputDialog::getText(this,"输入","请输入该学员的学员队",
                                         QLineEdit::Normal,"1-1-1",&isOK);

    if(isOK){
        //判断是否存在
        QString str = QString("select * from admin where 账号 = '%1'").arg(text);
        query.exec(str);

//        qDebug() << text;

        if(query.next())
        {
            username_qj = text;

            addstudent *s = new addstudent();
            //打开添加学员界面
            s->exec();
        }
        else{
            QMessageBox::critical(this, "错误", "该学员队不存在!", "确定");
        }
    }
}

void Admin::on_pushButton_ok_2_clicked()
{
    model2->submitAll(); //提交动作
}

void Admin::on_pushButton_cal_2_clicked()
{
    model2->revertAll(); //取消所用动作
    model2->submitAll(); //提交动作
}

void Admin::on_pushButton_3_clicked()
{
    login *l = new login();
    l->show();
    this->close();
}
