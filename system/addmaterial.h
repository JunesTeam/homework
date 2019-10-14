#ifndef ADDMATERIAL_H
#define ADDMATERIAL_H

#include <QDialog>

namespace Ui {
class addmaterial;
}

class addmaterial : public QDialog
{
    Q_OBJECT

public:
    explicit addmaterial(QWidget *parent = nullptr);
    ~addmaterial();

    void clear();   //清除界面
    void wToFile(QString str);  //写到文件中

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::addmaterial *ui;
};

#endif // ADDMATERIAL_H
