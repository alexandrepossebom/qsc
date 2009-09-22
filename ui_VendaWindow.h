/********************************************************************************
** Form generated from reading ui file 'VendaWindow.ui'
**
** Created: Fri Sep 11 15:11:51 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VENDAWINDOW_H
#define UI_VENDAWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VendaWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VendaWindow)
    {
        if (VendaWindow->objectName().isEmpty())
            VendaWindow->setObjectName(QString::fromUtf8("VendaWindow"));
        VendaWindow->resize(800, 600);
        menubar = new QMenuBar(VendaWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        VendaWindow->setMenuBar(menubar);
        centralwidget = new QWidget(VendaWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        VendaWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(VendaWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        VendaWindow->setStatusBar(statusbar);

        retranslateUi(VendaWindow);

        QMetaObject::connectSlotsByName(VendaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VendaWindow)
    {
        VendaWindow->setWindowTitle(QApplication::translate("VendaWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(VendaWindow);
    } // retranslateUi

};

namespace Ui {
    class VendaWindow: public Ui_VendaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENDAWINDOW_H
