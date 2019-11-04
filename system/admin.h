#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_cal_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_clicked();

    void on_pushButton_sort_clicked();

private:
    Ui::Admin *ui;
    QSqlTableModel *model;
};

#endif // ADMIN_H
