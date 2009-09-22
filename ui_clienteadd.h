/********************************************************************************
** Form generated from reading ui file 'clienteadd.ui'
**
** Created: Fri Sep 11 16:28:16 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CLIENTEADD_H
#define UI_CLIENTEADD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClienteAdd
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ClienteAdd)
    {
        if (ClienteAdd->objectName().isEmpty())
            ClienteAdd->setObjectName(QString::fromUtf8("ClienteAdd"));
        ClienteAdd->resize(400, 300);
        verticalLayout = new QVBoxLayout(ClienteAdd);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(ClienteAdd);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(ClienteAdd);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(ClienteAdd);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(ClienteAdd);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(ClienteAdd);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ClienteAdd);

        QMetaObject::connectSlotsByName(ClienteAdd);
    } // setupUi

    void retranslateUi(QWidget *ClienteAdd)
    {
        ClienteAdd->setWindowTitle(QApplication::translate("ClienteAdd", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ClienteAdd", "Nome:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ClienteAdd", "CPF:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ClienteAdd);
    } // retranslateUi

};

namespace Ui {
    class ClienteAdd: public Ui_ClienteAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTEADD_H
