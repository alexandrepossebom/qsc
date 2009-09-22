#include "vendaadd.h"
#include "ui_vendaadd.h"

#include <QDoubleValidator>
#include <QIntValidator>
#include <QDate>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

VendaAdd::VendaAdd(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::VendaAdd)
{
    m_ui->setupUi(this);

    QIntValidator *itensValidator = new QIntValidator(0,50,this);
    m_ui->itensLineEdit->setValidator(itensValidator);

    //    QValidator *valorValidator = new QDoubleValidator( 0.0, 5000.0, 2, this );
    //    m_ui->valorLineEdit->setValidator( valorValidator );

    QRegExp regExp("[1-9]\\d{0,3}\.\\d{2}");
    m_ui->valorLineEdit->setValidator(new QRegExpValidator(regExp, this));

    m_ui->dataLineEdit->setInputMask("99/99/9999");
    m_ui->dataLineEdit->setText(QDate::currentDate().toString("dd/MM/yyyy"));

    m_ui->clienteLineEdit->setDisabled(true);

}

VendaAdd::~VendaAdd()
{
    delete m_ui;
}

void VendaAdd::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
