#ifndef PASS2_H
#define PASS2_H

#include <QWidget>
#include <QString>

namespace Ui {
class pass2;
}

class pass2 : public QWidget
{
    Q_OBJECT

public:
    explicit pass2(QWidget *parent = nullptr);
    ~pass2();

//private slots:
//    void receiveData(QString str);     //接收来自用户端的账号信息

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::pass2 *ui;
//    QString num;
};

#endif // PASS2_H
