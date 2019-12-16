#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QWidget>
#include "listuser.h"
#include "leave_stu.h"
#include <pass2.h>

namespace Ui {
class studentForm;
}

class studentForm : public QWidget
{
    Q_OBJECT

public:
    explicit studentForm(QWidget *parent = nullptr);
    ~studentForm();

//signals:
//    void sends(QString str);

private slots:
    void on_pushButton_xinxi_clicked();

    void display();     //显示信息

    void on_pushButton_qingjia_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_xiaojia_clicked();

private:
    Ui::studentForm *ui;
    listuser *lis;
    leave_stu *lea;
    pass2 *pp;
};

#endif // STUDENTFORM_H
