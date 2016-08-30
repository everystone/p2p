/********************************************************************************
** Form generated from reading UI file 'qtapp.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTAPP_H
#define UI_QTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtAppClass)
    {
        if (qtAppClass->objectName().isEmpty())
            qtAppClass->setObjectName(QStringLiteral("qtAppClass"));
        qtAppClass->resize(600, 400);
        menuBar = new QMenuBar(qtAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        qtAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qtAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(qtAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qtAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qtAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtAppClass->setStatusBar(statusBar);

        retranslateUi(qtAppClass);

        QMetaObject::connectSlotsByName(qtAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtAppClass)
    {
        qtAppClass->setWindowTitle(QApplication::translate("qtAppClass", "qtApp", 0));
    } // retranslateUi

};

namespace Ui {
    class qtAppClass: public Ui_qtAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAPP_H
