#include "vendaaddview.h"
#include "ui_vendaaddview.h"
#include <QDate>

VendaAddView::VendaAddView(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::VendaAddView)
{
    m_ui->setupUi(this);
    QDate now = QDate::currentDate();
    m_ui->dataDateEdit->setDate(now);
    m_ui->dataDateEdit->setMaximumDate(now);
}

VendaAddView::~VendaAddView()
{
    delete m_ui;
}

void VendaAddView::changeEvent(QEvent *e)
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
