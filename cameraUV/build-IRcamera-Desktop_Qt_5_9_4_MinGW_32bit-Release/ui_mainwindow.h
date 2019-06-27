/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QComboBox *directorycomboBox;
    QToolButton *Button_save;
    QSplitter *splitter;
    QSplitter *splitter_2;
    QTextEdit *textEdit_log;
    QPushButton *pushButton_satrt;
    QPushButton *pushButton_catch;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(493, 362);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 31));
        label->setMaximumSize(QSize(16777215, 31));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        directorycomboBox = new QComboBox(centralWidget);
        directorycomboBox->setObjectName(QStringLiteral("directorycomboBox"));
        directorycomboBox->setMinimumSize(QSize(311, 0));

        horizontalLayout->addWidget(directorycomboBox);

        Button_save = new QToolButton(centralWidget);
        Button_save->setObjectName(QStringLiteral("Button_save"));
        Button_save->setMinimumSize(QSize(71, 21));
        Button_save->setMaximumSize(QSize(71, 21));

        horizontalLayout->addWidget(Button_save);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setMaximumSize(QSize(16777215, 16777215));
        splitter->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(splitter);

        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setMinimumSize(QSize(401, 131));
        splitter_2->setOrientation(Qt::Horizontal);
        textEdit_log = new QTextEdit(splitter_2);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        textEdit_log->setMinimumSize(QSize(311, 101));
        splitter_2->addWidget(textEdit_log);
        pushButton_satrt = new QPushButton(splitter_2);
        pushButton_satrt->setObjectName(QStringLiteral("pushButton_satrt"));
        pushButton_satrt->setMinimumSize(QSize(51, 91));
        pushButton_satrt->setLayoutDirection(Qt::LeftToRight);
        pushButton_satrt->setCheckable(true);
        pushButton_satrt->setChecked(false);
        splitter_2->addWidget(pushButton_satrt);

        verticalLayout->addWidget(splitter_2);

        pushButton_catch = new QPushButton(centralWidget);
        pushButton_catch->setObjectName(QStringLiteral("pushButton_catch"));

        verticalLayout->addWidget(pushButton_catch);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 493, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\220\214\346\265\216\345\244\247\345\255\246IRcamera\345\267\245\345\205\267", Q_NULLPTR));
        directorycomboBox->clear();
        directorycomboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "C:\\Users\\LHM\\Desktop\\IRPICTURES", Q_NULLPTR)
        );
        Button_save->setText(QApplication::translate("MainWindow", "\345\202\250\345\255\230\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_satrt->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        pushButton_catch->setText(QApplication::translate("MainWindow", "catch", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
