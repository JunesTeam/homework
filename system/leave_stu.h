#ifndef LEAVE_STU_H
#define LEAVE_STU_H

#include <QWidget>
#include <QString>

namespace Ui {
class leave_stu;
}

class leave_stu : public QWidget
{
    Q_OBJECT

public:
    explicit leave_stu(QWidget *parent = nullptr);
    ~leave_stu();

private slots:
//    void receiveData(QString str);     //接收来自用户端的账号信息

    void on_pushButton_re_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::leave_stu *ui;
//    QString num;
};

#endif // LEAVE_STU_H
