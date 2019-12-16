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

    void on_pushButton_2_clicked();

    void on_pushButton_sort_2_clicked();

    void on_pushButton_del_2_clicked();

    void on_pushButton_add_2_clicked();

    void on_pushButton_ok_2_clicked();

    void on_pushButton_cal_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Admin *ui;
    QSqlTableModel *model;

    QSqlTableModel *model2;
};

#endif // ADMIN_H
