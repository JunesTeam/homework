#include "leavesystem.h"
#include "ui_leavesystem.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>           //获取记录
#include <QSqlQuery>    //对数据库进行操作
#include <QSqlError>    //输出错误
#include <QHeaderView>
#include "globle.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

leaveSystem::leaveSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::leaveSystem)
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

    //设置模型
    model = new QSqlTableModel();
    model->setTable("请销假");  //指定使用哪个表
    model2 = new QSqlTableModel();
    model2->setTable("请销假");  //指定使用哪个表

    //把model放在view
    ui->tableView_2->setModel(model);
    ui->tableView_3->setModel(model2);

    //设置model的编辑模式，手动提交修改，修改后需要确定后才会修改到数据库
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置view中的数据库不允许修改
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    ui->tableView_3->horizontalHeader()->setSelectionModel(QHeaderView::Stretch);

    /* 页面1：待批假*/
    pushButton_wait("待批假");

    /* 页面2：已批假*/
    QString str2 = QString("请假状态 = '已批假' and 学员队 = '%1'").arg(username_qj);
    //显示
    model2->setFilter(str2);
    model2->select();
}

leaveSystem::~leaveSystem()
{
    delete ui;
}

void leaveSystem::pushButton_wait(QString str)
{
    QString str1 = QString("请假状态 = '%1' and 学员队 = '%2'").arg(str).arg(username_qj);
    //显示
    model->setFilter(str1);
    model->select();
}

void leaveSystem::on_pushButton_pijia_clicked()
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
        return ;
    }

    QSqlQuery query(db);
    QVariantList ID;

    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_2->selectionModel();
    //取出模型中的索引(每条记录的索引集合)
    QModelIndexList list = sModel->selectedRows();
    //获取选中行的学号
    for(int i = 0; i < list.size(); i++)
    {
        ID << model->record(list.at(i).row()).value(1).toString();  //获取学号
    }

    int ok = QMessageBox::warning(this, "批假!", "您确定批假吗？", "确定", "取消");
    if(ok == 0)
    {
        //?表示一个占位符, prepare表示预处理语句
        query.prepare("update 请销假 set 请假状态 = '已批假' where 学号 = ?");
        query.addBindValue(ID); //成员类型：QVariantList，可批量处理
        if (query.execBatch())     //执行预处理语句
            QMessageBox::warning(this, "成功!", "批假成功", "确定");
    }
    //重新显示待批假
   pushButton_wait("待批假");
}

void leaveSystem::on_tabWidget_currentChanged(int index)
{
    if (index == 1)
    {
        /* 页面2：已批假*/
        QString str2 = QString("请假状态 = '已批假' and 学员队 = '%1'").arg(username_qj);
        //显示
        model2->setFilter(str2);
        model2->select();
    }
    else if(index == 0)
    {
        /* 页面1：待批假*/
        pushButton_wait("待批假");
    }
}
