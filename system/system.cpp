#include "system.h"
#include "ui_system.h"
#include "addmaterial.h"
#include "listmaterial.h"

System::System(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::System)
{
    ui->setupUi(this);
}

System::~System()
{
    delete ui;
}

//转到添加学员界面
void System::on_action_Stu_add_triggered()
{
//    add.show();   //同时可以使用其他窗口
    addstudent add;
    add.exec(); //模态视图，不关闭则无法使用其他窗口
}

//转到学员列表界面
void System::on_action_Stu_list_triggered()
{
    listStudent a;
    a.exec();
}

void System::on_action_triggered()
{
    addmaterial add_m;
    add_m.exec();
}

void System::on_action_2_triggered()
{
    listmaterial a;
    a.exec();
}
