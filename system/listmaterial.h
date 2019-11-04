#ifndef LISTMATERIAL_H
#define LISTMATERIAL_H

#include <QDialog>
#include <QFile>
#include <QSqlTableModel>
#include <QString>

namespace Ui {
class listmaterial;
}

class listmaterial : public QDialog
{
    Q_OBJECT

public:
    explicit listmaterial(QWidget *parent = nullptr);
    ~listmaterial();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_sure_clicked();

    void on_pushButton_cancle_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::listmaterial *ui;

    //表格模型
    QSqlTableModel *model;
};

#endif // LISTMATERIAL_H
