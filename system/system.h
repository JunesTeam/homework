#ifndef SYSTEM_H
#define SYSTEM_H

#include <QMainWindow>
#include "liststudent.h"
#include "listmaterial.h"
#include "leavesystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class System; }
QT_END_NAMESPACE

class System : public QMainWindow
{
    Q_OBJECT

public:
    System(QWidget *parent = nullptr);
    ~System();

signals:
    void sends2(QString str);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

//    void receiveData(QString str);     //接收来自登录界面的账号信息

    void on_pushButton_5_clicked();

private:
    Ui::System *ui;
    listStudent *list_stu;
    listmaterial *list_m;
    leaveSystem *leave1;

    QString data1;
};
#endif // SYSTEM_H
