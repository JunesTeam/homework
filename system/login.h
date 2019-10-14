#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "system.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void clear();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::login *ui;
    System s;
};

#endif // LOGIN_H
