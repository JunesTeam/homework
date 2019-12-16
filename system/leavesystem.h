#ifndef LEAVESYSTEM_H
#define LEAVESYSTEM_H

#include <QWidget>
#include <QString>
#include <QSqlTableModel>

namespace Ui {
class leaveSystem;
}

class leaveSystem : public QWidget
{
    Q_OBJECT

public:
    explicit leaveSystem(QWidget *parent = nullptr);
    ~leaveSystem();

    void pushButton_wait(QString str);

private slots:
    void on_pushButton_pijia_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::leaveSystem *ui;
    //表格模型
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
};

#endif // LEAVESYSTEM_H
