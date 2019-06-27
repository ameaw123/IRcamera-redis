/********************************************************************************
** Form generated from reading UI file 'T1.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T1_H
#define UI_T1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_T1
{
public:

    void setupUi(QWidget *T1)
    {
        if (T1->objectName().isEmpty())
            T1->setObjectName(QStringLiteral("T1"));
        T1->resize(400, 300);

        retranslateUi(T1);

        QMetaObject::connectSlotsByName(T1);
    } // setupUi

    void retranslateUi(QWidget *T1)
    {
        T1->setWindowTitle(QApplication::translate("T1", "T1", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class T1: public Ui_T1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T1_H
