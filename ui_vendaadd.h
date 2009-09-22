/********************************************************************************
** Form generated from reading ui file 'vendaadd.ui'
**
** Created: Tue Sep 15 16:16:05 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VENDAADD_H
#define UI_VENDAADD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VendaAdd
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *clienteLineEdit;
    QToolButton *findClienteButton;
    QLabel *label_2;
    QLineEdit *itensLineEdit;
    QLabel *label_3;
    QLineEdit *valorLineEdit;
    QLabel *label_4;
    QLineEdit *dataLineEdit;
    QGroupBox *groupBox_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *VendaAdd)
    {
        if (VendaAdd->objectName().isEmpty())
            VendaAdd->setObjectName(QString::fromUtf8("VendaAdd"));
        VendaAdd->resize(663, 351);
        verticalLayout_3 = new QVBoxLayout(VendaAdd);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(VendaAdd);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(200000, 172));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        clienteLineEdit = new QLineEdit(groupBox);
        clienteLineEdit->setObjectName(QString::fromUtf8("clienteLineEdit"));
        clienteLineEdit->setMinimumSize(QSize(198, 28));

        horizontalLayout->addWidget(clienteLineEdit);

        findClienteButton = new QToolButton(groupBox);
        findClienteButton->setObjectName(QString::fromUtf8("findClienteButton"));

        horizontalLayout->addWidget(findClienteButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        itensLineEdit = new QLineEdit(groupBox);
        itensLineEdit->setObjectName(QString::fromUtf8("itensLineEdit"));
        itensLineEdit->setMaximumSize(QSize(67, 28));

        formLayout->setWidget(1, QFormLayout::FieldRole, itensLineEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        valorLineEdit = new QLineEdit(groupBox);
        valorLineEdit->setObjectName(QString::fromUtf8("valorLineEdit"));
        valorLineEdit->setMaximumSize(QSize(96, 28));

        formLayout->setWidget(2, QFormLayout::FieldRole, valorLineEdit);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        dataLineEdit = new QLineEdit(groupBox);
        dataLineEdit->setObjectName(QString::fromUtf8("dataLineEdit"));
        dataLineEdit->setMaximumSize(QSize(96, 28));

        formLayout->setWidget(3, QFormLayout::FieldRole, dataLineEdit);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(VendaAdd);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));

        verticalLayout_2->addWidget(groupBox_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(VendaAdd);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(VendaAdd);

        QMetaObject::connectSlotsByName(VendaAdd);
    } // setupUi

    void retranslateUi(QWidget *VendaAdd)
    {
        VendaAdd->setWindowTitle(QApplication::translate("VendaAdd", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("VendaAdd", "Dados Compra:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VendaAdd", "Cliente:", 0, QApplication::UnicodeUTF8));
        findClienteButton->setText(QApplication::translate("VendaAdd", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VendaAdd", "Itens:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("VendaAdd", "Valor:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("VendaAdd", "Data:", 0, QApplication::UnicodeUTF8));
        dataLineEdit->setInputMask(QString());
        groupBox_2->setTitle(QApplication::translate("VendaAdd", "Formas de Pagamento:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(VendaAdd);
    } // retranslateUi

};

namespace Ui {
    class VendaAdd: public Ui_VendaAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENDAADD_H
