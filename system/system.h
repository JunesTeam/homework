#ifndef SYSTEM_H
#define SYSTEM_H

#include <QMainWindow>
#include "addstudent.h"
#include "liststudent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class System; }
QT_END_NAMESPACE

class System : public QMainWindow
{
    Q_OBJECT

public:
    System(QWidget *parent = nullptr);
    ~System();

private slots:
    void on_action_Stu_add_triggered();

    void on_action_Stu_list_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::System *ui;

};
#endif // SYSTEM_H
