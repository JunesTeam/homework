#include "listmaterial.h"
#include "ui_listmaterial.h"
#include <QMessageBox>
#include <QSqlRecord>
#include "addmaterial.h"
#include "globle.h"
#pragma execution_character_set("utf-8")    //防止出现中文乱码

listmaterial::listmaterial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listmaterial)
{
    ui->setupUi(this);

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

    //设置模型
    model = new QSqlTableModel();
    model->setTable("物资");  //指定使用哪个表

    //把model放在view
    ui->tableView->setModel(model);

//    model->setHeaderData(0, Qt::Horizontal, "姓名");

    //设置model的编辑模式，手动提交修改，修改后需要确定后才会修改到数据库
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置view中的数据库不允许修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

listmaterial::~listmaterial()
{
    delete ui;
}

//响应查询按钮
void listmaterial::on_pushButton_clicked()
{
    int index = ui->comboBox_method->currentIndex();
    QString data = ui->lineEdit_connect->text();
    QString str = "";

    switch (index) {
    case 0: //查找全部
        str = QString("学员队 = '%1'").arg(username_qj);
        break;
    case 1:
        str = QString("名称 = '%1' and 学员队 = '%2'").arg(data).arg(username_qj);
        break;
    case 2:
        str = QString("存放位置 = '%1' and 学员队 = '%2'").arg(data).arg(username_qj);
        break;
    case 3: //专业
        str = QString("负责人 = '%1' and 学员队 = '%2'").arg(data).arg(username_qj);
        break;
    default:
        str = QString("学员队 = '%1'").arg(username_qj);
        break;
    }

    model->setFilter(str);
    model->select();
}

void listmaterial::on_pushButton_del_clicked()
{
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView->selectionModel();
    //取出模型中的索引(每条记录的索引集合)
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < list.size(); i++)
    {
        model->removeRow( list.at(i).row() );
    }

    int ok = QMessageBox::warning(this, "删除选中行!", "你确定删除选中行吗？",
                        "确定", "取消");
    if(ok == 1)
    {
       model->revertAll();//如果不删除，则撤销
    }
    else model->submitAll(); //否则提交，在数据库中删除该行
}

void listmaterial::on_pushButton_sure_clicked()
{
    model->submitAll(); //提交动作
}

void listmaterial::on_pushButton_cancle_clicked()
{
    model->revertAll(); //取消所用动作
    model->submitAll(); //提交动作
}

void listmaterial::on_pushButton_add_clicked()
{
    addmaterial *add_m = new addmaterial();
    add_m->exec();
}
