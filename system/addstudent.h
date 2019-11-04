#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>

namespace Ui {
class addstudent;
}

class addstudent : public QDialog
{
    Q_OBJECT

public:
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();
    void clear();   //清除界面
    int wToSQL(QString str, QString str1, QString str2);  //写到文件中

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::addstudent *ui;
};

#endif // ADDSTUDENT_H
