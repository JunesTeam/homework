#ifndef PASS1_H
#define PASS1_H

#include <QWidget>

namespace Ui {
class pass1;
}

class pass1 : public QWidget
{
    Q_OBJECT

public:
    explicit pass1(QWidget *parent = nullptr);
    ~pass1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::pass1 *ui;
};

#endif // PASS1_H
