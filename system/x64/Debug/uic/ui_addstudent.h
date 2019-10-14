/********************************************************************************
** Form generated from reading UI file 'addstudent.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTUDENT_H
#define UI_ADDSTUDENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_addstudent
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_name;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QComboBox *comboBox_platoon;
    QComboBox *comboBox_class;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *comboBox_age;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_ok;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_cancle;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_major;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *lineEdit_job;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QRadioButton *radioButton_male;
    QRadioButton *radioButton_female;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_id;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *addstudent)
    {
        if (addstudent->objectName().isEmpty())
            addstudent->setObjectName(QString::fromUtf8("addstudent"));
        addstudent->resize(350, 480);
        gridLayout = new QGridLayout(addstudent);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(addstudent);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_name = new QLineEdit(addstudent);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setClearButtonEnabled(true);

        horizontalLayout->addWidget(lineEdit_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(addstudent);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        comboBox_platoon = new QComboBox(addstudent);
        comboBox_platoon->setObjectName(QString::fromUtf8("comboBox_platoon"));

        horizontalLayout_6->addWidget(comboBox_platoon);

        comboBox_class = new QComboBox(addstudent);
        comboBox_class->setObjectName(QString::fromUtf8("comboBox_class"));

        horizontalLayout_6->addWidget(comboBox_class);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_6, 7, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(addstudent);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        comboBox_age = new QComboBox(addstudent);
        comboBox_age->setObjectName(QString::fromUtf8("comboBox_age"));

        horizontalLayout_3->addWidget(comboBox_age);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        horizontalLayout_3->setStretch(2, 3);

        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_ok = new QPushButton(addstudent);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout_8->addWidget(pushButton_ok);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        pushButton_cancle = new QPushButton(addstudent);
        pushButton_cancle->setObjectName(QString::fromUtf8("pushButton_cancle"));

        horizontalLayout_8->addWidget(pushButton_cancle);


        gridLayout->addLayout(horizontalLayout_8, 9, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(addstudent);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_major = new QLineEdit(addstudent);
        lineEdit_major->setObjectName(QString::fromUtf8("lineEdit_major"));
        lineEdit_major->setClearButtonEnabled(true);

        horizontalLayout_5->addWidget(lineEdit_major);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_5, 6, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(addstudent);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        lineEdit_job = new QLineEdit(addstudent);
        lineEdit_job->setObjectName(QString::fromUtf8("lineEdit_job"));
        lineEdit_job->setClearButtonEnabled(true);

        horizontalLayout_7->addWidget(lineEdit_job);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_7, 8, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(addstudent);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        radioButton_male = new QRadioButton(addstudent);
        radioButton_male->setObjectName(QString::fromUtf8("radioButton_male"));

        horizontalLayout_2->addWidget(radioButton_male);

        radioButton_female = new QRadioButton(addstudent);
        radioButton_female->setObjectName(QString::fromUtf8("radioButton_female"));

        horizontalLayout_2->addWidget(radioButton_female);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 3);
        horizontalLayout_2->setStretch(2, 3);
        horizontalLayout_2->setStretch(3, 4);

        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        label = new QLabel(addstudent);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(25);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(addstudent);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_id = new QLineEdit(addstudent);
        lineEdit_id->setObjectName(QString::fromUtf8("lineEdit_id"));
        lineEdit_id->setClearButtonEnabled(true);

        horizontalLayout_4->addWidget(lineEdit_id);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        retranslateUi(addstudent);

        QMetaObject::connectSlotsByName(addstudent);
    } // setupUi

    void retranslateUi(QDialog *addstudent)
    {
        addstudent->setWindowTitle(QCoreApplication::translate("addstudent", "\346\267\273\345\212\240\345\255\246\345\221\230", nullptr));
        label_2->setText(QCoreApplication::translate("addstudent", "\345\247\223 \345\220\215\357\274\232", nullptr));
        lineEdit_name->setPlaceholderText(QCoreApplication::translate("addstudent", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215", nullptr));
        label_7->setText(QCoreApplication::translate("addstudent", "\347\217\255 \346\216\222\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("addstudent", "\345\271\264 \351\276\204\357\274\232", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("addstudent", "\347\241\256\345\256\232", nullptr));
        pushButton_cancle->setText(QCoreApplication::translate("addstudent", "\345\217\226\346\266\210", nullptr));
        label_6->setText(QCoreApplication::translate("addstudent", "\344\270\223 \344\270\232\357\274\232", nullptr));
        lineEdit_major->setPlaceholderText(QCoreApplication::translate("addstudent", "\350\257\267\350\276\223\345\205\245\344\270\223\344\270\232", nullptr));
        label_8->setText(QCoreApplication::translate("addstudent", "\350\201\214 \345\212\241\357\274\232", nullptr));
        lineEdit_job->setPlaceholderText(QCoreApplication::translate("addstudent", "\350\257\267\350\276\223\345\205\245\350\201\214\345\212\241", nullptr));
        label_3->setText(QCoreApplication::translate("addstudent", "\346\200\247 \345\210\253\357\274\232", nullptr));
        radioButton_male->setText(QCoreApplication::translate("addstudent", "\347\224\267", nullptr));
        radioButton_female->setText(QCoreApplication::translate("addstudent", "\345\245\263", nullptr));
        label->setText(QCoreApplication::translate("addstudent", "      \346\267\273 \345\212\240 \345\255\246 \345\221\230", nullptr));
        label_5->setText(QCoreApplication::translate("addstudent", "\345\255\246 \345\217\267\357\274\232", nullptr));
        lineEdit_id->setPlaceholderText(QCoreApplication::translate("addstudent", "\350\257\267\350\276\223\345\205\24512\344\275\215\345\255\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addstudent: public Ui_addstudent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTUDENT_H
