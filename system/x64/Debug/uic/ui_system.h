/********************************************************************************
** Form generated from reading UI file 'system.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_System
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *System)
    {
        if (System->objectName().isEmpty())
            System->setObjectName(QString::fromUtf8("System"));
        System->resize(800, 600);
        centralwidget = new QWidget(System);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        System->setCentralWidget(centralwidget);
        menubar = new QMenuBar(System);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        System->setMenuBar(menubar);
        statusbar = new QStatusBar(System);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        System->setStatusBar(statusbar);

        retranslateUi(System);

        QMetaObject::connectSlotsByName(System);
    } // setupUi

    void retranslateUi(QMainWindow *System)
    {
        System->setWindowTitle(QCoreApplication::translate("System", "System", nullptr));
    } // retranslateUi

};

namespace Ui {
    class System: public Ui_System {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEM_H
