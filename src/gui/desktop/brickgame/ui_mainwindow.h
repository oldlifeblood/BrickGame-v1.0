/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonTetris;
    QPushButton *pushButtonSnake;
    QPushButton *pushButtonComingSoon;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 500);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-color: #2e2e2e;\n"
"    }\n"
"    QLabel {\n"
"        color: #ffffff;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #4CAF50;\n"
"        color: white;\n"
"        border: none;\n"
"        border-radius: 10px;\n"
"        padding: 10px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #45a049;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #388e3c;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(20);
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButtonTetris = new QPushButton(centralwidget);
        pushButtonTetris->setObjectName("pushButtonTetris");
        pushButtonTetris->setMinimumSize(QSize(150, 100));
        QFont font1;
        font1.setPointSize(16);
        pushButtonTetris->setFont(font1);

        horizontalLayout->addWidget(pushButtonTetris);

        pushButtonSnake = new QPushButton(centralwidget);
        pushButtonSnake->setObjectName("pushButtonSnake");
        pushButtonSnake->setMinimumSize(QSize(150, 100));
        pushButtonSnake->setFont(font1);

        horizontalLayout->addWidget(pushButtonSnake);

        pushButtonComingSoon = new QPushButton(centralwidget);
        pushButtonComingSoon->setObjectName("pushButtonComingSoon");
        pushButtonComingSoon->setMinimumSize(QSize(150, 100));
        pushButtonComingSoon->setFont(font1);

        horizontalLayout->addWidget(pushButtonComingSoon);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BrickGame", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "BrickGame by sunnitif", nullptr));
        pushButtonTetris->setText(QCoreApplication::translate("MainWindow", "Tetris", nullptr));
        pushButtonSnake->setText(QCoreApplication::translate("MainWindow", "Snake", nullptr));
        pushButtonComingSoon->setText(QCoreApplication::translate("MainWindow", "Coming Soon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
