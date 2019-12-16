#include "globle.h"

//用户
QString username_qj = "";
QString password_qj = "";

//数据库
QString sqlhost = "106.52.121.11";  //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
int sqlport = 8081;                 //连接数据库端口号
QString sqlname = "postgres";       //连接数据库名
QString sqluser = "postgres";       //数据库用户名
QString sqlpass = "postgres";       //数据库密码
QString sqldataname = "system";     //使用system数据库

//初始：
//main; mainwindow; login（登录）; admin（管理员端）;
//管理端：
//system（队干部端）; addmaterial（添加物资）; addstudent（添加学员）; leavesystem（请销假）; listmaterial（物资管理）;
//liststudent（人员管理）; pass1（修改密码）;
//用户端：
//studentform（学员端）; listuser（查看个人信息）; pass2（修改密码）; leave_stu（学员请假）

/*
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
*/
