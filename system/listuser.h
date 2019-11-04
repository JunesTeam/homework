#ifndef LISTUSER_H
#define LISTUSER_H

#include <QWidget>
#include <QString>

namespace Ui {
class listuser;
}

class listuser : public QWidget
{
    Q_OBJECT

public:
    explicit listuser(QWidget *parent = nullptr);
    ~listuser();
    void display();

//private slots:
//    void receiveData(QString str);     //接收来自用户端的账号信息

private:
    Ui::listuser *ui;
//    QString data;
};

#endif // LISTUSER_H
