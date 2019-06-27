/********************************************************************************
** Form generated from reading UI file 'UserDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERDEMO_H
#define UI_USERDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserDemoClass
{
public:

    void setupUi(QWidget *UserDemoClass)
    {
        if (UserDemoClass->objectName().isEmpty())
            UserDemoClass->setObjectName(QStringLiteral("UserDemoClass"));
        UserDemoClass->resize(600, 400);

        retranslateUi(UserDemoClass);

        QMetaObject::connectSlotsByName(UserDemoClass);
    } // setupUi

    void retranslateUi(QWidget *UserDemoClass)
    {
        UserDemoClass->setWindowTitle(QApplication::translate("UserDemoClass", "UserDemo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserDemoClass: public Ui_UserDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERDEMO_H
